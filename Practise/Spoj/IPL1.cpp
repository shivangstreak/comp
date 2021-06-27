#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int tar;
double ov;
char str[100];
double dp[125][11][350];
double findprob(int balls,int wkt,int target){
       
        if(target<=0)
                return 1;
        if(wkt>=10 || balls>=120){
                return 0;
        }
        if(dp[balls][wkt][target]!=-1){
               
                return dp[balls][wkt][target];
        }        
        else{
	return dp[balls][wkt][target] = 
		 (findprob(balls+1,wkt,target)  
		+ findprob(balls+1,wkt,target-1) 
		+ findprob(balls+1,wkt,target-2) 
		+ findprob(balls+1,wkt,target-3) 
		+ findprob(balls+1,wkt,target-4) 
		+ findprob(balls+1,wkt,target-5) 
		+ findprob(balls+1,wkt,target-6) 
		+ findprob(balls+1,wkt+1,target) 
		+ findprob(balls,wkt,target-1) 
		+ findprob(balls,wkt,target-1)) / 10;
        }
}
int main(){
        int t;scanf("%d",&t);
        while(t--){
                for(int i=0;i<125;i++){
                        for(int j=0;j<11;j++){
                                for(int k=0;k<350;k++){
                                        dp[i][j][k]=-1;
                                }
                        }
                }
                scanf("%lf %s %d",&ov,str,&tar);
                int balls=6*(int)(ov)+(int)(10*(ov-(int)(ov)));
                int curr=0,i;
                for(i=0;i<strlen(str);i++){
                        if(str[i]=='/'){
                                break;
                        }
                }
                for(int j=0;j<i;j++){
                        curr = 10*curr + (str[j]-'0');
                }
                int wt=0;
                for(int j=i+1;j<strlen(str);j++){
                        wt=wt*10+(str[j]-'0');
                }
             //   cout<<balls<<" "<<curr<<" "<<wt<<endl;
                string result=to_string(findprob(balls,wt,tar-curr)*100);
                int jj=0,len=result.size();
                for(jj=0;jj<len;jj++){
                        if(result[jj]=='.'){
                                break;
                        }
                        else{
                                cout<<result[jj];
                        }
                }
                if(jj<len)
                        cout<<".";
                int kk=jj+1;
                for(;kk<len && kk<jj+3;kk++){
                        cout<<result[kk];
                }
                printf("\n");
        }
	return 0;
}
