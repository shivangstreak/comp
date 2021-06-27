#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+6;
int p[N];
string str;
int k,mx;
int len;
void kmp(){
        p[0]=0;
        int i=1;
        int j=0;
        while(i<len){
                if(str[j]==str[i]){
                        p[i]=j+1;
                        if(i<=k){
                            //    cout<<i<<" "<<p[i]<<endl;
                              mx=max(mx,p[i]);
                        }
                        i++;
                        j++;
                }
                else{
                        if(j==0){
                                p[i]=0;
                                if(i<=k){
                                      mx=max(mx,p[i]);
                                }
                                i++;
                        }
                        else{
                                j=p[j-1];
                        }
                }
        }
}
int main(){
        int t;
        cin>>t;
        while(t--){
                memset(p,0,sizeof(p));
                cin>>str>>k;
                k--;
                len=str.size();
                mx=0;
                kmp();
              //  cout<<mx<<endl;
                int temp=p[len-1];
                while(temp!=0 && temp>mx){
                        temp=p[temp-1];
                }
                if(temp==0){
                        cout<<"Puchi is a cheat!\n";
                }
                else{
                        cout<<str.substr(0,temp)<<"\n";
                }
        } 
	return 0;
}	


