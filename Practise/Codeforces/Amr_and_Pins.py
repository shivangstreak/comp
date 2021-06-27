import math
r,x,y,x1,y1=map(int,raw_input().split())
d=math.sqrt((x-x1)**2+(y-y1)**2)
#print d
print int(math.ceil(d/(r*2.0)))
