import maxflow
import numpy as np


def readdata(fname):
	prefmatrix =[]
	with open(fname) as f:
		for line in f:
			prefmatrix.append([int(x) for x in line.split(",")])
	return np.array(prefmatrix)

def parta(pm):
	g = maxflow.Graph[int](50, 120)
	numemps = pm.shape[0]
	numjobs = pm.shape[1]
	print "Total jobs:", numjobs
	empnodes = g.add_nodes(numemps)
	jobnodes = g.add_nodes(numjobs)
	
	for i in xrange(numemps):
		g.add_tedge(empnodes[i], numjobs, 0)
	for i in xrange(numjobs):
		g.add_tedge(jobnodes[i], 0, 1)

	# for i in xrange(min(numemps, numjobs)):
	# 	g.add_edge(empnodes[i], jobnodes[i], 1, 0)

	for i in xrange(numemps):
		for j in xrange(numjobs):
			if pm[i][j] == 1 or pm[i][j] == 2:
				#print i,j,pm[i][j]
				g.add_edge(empnodes[i], jobnodes[j], 1, 0)

	flow = g.maxflow()
	print "Maximum no of jobs that can be assigned:", flow

def parta2(pm):
	g = maxflow.Graph[int](50, 120)
	numemps = pm.shape[0]
	numjobs = pm.shape[1]
	print "Total jobs:", numjobs
	empnodes = g.add_nodes(numemps)
	jobnodes = g.add_nodes(numjobs)
	
	for i in xrange(numemps):
		g.add_tedge(empnodes[i], 0, numjobs)
	for i in xrange(numjobs):
		g.add_tedge(jobnodes[i], 1, 0)

	# for i in xrange(min(numemps, numjobs)):
	# 	g.add_edge(empnodes[i], jobnodes[i], 1, 0)

	for i in xrange(numemps):
		for j in xrange(numjobs):
			if pm[i][j] == 1 or pm[i][j] == 2:
				#print i,j,pm[i][j]
				g.add_edge(jobnodes[j], empnodes[i], 1, 0)

	flow = g.maxflow()
	print "Maximum no of jobs that can be assigned:", flow

pm = readdata("preferenceMatrix.txt")
parta(pm)

#part (b)
from pulp import *
for i in xrange(pm.shape[0]):
	for j in xrange(pm.shape[1]):
		if pm[i][j] == -1:
			pm[i][j] = 0

prob = LpProblem("assignment", LpMinimize)
variables = [LpVariable("x"+str(i)+'_'+str(j), None, None, LpBinary) for i in xrange(pm.shape[0]) for j in xrange(pm.shape[1]) if pm[i][j]>0]
#print variables
#objective
def geti(v):
	return int(v.name[1:].split("_")[0])
def getj(v):
	return int(v.name[1:].split("_")[1])

prob += sum(pm[geti(v)][getj(v)]*v for v in variables)

#constraints
for i in xrange(pm.shape[0]):
	prob += sum(v for v in variables if geti(v) == i) <= 2
	prob += sum(v for v in variables if geti(v) == i) >= 1

for j in xrange(pm.shape[1]):
	prob += sum(pm[geti(v)][getj(v)]*v for v in variables if getj(v) == j) >= 1
	prob += sum(v for v in variables if getj(v) == j) == 1


print prob

prob.solve()
for v in prob.variables(): 
	#print v.name, "=", v.varValue 
	if v.varValue == 1:
		print "Emp:", geti(v), "Job:", getj(v)

print "objective=", value(prob.objective)  
print "Average preference:", value(prob.objective) / pm.shape[1]