#include<bits/stdc++.h>
using namespace std;
#define ll long long
int ans[100005];
int a[100005];
int main(){
	int owkey,reqkey,n,i;
cin>>owkey>>reqkey;
cin>>n;
for(i=0;i<n;i++)
cin>>a[i];
memset(ans,-1,sizeof(ans));
queue<int>q;
q.push(owkey);
ans[owkey]=0;
while(!q.empty()){
ll val=q.front();
q.pop();
if(val==reqkey)
break;
for(i=0;i<n;i++){
ll to=a[i];
to=to*val;
to%=100000;
if(ans[to]==-1){
ans[to]=ans[val]+1;
q.push(to);
}
}
}
printf("%d\n",ans[reqkey]);
	return 0;
}
