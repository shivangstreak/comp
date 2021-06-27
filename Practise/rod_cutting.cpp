typedef long long int ll; // cut rod at geven places so cost of cutting is min
vector<int>ans;
vector<vector<ll>>parent;
vector<vector<ll>>dp;
vector<int>cuts;
void build(ll l,ll r){
    if(l+1>=r)
        return;
    ans.push_back(cuts[parent[l][r]]);
    build(l,parent[l][r]);
    build(parent[l][r],r);
}
ll rec(ll l,ll r){
    if(l+1>=r)
        return 0;
    if(dp[l][r]!=-1)
        return dp[l][r];
    int bestIndx;
    ll mi=INT_MAX;
    for(int i=l+1;i<r;i++){
        ll p=rec(l,i)+rec(i,r)+(ll)cuts[r]-(ll)cuts[l];
        if(p<mi){
            mi=p;
            bestIndx=i;
        }
    }
    dp[l][r]=mi;
    parent[l][r]=bestIndx;
    return dp[l][r];
}
vector<int> Solution::rodCut(int A, vector<int> &B) {
        B.push_back(A);
        B.insert(B.begin(),0);
        int n=B.size();
        cuts.clear();
    for(int j=0;j<n;j++)
        cuts.push_back(B[j]);
    dp.clear();
    parent.clear();
    dp.resize(n);
    parent.resize(n);
    ans.clear();
    for(int i=0; i<n; i++){
        dp[i].resize(n);
        parent[i].resize(n);
        for(int j=0; j<n; j++)
            dp[i][j]=-1;
    }        
       ll best= rec(0,n-1);
        build(0,n-1);
    
        return ans;
}

