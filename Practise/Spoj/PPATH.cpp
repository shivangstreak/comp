#include<bits/stdc++.h>
using namespace std;
bool prime[10005];
int digits[4];
int dist[10005];
int a,b;
void D(int a){
	digits[0]=a%10;
	digits[1]=(a%100)/10;
	digits[2]=(a%1000)/100;
	digits[3]=(a%10000)/1000;
}
int compute(){
	int Y=(digits[3]*1000)+(digits[2]*100)+(digits[1]*10)+(digits[0]);
	return Y;
}
queue<int>q;
void bfs(int a){
	q.push(a);
	int Y;
	dist[a]=0;
	while(1){
		int temp=q.front();
		for(int k=0;k<4;k++){
			for(int h=0;h<=9;h++){
				D(temp);
				digits[k]=h;
				Y=compute();
				if(prime[Y]==1 && dist[Y]==-1 && Y>=1000){
						dist[Y]=dist[temp]+1;
						q.push(Y);
				}
			}
		}
		if(temp==b){
			return;
		}
		q.pop();
	}
}
int main(){
	int t;scanf("%d",&t);
	memset(prime,true,sizeof(prime));
	prime[0]=prime[1]=false;
	for(int i=2;i<10005;i++){
		if(prime[i]==true){
			for(int j=i*i;j<10005;j+=i){
				prime[j]=false;
			}
		}
	}
	while(t--){
		scanf("%d%d",&a,&b);
		if(a==b){
			printf("0\n");
			continue;
		}
		memset(dist,-1,sizeof(dist));
		while(q.empty()==false){
			q.pop();
		}
		bfs(a);
		cout<<dist[b]<<"\n";
	}
	return 0;
}
