import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd
import time
import drywetlab

class OrganoidSim():

    def __init__(self, n, u, num_inputs, cam):

        self.u = None
        self.n = None
        self.cam = None

        Ne = 800
        N = 1000

        # Used for constructing nonhomogeneous neural populations,
        # interpolated between two types based on the value of
        # r ∈ [0,1]. Excitatory neurons go from Regular Spiking
        # to Chattering, while inhibitory neurons go from 
        # Low-Threshold Spiking to Late Spiking models over the
        # same range. Adapted from Izhikevich's writings.
        r = np.random.rand(N) # unitless
        l = np.ones(N) # unitless

        # a : 1/ms recovery time constant of membrane leak currents
        a = np.hstack((0.03*l[:Ne], 0.03 + 0.14*r[Ne:]))
        # b : nS recovery conductivity
        b = np.hstack((-2*l[:Ne] + 3*r[:Ne]**2, 8 - 3*r[Ne:]))
        # c : mV voltage of the downstroke
        c = np.hstack((-50 + 10*r[:Ne]**2, -53 + 8*r[Ne:]))
        # d : pA instantaneous increase in leakage during downstroke
        d = np.hstack((100 + 50*r[:Ne]**2, 20 + 80*r[Ne:]))
        # C : pF membrane capacitance
        C = np.hstack((100 - 50*r[:Ne]**2, 100 - 80*r[Ne:]))
        # k : nS/mV Na+ voltage-gated channel conductivity parameter 
        k = np.hstack((0.7 + 0.8*r[:Ne]**2, 1 - 0.7*r[Ne:]))
        # mV : resting membrane voltage
        Vr = np.hstack((-60*l[:Ne], -56 - 10*r[Ne:]))
        # mV : threshold voltage at u=0
        Vt = np.hstack((-40*l[:Ne], -42 + 2*r[Ne:]))

        # Sij : pA total EPSC generated in neuron i when neuron j fires.
        S = np.hstack((0.5 * np.random.rand(N,Ne), -np.random.rand(N,N-Ne))) * 42
        # v : mV membrane voltage
        v = l*Vr
        # u : pA membrane leakage current
        u = np.zeros_like(v)

        #---------------------------
        tau = 3 # EPSC decay time constant
        XY = np.random.rand(2,N) * 70#um

        # Lognormal distribution from Song (2005), converted from EPSP to EPSC.
        # Unfortunately, I do not yet (or maybe ever) have nice physical 
        # explanations of THESE parameters. :(
        mu, sigma = -0.702, 0.9355
        Covertau = np.mean(C / tau)
        S = np.random.lognormal(mean=mu, sigma=sigma, size=(N,N))
        S *= Covertau
        S[:,Ne:] *= -2

        n = drywetlab.PhysicalOrganoid(XY=XY, S=S, tau=tau,
                                       a=a, b=b, c=c, d=d, k=k, C=C, Vr=Vr, Vt=Vt)

        n.reset()
        #theta = np.linspace(0, 2*np.pi, num=9)[:-1]
        theta = np.linspace(0, 2*np.pi, num=num_inputs+1)[:-1] 
        points = 25*np.array((np.cos(theta), np.sin(theta))) + 35
        u = drywetlab.UtahArray(# spacing=10, shape=(7,7), offset=(5,5),
                                points=points, activation=None)
        u.insert(n)


        #----------------------------------
        def Iin(t):
            return 225*np.random.randn(N) + u.Iout(t)

        def tick(t, *args):
            states[t,:] = u.Vprobe()[1::2]

        interval = 100
        real_time = 25 * 1000
        frames = real_time // interval
        states = np.zeros((real_time, 24))
        cam = drywetlab.Ca2tCamera(n, Iin=Iin, frameskip=interval - 1, 
                                   window_size=11, reactivity=100)
        
        #--------------------------------------------
        self.u = u
        self.n = n
        self.cam = cam
        self.interval = interval
        self.num_inputs = num_inputs



    def make_rob_a_picture(self, name, t_stop, t_snap, pattern):
        cam = self.cam
        u = self.u
        n = self.n
        interval = self.interval
        num_inputs = self.num_inputs
        cam.init(plt.figure())
        #i = np.random.randint(1<<u_width)
        #u.activation = lambda t: 100 * ((np.arange(u_width) == i) & (t <= t_stop)) #!! activation
        def activation(t):
            bins = np.array([bit=='1' for bit in np.binary_repr(pattern, width=num_inputs)])
            return 100.0 * (bins & (t <= t_stop))
        u.activation = activation
        #n.reset() #resets model


        for T in range(t_snap // interval - 1):
            cam.update(T, show=False)
        cam.update(T, show=True)
        #print(np.binary_repr(pattern, width=num_inputs))
        plt.savefig(name + str(i) + '_' + str(np.binary_repr(pattern, width=num_inputs)) +'_'+'out'+'.png')
        
    def u_width(self):
        return self.u.points.shape[1]
    
    def plot_stim(self, name, pattern, num_inputs):
        plt.figure()
        theta = np.linspace(0, 2*np.pi, 9)[:-1] 
        points = 25*np.array((np.cos(theta), np.sin(theta))) + 35
        #print("Theta: " + str(theta))
        #print("Points: "+ str(points[1][1]))
        plt.xlim(-3.4, 73.4)
        plt.ylim(-3.4, 73.4)
        x = points[0,:]
        y = points[1,:]
        bins = np.array([bit=='1' for bit in np.binary_repr(pattern, width=8)])
        #print(bins)
        index = []
        for j in range(0,8):
            if(not bins[j]):
                #print("i is: " + str(bins[i]))
                index.append(j)

        x = np.delete(x, index)
        y = np.delete(y, index)
        plt.plot(x,y, 'o', color='tab:orange')   
        plt.savefig(name + str(i) + '_' + str(np.binary_repr(pattern, width=num_inputs))+'_'+'stim'+'.png')

        
