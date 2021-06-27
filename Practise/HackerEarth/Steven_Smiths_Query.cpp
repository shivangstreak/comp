#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+6;
int BIT[N];
int ans[N];
pair<pair<int,int>,int>arr[N];
int Query(int indx){
        int res=0;
        while(indx>0){
                res+=BIT[indx];
                indx-=(indx&(-indx));
        }
        return res;
}
void Update(int indx,int val){
        while(indx<=N){
                BIT[indx]+=val;
                indx+=(indx&(-indx));
        }
}
int main(){
        int n,t,o;scanf("%d",&n);
        for(int i=0;i<n;i++){
                scanf("%d%d",&t,&o);
                arr[i].first.first=t;
                arr[i].first.second=o;
                arr[i].second=i;
        }
        sort(arr,arr+n);
       // cout<<endl;
        int i=0;
        while(i<n){
              int temp=i;
              ans[arr[temp].second]=Query(arr[temp].first.second);
             // cout<<arr[temp].first.first<<" "<<arr[temp].first.second<<" "<<arr[temp].second<<endl;
              while(i<n && arr[temp].first.first==arr[i].first.first && arr[temp].first.second==arr[i].first.second){
                          ans[arr[i].second]=ans[arr[temp].second]; 
                          i++;               
              }
              i=temp;
              while(i<n && arr[temp].first.first==arr[i].first.first && arr[temp].first.second==arr[i].first.second){
                          Update(arr[i].first.second,1);
                          i++;               
              }
        }      
       // cout<<endl;
        for(int i=0;i<n;i++){
                printf("%d\n",ans[i]);
        } 
	return 0;
}	


