import sys
import socket
import random
import time


def main():

		print 'Arg1:', sys.argv[1], ' Arg2:', sys.argv[2]
		s = socket.socket() #create socket
		port = int(sys.argv[2]) #bind to port

		# connect to server
		host_ip = socket.gethostbyname(str(sys.argv[1]))
		s.connect((host_ip, port))
		seq_num = 0
		pattern = 0
		while True:
			
#			if(seq_num%2==0 or seq_num == 41):
#				pattern=0
#			else:
#				pattern=21 
			# send 8 bit number
			s.send( #str(pattern)) #
				str(random.randint(0,255)))
			out = s.recv(128) # receive echo from client
			print 'Recieved:', out
			#time.sleep(1)
			seq_num+=1

		#-----------------------------------------------
		s.close() #close socket
		#-----------------------------------------------


if __name__ == '__main__':
	  main()
