#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
        int n,t,d;scanf("%d",&t);
        int flag;
        while(t--){
                scanf("%d",&n);
                scanf("%d",&d);
                int gc=d;
                flag=0;
                for(int i=1;i<n;i++){
                        scanf("%d",&d);
                        gc=__gcd(d,gc);
                        if(gc==1){
                                flag=1;
                        }
                }
                if(flag==1){
                        printf("%d\n",n);
                }
                else{
                        printf("-1\n");
                }
        }
	return 0;
}	


