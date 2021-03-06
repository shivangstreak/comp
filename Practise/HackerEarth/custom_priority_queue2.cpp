#include<bits/stdc++.h> // Priority_queue...
using namespace std;
struct node{
	int i,j;
	node(int i1,int j1){
		i=i1;
		j=j1;
	}
};
bool operator<(const node &a,const node &b){
	//return a.j>b.j;  // For min heap
	return a.i<b.i;  //For max Heap
}
/*class cmp{
	public:
		bool operator()(const struct node &t1,const struct node &t2){
			return t1.i>t2.i;  // MinHeap on bases of i....
		//	return t1.j>t2.j;  // MaxHeap on bases of j....
		}
};*/
int main(){
	//priority_queue<node,vector<node>,cmp>q;
	priority_queue<node>q;
	q.push(node(4,7));
	q.push(node(8,3));
	while(q.empty()==false){
		cout<<q.top().i<<" "<<q.top().j<<"\n";
		q.pop();
	}
	return 0;
}
