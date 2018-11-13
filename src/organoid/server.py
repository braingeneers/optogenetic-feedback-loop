import sys
import socket
#import numpy as np
import random 
import time

s = socket.socket() #create socket

port = int(sys.argv[1]) 
s.bind(('', port)) #bind to port
print "socket binded to %s" %(port)

# listen on socket 
s.listen(5)
while True:

# Establish connection with client 
	c, addr = s.accept() 
	print 'Got connection from', addr 

	while True:
		# send 8 bit number 
		c.send(str(random.randint(0,255)))
		out = c.recv(1024)
		print 'Recieved:', out 
		time.sleep(1)

	# Close connection with client 
	c.close() 

