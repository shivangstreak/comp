#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
/*struct node{
	int x,y;
}a[2005];*/
double v1[2005],v2[2005];
double dist(double x,double y,double s,double d){
	return (x-s)*(x-s)+(y-d)*(y-d);
}
int main(){
	int n;cin>>n;
	double x,y,x1,y2,x2,y1;
	cin>>x1>>y1>>x2>>y2;
	for(int i=0;i<n;i++){
		cin>>x>>y;
		v1[i]=dist(x,y,x1,y1);
		v2[i]=dist(x,y,x2,y2);
	}
	vector<double>ans1,ans2;
	for(int i=0;i<n;i++){
		if(v1[i]<v2[i]){
			ans1.pb(v1[i]);
		}
		else if(v1[i]>v2[i]){
			ans2.pb(v2[i]);
		}
		else{
			ans1.pb(v1[i]);
			ans2.pb(v2[i]);
		}
	}
	double an1=-1,an2=-1;
	int s1=ans1.size(),s2=ans2.size();
	for(int i=0;i<s1;i++){
		an1=max(ans1[i],an1);
	}
	for(int i=0;i<s2;i++){
		an2=max(ans2[i],an2);
	}
	
	if(an1!=-1 && an2!=-1){
		cout<<an1+an2<<"\n";
	}
	else if(an1!=-1 && an2==-1){
		cout<<an1<<"\n";
	}
	else if(an1==-1 && an2!=-1){
		cout<<an2<<"\n";
	}
	return 0;
}
