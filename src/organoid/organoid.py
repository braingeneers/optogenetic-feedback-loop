#!/usr/bin/python

import sys
import numpy
from PIL import Image

#-----------------------------------------------
import socket


def main():

		print 'Arg1:', sys.argv[1], '  Arg2:', sys.argv[2]
		s = socket.socket() #create socket
		port = int(sys.argv[2]) #bind to port

		# connect to server
		host_ip = socket.gethostbyname(str(sys.argv[1]))
		s.connect((host_ip, port))

		seq_num = 0 #feedback loop sequence number

		while True:
			# receive data from server
			input = s.recv(1024)
			print 'Master sent', input, int(input)
			#-----------------------------------------------
			s.send(input)

			#Organoid Simulation
			organoid(seq_num, int(input))

			seq_num+=1 #increment sequence number

		#-----------------------------------------------
		s.close() #close socket
		#-----------------------------------------------


def organoid(seq_num, input_pattern):
        a = numpy.random.rand(30,30,3) * 255
        b = numpy.random.rand(30,30,3) * 255
        a = a - 3*b
        im_out = Image.fromarray(a.astype('uint8')).convert('L')
        im_out = im_out.resize([3000,3000])
        im_out.save('out%000d.jpg' % seq_num)
	return;


if __name__=="__main__":
   main()
