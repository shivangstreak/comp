    #include<bits/stdc++.h>
    using namespace std;
    #define pb push_back
    #define ll long long int
    #define II pair<int,int>
    #define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
    const int N=1e5+5;
    struct node{
    	int heads;
    	node(){
    		heads=0;
    	}
    }segTree[4*N];
    int lazy[4*N];
    void buildTree(int pos,int start,int end){
    	if(start>end)
    		return;
    	if(start==end){
    		segTree[start].heads=0;
    	}	
    	int mid=start+(end-start)>>1;
    	buildTree(2*pos+1,start,mid);
    	buildTree(2*pos+2,mid+1,end);
    }
    void update(int pos,int start,int end,int l,int r){
    	if(start>end){
    		return;
    	}
    	if(lazy[pos]==1){
    		segTree[pos].heads=(end-start+1)-segTree[pos].heads;
    		if(start!=end){
    			lazy[2*pos+1]=lazy[2*pos+1]^1;
    			lazy[2*pos+2]=lazy[2*pos+2]^1;			
    		}
    		lazy[pos]=0;
    	}
    	if(start>r || end<l){
    		return;
    	}
    	if(l<=start && end<=r){
    		segTree[pos].heads=(end-start+1)-segTree[pos].heads;
    		if(start!=end){
    			lazy[2*pos+1]=lazy[2*pos+1]^1;
    			lazy[2*pos+2]=lazy[2*pos+2]^1;			
    		}
    		return;
    	}
    	int mid=start+((end-start)>>1);
    	update(2*pos+1,start,mid,l,r);
    	update(2*pos+2,mid+1,end,l,r);
    	segTree[pos].heads=segTree[2*pos+1].heads+segTree[2*pos+2].heads;	
    }
    int query(int pos,int start,int end,int l,int r){
    	if(start>end){
    		return 0;
    	}
    	if(lazy[pos]==1){
    		segTree[pos].heads=(end-start+1)-segTree[pos].heads;
    		if(start!=end){
    			lazy[2*pos+1]=lazy[2*pos+1]^1;
    			lazy[2*pos+2]=lazy[2*pos+2]^1;
    		}
    		lazy[pos]=0;
    	}
    	if(start>r || end<l){
    		return 0;
    	}
    	if(l<=start && end<=r){
    		return segTree[pos].heads;
    	}
    	int mid=start+((end-start)>>1);
    	int sum=0;
    	sum+=query(2*pos+1,start,mid,l,r);
    	sum+=query(2*pos+2,mid+1,end,l,r);
    	return sum;	
    }
    int main(){
    	faster;
    	int d,l,r,n,q;cin>>n>>q;
    	while(q--){
    		cin>>d>>l>>r;
    		if(d==0){
    			update(0,0,n-1,l,r);
    		}
    		else{
    			cout<<query(0,0,n-1,l,r)<<"\n";						
    		}
    	}
    	return 0;
    } 
