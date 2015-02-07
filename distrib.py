#!/usr/bin/env python3

dict={}

while True:
	try:
		s=input()
	except EOFError:
		break
	
	try:
		dict[s]+=1
	except KeyError:
		dict[s]=1

for f in dict:
	print(f, dict[f])
