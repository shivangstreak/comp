#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
string str1,str2,str3;
const int N=1e6+5;
ll z[2*N];
void z_algo(){
        int n=str3.size();
        ll l=0,r=0;
        for(int i=1;i<n;i++){
                if(i>r){
                        l=r=i;
                        while(r<n && str3[r-l]==str3[r]){
                                r++;
                        }           
                        z[i]=r-l;
                        r--;              
                }
                else{
                        int k=i-l;
                        if(i+z[k]<=r){
                                z[i]=z[k];                        
                        }
                        else{
                                l=i;
                                while(r<n && str3[r-l]==str3[r]){
                                        r++;
                                }           
                                z[i]=r-l;
                                r--;                                
                        }
                }
        }
}
int main(){
        faster;
        int t;cin>>t;
        while(t--){
                memset(z,0,sizeof(z));
                str1="";
                str2="";
                str3="";
                cin>>str1>>str2;
                int m=str2.size(); 
                str2+=str2;
                str3=str1;
                str3+="#";
                str3+=str2;
                z_algo();
                ll ans=0;
                int len=str3.size(),n=str1.size();
               /* for(int i=0;i<len;i++){
                        cout<<z[i]<<" ";
                }
                cout<<endl;
                cout<<n+1<<" "<<len-2<<endl;*/
                for(int i=n+1;i<len-m;i++){
                     //   cout<<i<<" "<<z[i]<<endl;
                        if(z[i]==n){
                                ans++;
                        }
                }
                printf("%lld\n",ans);
        }        
	return 0;
}	


