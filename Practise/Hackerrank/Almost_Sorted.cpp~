#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;scanf("%d",&n);
	vector<int>v,v1;
	for(int i=0;i<n;i++){
		int d;scanf("%d",&d);
		v.push_back(d);
	}
	v1=v;
	sort(v1.begin(),v1.end());
	int start;
	int end;
	for(start=0;start<n;start++){
		if(v1[start]!=v[start]){
			break;
		}
	}
	if(start!=n){
		for(end=n-1;end>=0;end--){
			if(v1[end]!=v[end]){
				break;
			}
		}
		int f=1;
		swap(v[start],v[end]);
		for(int i=start;i<end;i++){
			if(v[i]>v[i+1]){
				f=0;
				break;
			}
		}
		if(f==1){
			cout<<"yes\n"<<"swap "<<start+1<<" "<<end+1<<"\n";
			return 0;
		}
		else{
			f=1;
			swap(v[start],v[end]);
			for(int i=start;i<end;i++){
				if(v[i]<v[i+1]){
					f=0;
					break;
				}
			}
			if(f==1){
				
				cout<<"yes\n"<<"reverse "<<start+1<<" "<<end+1<<"\n";
				return 0;
			}			
			else{
				cout<<"no\n";
			}	
		}		
	}
	else{
		printf("yes\n");
	}
	return 0;
}
