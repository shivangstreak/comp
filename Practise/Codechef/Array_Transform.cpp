#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[105];
int Hash[15];
int main(){
        int t;scanf("%d",&t);
        while(t--){
                memset(Hash,0,sizeof(Hash));
                int n,k;scanf("%d%d",&n,&k);
                for(int i=0;i<n;i++){
                        scanf("%d",&arr[i]);
                        Hash[(arr[i]%(k+1)+k+1)%(k+1)]++;
                }
                int mx=*max_element(Hash,Hash+15);
                if(mx>=n-1){
                        printf("YES\n");
                }
                else{
                        printf("NO\n");
                }
        }
	return 0;
}	


