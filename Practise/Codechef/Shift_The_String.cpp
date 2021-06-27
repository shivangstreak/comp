#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=(1e7+10);
string str1,str2,str3;
int n;
int z[N];
void z_algo(){
        int len=str3.size();
        int l=0,r=0;
        for(int i=1;i<len;i++){
                if(i>r){
                        l=r=i;
                        while(r<len && str3[r-l]==str3[r]){
                                r++;
                        }        
                        z[i]=r-l;
                        r--;
                }
                else{
                        int k=i-l;
                        if(z[k]+i<=r){
                                z[i]=z[k];
                        }
                        else{
                                l=i;
                                while(r<len && str3[r-l]==str3[r]){
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
        
        cin>>n;
        cin>>str1>>str2;
        str3=str1;
        str3+="#";
        str3+=str2;
        str3+=str2;
        z_algo();
        int mx=-1;
        int shifts;
        for(int i=0;i<n;i++){
                if(z[i+n+1]>mx){
                        mx=z[i+n+1];
                        shifts=i;
                }
        }
        cout<<shifts<<"\n";
	return 0;
}	


