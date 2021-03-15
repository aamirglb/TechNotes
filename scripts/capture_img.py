#!/bin/python

import socket
import sys
import errno
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
img=1
try:
	sock.bind(('',5000))
	sock.setblocking(0)

except:
	print("bind failed")

while True:
	try:
		msg = sock.recvfrom(70000)
		print("Captured image of ", len(msg[0]), len(msg[0])/1024, " bytes")
		if msg[0]:
			fname = str(img) + ".png"
			img+=1
			f = open(fname, "wb")
			f.write(msg[0])
			f.close()
	except socket.error, e:
		if e.args[0] == errno.EWOULDBLOCK:
			pass
	time.sleep(0.2)

