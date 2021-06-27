#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
int temp[N],arr[N];
int len;
int Binary_Search_Ceil(int start,int end,int val){
        while(start<=end){
                int mid=(start+end)/2;
                if(mid<len && temp[mid]<val && temp[mid+1]>=val){
                        return mid+1;
                }
                else if(temp[mid]<val){
                        start=mid+1;
                }
                else{
                        end=mid-1;
                }
        }
        return -1;
}
int main(){
        int n;scanf("%d",&n);
        for(int i=0;i<n;i++){
                scanf("%d",&arr[i]);
        }
        temp[0]=arr[0];
        len=0;
        for(int i=1;i<n;i++){
                if(arr[i]<temp[0]){
                        temp[0]=arr[i];
                }
                else if(arr[i]>temp[len]){
                        len++;
                        temp[len]=arr[i];
                }
                else{
                        //cout<<arr[i]<<endl;
                        
                        int ind=Binary_Search_Ceil(0,len,arr[i]);
                        temp[ind]=arr[i];
                }
        }       
        printf("%d\n",len+1);
	return 0;
}	


