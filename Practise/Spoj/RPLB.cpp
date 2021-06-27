#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[1005];
int dp[1005][2000];
int n,k;
int solve(int i,int w){
	if(i>n)
		return w;
	if(dp[i][w]!=-1){
		return dp[i][w];
	}
	if(arr[i]+w<=k){
		dp[i][w]=max(solve(i+2,arr[i]+w),solve(i+1,w));
	}
	else{
		dp[i][w]=solve(i+1,w);
	}
	return dp[i][w];
}
int main(){
	int t;scanf("%d",&t);
	int Case=1;
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&arr[i]);
		memset(dp,-1,sizeof(dp));
		printf("Scenario #%d: %d\n",Case++,solve(1,0));	
	}
	return 0;
}
/*
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define MAX 1005
#define MaxOf(a,b) ((a)>(b)?(a):(b))

using namespace std;

int Raspberries[MAX],Table[MAX][MAX];
int PickMaximum(int ,int );
int main(void){
   
    int i,TestCases,NumberOfBushes,MaximumCapacity;
    int Scenario=1;
   
    scanf("%d",&TestCases);
   
    while(TestCases--){
       
        scanf("%d%d",&NumberOfBushes,&MaximumCapacity);
       
        for(i=0;i<NumberOfBushes;i++)
            scanf("%d",&Raspberries[i]);
       
        printf("Scenario #%d: %d\n",Scenario,PickMaximum(NumberOfBushes,MaximumCapacity));   
        Scenario++;
       
    }  
   
    return 0;   
   
}

int PickMaximum(int TotalBushes,int Capacity){
   
    int i,j;
    //If we have finite berries but zero capacity then number of maximum pickings are 0 and vice versa.    -Base Case
    memset(Table,0,sizeof(int)*MAX*MAX);
       
    for(i=1;i<=TotalBushes;i++){
       
        for(j=1;j<=Capacity;j++){
           
            if(i==1){//Again a base case.

//When we have only one bush in total then Raspberries can be picked if they are less than CurrentCapacity other wise 0 selections are made.
               
                if(Raspberries[i-1]<=j)
                     Table[i][j]=Raspberries[i-1];
               
                else Table[i][j]=0;
               
            }
           
            else{
             
              if(j-Raspberries[i-1]<0)
                Table[i][j]=Table[i-1][j];
           
              else Table[i][j]=MaxOf(Raspberries[i-1]+Table[i-2][j-Raspberries[i-1]],Table[i-1][j]);       
           
            }
       
        }       
       
    }       
       
    return Table[TotalBushes][Capacity];
   
}
*/
