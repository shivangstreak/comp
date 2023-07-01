# d = {}
#
# d[1]=2
# d[4]=4
#
# print(d.items())
#
#
# for i in sorted(d.items(), key=lambda x: x[1], reverse=True):
#     print(i)
#
# print([2]*3)

# f = "the services are as follows"
# f = f.split()
# print(f)
# f = f[::-1]
# print(f)
#
# print(' '.join(f))


# for i in range(6,1,-1):
#     print(i)

# t = "5,6"
# y=t.split(',')
# a,b = y
# a = int(a)
# b = int(b)
# print(type(a))
# print(b)
# from collections import defaultdict
#
# f = defaultdict(int)
#
# f[2]=99
# f[3]="sss"
# print(f)


d = {}

d[1] = 1
d[3] = "ASSS"

for i in enumerate(d.keys()):
    print(i)

