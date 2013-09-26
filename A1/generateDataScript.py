from random import randint
import glob

#print "hello!"
id = 0
f = open("data", "w")
while id < 5000:
	a = randint(0,100)
	b = randint(0,100)
	c = randint(0,100)
	line = "%d,%d,%d,%d\n" % (id,a,b,c)
	id+=1
	
	#print "%s" % line
	f.write(line)

f.close()

	
	 
