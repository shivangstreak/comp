#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int Next[105][100005];
int arr[105];
const int SUM=1e5+5;
int n;
void init(){
        for(int s=1;s<SUM;s++){
              Next[n+1][s]=n+1;  
        }
        for(int s=1;s<SUM;s++){
                int last=n;
                for(int start=n;start>=1;start--){
                        Next[start][s]=Next[start+1][s];
                        while(arr[last]-arr[start-1]>s){
                                last--;
                        }
                        if(arr[last]-arr[start-1]==s){
                                Next[start][s]=last;
                        }
                }
        }
}
int main(){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
                scanf("%d",&arr[i]);
        }
        for(int i=2;i<=n;i++){
                arr[i]+=arr[i-1];
        }
        init();
        vector<int>res;
        int mx=INT_MIN;
        for(int s=1;s<SUM;s++){
                int start=1;
                int cnt=0;
                while(start<=n){
                        if(Next[start][s]<=n){
                                cnt++;
                        }
                        start=Next[start][s]+1;
                }
                if(cnt>mx){
                        res.clear();
                        mx=cnt;
                }
                if(cnt==mx){
                        res.pb(s);
                }
        }
        printf("%d\n",mx);
        int len=res.size();
        for(int i=0;i<len;i++){
                printf("%d ",res[i]);
        }
        printf("\n");
	return 0;
}	
