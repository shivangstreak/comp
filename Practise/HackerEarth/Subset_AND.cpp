#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[1005];
int main(){
        int t,z,n;scanf("%d",&t);
        while(t--){
                scanf("%d %d",&z,&n);
                int flag;
                for(int i=0;i<n;i++){
                        scanf("%d",&arr[i]);
                }
                for(int i=31;i>=0;i--){
                        if(z&(1<<i)){
                               // cout<<i<<endl;
                                flag=0;
                                for(int j=0;j<n;j++){
                                     //   cout<<"Inside "<<arr[j]<<endl;
                                        if(( (1<<i) & arr[j])==0){
                                                //cout<<"COme on\n";
                                                flag=1;
                                                break;
                                        }
                                }
                                if(flag==0){
                                        break;
                                }
                        }
                }
                if(flag==0){
                        printf("No\n");
                        continue;
                }  
                printf("Yes\n");
        }
	return 0;
}	


