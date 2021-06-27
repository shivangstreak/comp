#include<bits/stdc++.h> // lower_bound c++ implementation
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
	int a[]={1,2,2,3,4,5};
	int l=0,hi=5,mid;
	int s=2;
	while(l<=hi){
		mid=l+(hi-l)/2;
		if(s>a[mid]){
			l=mid+1;
		}
		else{
			hi=mid-1;
		}
	}
	cout<<l<<endl;
	cout<<(lower_bound(a,a+6,2)-a)<<endl;
	return 0;
}


int _binarySearch(int arr[], int low, int high, int x)
{
    if (high >= low)
    {
        int mid = (low + high)/2; /*low + (high - low)/2;*/
 
        /* Check if arr[mid] is the first occurrence of x.
            arr[mid] is first occurrence if x is one of the following
            is true:
            (i) mid == 0 and arr[mid] == x
            (ii) arr[mid-1] < x and arr[mid] == x
        */
        if ( (mid == 0 || x > arr[mid-1]) && (arr[mid] == x) )
            return mid;
        else if (x > arr[mid])
            return _binarySearch(arr, (mid + 1), high, x);
        else
            return _binarySearch(arr, low, (mid -1), x);
    }
 
    return -1;
}

int firstOccur(int left,int right,int x){
        int ans=-1;
        while(left<=right){
                int mid=(left+right)/2;
                if(arr[mid]==x){
                   ans=mid;
                   high=mid-1;     
                }
                else if(x>arr[mid]){
                        low=mid+1;
                }
                else if(x<arr[mid]){
                        high=mid-1;
                }
        }
        return ans;
}
	
number of elements less than key	
public static int binarySearchWithUpperBound(int key) {
    int low = 1, high = N, mid, ans = 0;
    while(low ≤ high) {
        mid = (low + high) / 2;
        if(a[mid] < key) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}	
