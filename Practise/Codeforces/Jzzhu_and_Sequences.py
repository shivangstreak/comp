x,y=map(int,raw_input().split())
n=input()
n=n-1
n=n%6
MOD=int(1e9+7)
a=[]
a.append(x)
a.append(y)
for i in xrange(4):
    l=len(a)
    a.append(a[l-1]-a[l-2])
#print "MOD is",MOD
#print "\nn is {0}".format(n)
print a[n]%MOD
