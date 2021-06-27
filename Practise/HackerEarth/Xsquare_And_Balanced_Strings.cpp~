#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[26];
int main(){
        int t;scanf("%d",&t);
        string str;
        while(t--){
                fill(arr,arr+26,0);
                cin>>str;
                int len=str.size(),ans=0;
                for(int i=0;i<len;i++){
                        ans=ans^(1<<(str[i]-'a'));
                }
                
                /*int cnt=0;
                int flag=0;
                for(int i=0;i<26;i++){
                        if(arr[i]&1){
                                flag=1;
                                break;     
                        }
                }*/
                if(ans==0){
                        printf("1\n");
                }
                else{
                        printf("-1\n");
                }
        }
	return 0;
}	
