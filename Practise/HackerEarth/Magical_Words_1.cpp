#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
string str;
int start,End;
int main(){
        faster;    
        int t;cin>>t;
        while(t--){
                ll ans=0;
                cin>>str;
                int len=str.size();
                for(int i=0;i<len;i++){
                        start=i;
                        End=i;
                        while(start>=0 && End<len && str[start]==str[End]){
                                ans+=(End-start+1)*(End-start+1);
                                start--;
                                End++;
                        }                        
                }
                for(int i=1;i<len;i++){
                        start=i-1;
                        End=i;
                        while(start>=0 && End<len && str[start]==str[End]){
                                ans+=(End-start+1)*(End-start+1);
                                start--;
                                End++;
                        }                        
                }
                cout<<ans<<"\n";
        }
	return 0;
}	


