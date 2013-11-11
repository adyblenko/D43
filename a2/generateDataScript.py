from random import randint
import glob

#print "hello!"
id = 0
f = open("data3", "w")
while id < 10000:
	a = randint(0,10000)
	line = "%d,%d\n" % (id,a)
	id+=1
	
	#print "%s" % line
	f.write(line)

f.close()

#print "hello!"
id = 0
f = open("data2", "w")
while id < 10000:
	a = randint(0,10000)
	line = "%d,%d\n" % (id,a)
	id+=1
	
	#print "%s" % line
	f.write(line)

f.close()

	
	 
