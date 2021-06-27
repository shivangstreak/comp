n,m=map(int,raw_input().split())
if(m==1):
    n=(n*(n-1))/2
    print "{0} {1}".format(n,n)
else:
    n=n-m
    mx=n*(n+1)/2
    x=1
    x=x+n/m
    y=n%m
    mn=(y*(x+1)*x)/2+((m-y)*x*(x-1))/2
    print "{0} {1}".format(mn,mx)
