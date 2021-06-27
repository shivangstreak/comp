#include <iostream> // O(n^2) O(1) space
using namespace std;
string str;
int main() {
	int t;cin>>t;
	while(t--){
	    cin>>str;
        int mx=1;
        int ind=0,low,high;
        int len=str.size();
        for(int i=1;i<len;i++){
            // pal with even length
            low=i-1; 
            high=i;
    while(low>=0 && low<len && high>=0 && high<len && str[low]==str[high]){
                if(high-low+1>mx){
                    ind=low;
                    mx=high-low+1;
                }
                low--;
                high++;
            }
    low=i-1;
    high=i+1;
     while(low>=0 && low<len && high>=0 && high<len && str[low]==str[high]){
                if(high-low+1>mx){
                    ind=low;
                    mx=high-low+1;
                }
                low--;
                high++;
            }   
        }
        cout<<str.substr(ind,mx)<<endl;
	}
	return 0;
}
