#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=200005;
struct node{
	string ch;
	int d;
}arr[N];
set<int> Set;
int temp,size;
int record[N];
unordered_map<ll,int>mymap;
unordered_map<int,ll>backMap;
ll BITS[N];
ll giveSum(int indx){
	ll ans=0;
	while(indx>0){
		ans+=BITS[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
void update(int indx){
	while(indx<N){
		BITS[indx]++;
		indx+=indx&(-indx);
	}
}
void deleteUpdate(int indx){
	ll dummy=BITS[indx];
	while(indx<N){
		BITS[indx]-=dummy;
		indx+=indx&(-indx);
	}
}
int main(){
	memset(BITS,0,sizeof(BITS));
	int q;scanf("%d",&q);
	int d;
	string str;
	temp=1;
	for(int i=1;i<=q;i++){
		cin>>str;
		scanf("%d",&d);
		arr[i].ch=str;
		arr[i].d=d;
		if(str=="I" || str=="D" || str=="C")
			Set.insert(arr[i].d);
	}
	set<int>::iterator it;
	it=Set.begin();
	while(it!=Set.end()){
		if(mymap[*it]==0){
			mymap[*it]=temp;
			backMap[temp]=*it;
			temp++;
		}
		it++;
	}
	//cout<<"temp "<<temp<<endl;
	size=0;
	for(int i=1;i<=q;i++){
		//cout<<i<<" arr[i].ch "<<arr[i].ch<<" size "<<size<<endl;
		if(arr[i].ch=="I"){
			if(record[mymap[arr[i].d]]==0){
				update(mymap[arr[i].d]);
				record[mymap[arr[i].d]]=1;
				size++;	
			}
		}
		else if(arr[i].ch=="D"){
			if(record[mymap[arr[i].d]]==1){
				deleteUpdate(mymap[arr[i].d]);				
				record[mymap[arr[i].d]]=0;
				size--;		
			}
		}
		else if(arr[i].ch=="K"){
			int l=1;
			int r=temp-1;
			int mid,sum;
			int k=arr[i].d;
			if(k>size){
				printf("invalid\n");
				continue;
			}
			while(l<=r){
				mid=(l+r)/2;
				sum=giveSum(mid);
				if(sum==k){
					//printf("%lld\n",backMap[mid]);
					break;
				}
				else if(sum<k){
					l=mid+1;
				}
				else{
					r=mid-1;
				}
			}
			while(mid>0 && giveSum(mid)==k){
				mid--;
			}
			printf("%lld\n",backMap[mid+1]);
		}
		else if(arr[i].ch=="C"){
			//cout<<"no of data less than "<<mymap[arr[i].d]<<endl;
			printf("%lld\n",giveSum(mymap[arr[i].d]-1));
		}
	}
	return 0;
}
