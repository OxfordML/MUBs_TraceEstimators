import mubs
import numpy as np
import time
itters = 10000
t = time.time()
a = np.zeros([7109,1])
b = np.zeros([7109,1])
for i in xrange(itters):
	r0 = np.random.randint(0,7109)
	r1 = np.random.randint(0,7109)

	mubs.mubs(a,b,r0,r1,7109,7109)
print 'Time to compute 7109 dim MUBs:', (time.time() - t)/itters, 's'


r0 = np.random.choice(7109)
r1 = np.random.choice(7109)
c = np.zeros([7109,1])
d = np.zeros([7109,1])

mubs.mubs(c,d,r0,r1,7109,7109)

print 'Norm should equal one:', (c.T.dot(c) + d.T.dot(d))[0,0]
print 'Dot Product should equal ', 1./np.sqrt(7109), ':', np.abs((c + 1.j*d).T.dot(a + 1.j*b))[0,0]
