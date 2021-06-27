a

    #include<iostream>
    #include<cstdio>
    using namespace std;
    int main()
    {
        int N, S, Q;
        int i;
        scanf(" %d",&N);
        int a[1000002] = {0}; // initializing all the possible sweets' quantity 0 in the beginning
        for(i=0;i<N;i++)
        {
            scanf(" %d %d",&S,&Q);
            a[S] = Q;
        }
        int rmax[1000002];   // to store running max of quantities
        rmax[0] = 0;
        int mx = 0;
        for(i=1000000;i>0;i--)
        {
            if(mx<a[i])
            {
                mx = a[i];
            }
            rmax[i] = mx;
        }
        int G, M;
        long long R = 0;
        scanf(" %d",&G);
        for(i=0;i<G;i++)
        {
            scanf(" %d",&M);
            R = R + (rmax[M]/M)*100;
        }
        printf("%lld",R);
        return 0;
    }


