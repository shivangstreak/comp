#include <iostream>
using namespace std;
int arr[550];
void call(){
    arr[0]=1;
    int two=2,three=3,five=5,ii=0,j=0,k=0;
    for(int i=1;i<550;i++){
        int temp=min(min(two,three),five);
        arr[i]=temp;
        if(temp==two){
            ii++;
            two=arr[ii]*2;
        }
        if(temp==three){
            j++;
            three=arr[j]*3;
        }
        if(temp==five){
            k++;
            five=arr[k]*5;
        }
    }
}
int main() {
	int t,n;scanf("%d",&t);
	call();
	while(t--){
	    scanf("%d",&n);
	    cout<<arr[n-1]<<"\n";
	}
	return 0;
}
