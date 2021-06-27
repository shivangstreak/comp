#include <bits/stdc++.h>
using namespace std;
int p,q,ans,t,w;
int prm[1200000];
bool chk(int x){   
     int rem=0;
     int x1=x;
     while(x){
          rem*=10;
          rem+=x%10;
          x/=10;
     }
     return x1==rem ;
}
int main(){
     cin>>p>>q;
     memset(prm,1,sizeof(prm));
     prm[1]=0;
     for (int i=2;i<=1200000;i++){
          if (!prm[i]) continue;
          prm[i]=1;
          for (int j=2;j*i<1200000;j++) prm[i*j]=0;
     }
     for (int i=1;i<=1200000;i++){
          t+=prm[i];
          w+=chk(i);
          if (w*p/q>=t) ans=i;
     }
     cout<<ans;
     return 0;
}
