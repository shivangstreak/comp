#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
string str,s;
int p[30005];
int ans,mx;
void manchar(){
        s="^";
        int len=str.size();
        for(int i=0;i<len;i++){
                s+="#";
                s+=str.substr(i,1);
        }
        s+="#$";
        len=s.size();
        int c=0,r=0;
        for(int i=1;i<len-1;i++){
                int mirror_i=2*c-i;
                p[i]=(r>i)?min(r-i,p[mirror_i]):0;
                while(s[i-1-p[i]]==s[i+1+p[i]]){
                        p[i]++;
                }
                if(i+p[i]>r){
                        c=i;
                        r=i+p[i];
                }
        }
        mx=*max_element(p,p+len-1);
        for(int i=1;i<len-1;i++){
                if(p[i]==mx){
                        ans++;
                }
        }
}
int main(){
        faster;
        int t;cin>>t;
        while(t--){
                str="";
                s="";
                ans=0;
                cin>>str;
                memset(p,0,sizeof(p));
                manchar();
                cout<<mx<<" "<<ans<<"\n";        
        }
	return 0;
}	


