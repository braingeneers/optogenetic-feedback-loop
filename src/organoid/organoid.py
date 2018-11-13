#!/usr/bin/python

import sys
import numpy
from PIL import Image

#-----------------------------------------------
import socket



def main():

		print 'Arg1:', sys.argv[1]
		s = socket.socket() #create socket

		port = int(sys.argv[1])
		s.bind(('', port)) #bind to port
		print "socket binded to %s" %(port)

		seq_num = 0 #feedback loop sequence number

		# listen on socket
		s.listen(5)
		while True:

		# Establish connection with client
			c, addr = s.accept()
			print 'Got connection from', addr

			while True:
					# receive 8 bit number from client
					input = c.recv(128)
					print 'Master sent', input, int(input)
					# echo 8 bit number
					c.send(input)

					#Organoid Simulation
					organoid(seq_num, int(input))

					seq_num+=1 #increment sequence number

			# Close connection with client
			c.close()
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


if __name__ == '__main__':
	  main()
