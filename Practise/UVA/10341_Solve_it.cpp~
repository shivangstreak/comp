#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
#define PRE 1e-7
int p,q,r,s,t,u;
double fxn(double x){
  return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}
 
double bisection(){
	double lo=0,hi=1;
	while(lo+PRE<hi){
		double x=(lo+hi)/2.0;
		if(fxn(lo)*fxn(x)<=0){
			hi=x;
		}
		else{
			lo=x;
		}
	}
	return (hi+lo)/2.0;
}
int main(){
	while(scanf("%d %d %d %d %d %d",&p,&q,&r,&s,&t,&u)==6){
		if(fxn(0)*fxn(1)>0){
			printf("No solution\n");
		}
		else{
			printf("%.4lf\n",bisection());
		}
	}
	return 0;
}
