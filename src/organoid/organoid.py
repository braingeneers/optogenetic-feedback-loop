#!/usr/bin/python

import sys
import numpy
from PIL import Image

#-----------------------------------------------
import socket

print 'Arg1:', sys.argv[1], '  Arg2:', sys.argv[2]
s = socket.socket() #create socket
port = int(sys.argv[2]) #bind to port

# connect to server
host_ip = socket.gethostbyname(str(sys.argv[1]))
s.connect((host_ip, port))

while True:
	# receive data from server
	input = s.recv(1024)
	print 'Master sent', input, int(input)
	#-----------------------------------------------
	s.send(input)
	#Organoid Simulation


	#for n in xrange(10):
	#    a = numpy.random.rand(30,30,3) * 255
	#    b = numpy.random.rand(30,30,3) * 255
	#    a = a - 2*b
	#    im_out = Image.fromarray(a.astype('uint8')).convert('L')
	#    im_out = im_out.resize([3000,3000])
	#    im_out.save('out%000d.jpg' % n)





#-----------------------------------------------
s.close() #close socket
#-----------------------------------------------


