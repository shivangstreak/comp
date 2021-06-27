#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const ll N=1e6+5;
bool pandatic[N],possible[N];
bool solve(int x){
        int temp=x;
        int digit;
        while(temp>0){
                digit=temp%10;
                temp/=10;
                if(digit==0)
                        continue;
                digit=digit*digit;
                if(x>digit && possible[x-digit]==true){
                        possible[x]=true;
                        return true;
                }        
        }
        return false;
}
int main(){
        int t;scanf("%d",&t);
        fill(pandatic,pandatic+N,false);
        fill(possible,possible+N,false);
        for(int i=1;i<N;i++){
                ll val=i*i;
                if(val>N)
                        break;
                pandatic[val]=true;
        }
        for(int i=1;i<N;i++){
                possible[i]=pandatic[i] || solve(i);
        }
        while(t--){
                int n;scanf("%d",&n);
                if(possible[n]==true){
                        printf("Yes\n");
                }
                else{
                        printf("No\n");
                }
        }
	return 0;
}	
