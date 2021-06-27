#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=5*1e5+6;

bool isValid(int n,vector<int>& A,int m,vector<int>& B,int time){
	int time_left;
	int j=n-1;

	for(int i=m-1;i>=0;i--){
		time_left=time;
		if(j<0){
			break;
		}
		while(j>=0 && time_left>0){
			if(B[i]>=A[j]){
				time_left--;
				j--;
			}
			else{
				break;
			}
		}
	}
	if(j==-1){
		return true;
	}
	else{
		return false;
	}
}

int min_time_needed(int n,vector<int>& A,int m,vector<int>& B){
	sort(A.begin(),A.end());
	sort(B.begin(),B.end());
	if(A[n-1]>B[m-1]){
		return -1;
	}
	int l=1;
	int r=1e9;
	int mid,ans,time;
	while(l<=r){
		mid=l+(r-l)/2;
		time = mid/2;
		if(mid&1){
			time++;
		}
		if(isValid(n,A,m,B,time)){
			//cout<<"mid is "<<time<<endl;
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	// if(l==r && isValid(n,A,m,B,l)){
	// 	ans=l;
	// }
	return ans;
}

int main(){
	faster
	int n,m,temp;
	vector<int> A,B;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>temp;
		A.push_back(temp);
	}

	for(int i=0;i<m;i++){
		cin>>temp;
		B.push_back(temp);
	}

	cout<<min_time_needed(n,A,m,B)<<"\n";
	return 0;
}