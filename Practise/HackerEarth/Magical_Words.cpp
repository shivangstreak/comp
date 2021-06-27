#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
        int t;scanf("%d",&t);
        while(t--){
                ll ans=0;
                string str;cin>>str;
                int len=str.size();
                for(int i=0;i<len;i++){
                       int start=i,end=i;
                       while(start>=0 && end<len){
                                 if(str[start]==str[end]){
                                        ans+=(end-start+1)*(end-start+1);
                                        start--;
                                        end++;
                                 }
                                 else{
                                        break;
                                 }
                       }      
                }
                for(int i=0;i<len-1;i++){
                       int start=i,end=i+1;
                       while(start>=0 && end<len){
                                 if(str[start]==str[end]){
                                        ans+=(end-start+1)*(end-start+1);
                                        start--;
                                        end++;
                                 }
                                 else{
                                        break;
                                 }
                       }      
                }
                cout<<ans<<"\n";                
        }
	return 0;
}	
