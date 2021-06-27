#include <bits/stdc++.h> 
using namespace std; 
vector<int> findLastTwo(vector<int>& nums, int index, int n,int target){
    int l = index;
    int r = n-1;
    vector<int> res;
    cout<<"yo3"<<endl;
    cout<<l<<" "<<r<<endl;
    while(l<=r){
        if(l+1<n && nums[l]==nums[l+1]){
            l++;
        }
        if(r-1>index && nums[r-1]==nums[r]){
            r--;
        }
        if(nums[l]+nums[r]<target){
            l++;
        }
        else if(nums[l]+nums[r]>target){
            r--;
        }
        else{
            res.push_back(nums[l]);
            res.push_back(nums[r]);
        }
    }
    for(auto x:res){
        cout<<x<<" ";
    }
    return res;
}
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    int n=nums.size();
    cout<<"yo"<<endl;
    for(int i=0;i<n;i++){
        if(i>0 && nums[i-1]==nums[i]){
            continue;
        }
        vector<int> temp;
        cout<<"yo2"<<endl;
        int target = 0 - nums[i];
        vector<int> temp2 = findLastTwo(nums,i+1,n,target);
        if (temp2.empty()){
            continue;
        }
        cout<<"yo"<<endl;
        temp.push_back(nums[i]);
        temp.push_back(temp2[0]);
        temp.push_back(temp2[1]);
        result.push_back(temp);
        cout<<"yo"<<endl;
    }
    return result;
}
int main() 
{ 
    int n,b;
    cin>>n;
    vector<int> a;
    for(int i=0;i<n;i++){
        cin>>b;
        a.push_back(b);
    }
    sort(a.begin(),a.end());
    for(auto x:a){
        cout<<x<<" ";
    }
    cout<<"\n";
    vector<vector<int>> res = threeSum(a);
    for(auto x: res){
        for(auto y:x){
            cout<<y<<" ";
        }
        cout<<"\n";
    }
    return 0;
}