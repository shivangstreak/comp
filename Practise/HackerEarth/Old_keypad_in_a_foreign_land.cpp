#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll arr[100];
ll PP[100];
int main(){
        ll n,k,d;
        cin>>n;
        for(int i=0;i<n;i++){
                cin>>arr[i];
        }
        cin>>k;
        ll sum=0;
        for(int i=0;i<k;i++){
                cin>>d;
                sum+=d;
                PP[1]++;
                PP[d+1]--;
        }
        if(sum<n){
                cout<<"-1\n";
                return 0;
        }
        for(int i=1;i<100;i++){
                PP[i]+=PP[i-1];
        }
        sort(arr,arr+n);
        int j=1;
        ll ans=0;
        for(int i=n-1;i>=0;i--){
                while(j<100 && PP[j]==0){
                        j++;
                }
                //cout<<j<<" "<<arr[i]<<endl;
                PP[j]--;
                ans+=j*arr[i];
        }
        cout<<ans<<"\n";
	return 0;
}
