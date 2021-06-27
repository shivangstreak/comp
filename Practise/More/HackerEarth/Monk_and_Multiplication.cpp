#include <bits/stdc++.h>
using namespace std;
class maxHeap{
	int heap_size;
	int cap;
	vector<int>heap;
	public:
		int parent(int i){return (i-1)/2;}
		int right(int i){return 2*i+2;}
		int left(int i){return 2*i+1;}
		maxHeap(int i){
			heap.resize(i);
			cap=i;
			heap_size=0;
		}
		void insertKey(int i){
			heap_size++;
			int j=heap_size-1;
			heap[j]=i;
			while(j!=0 && heap[parent(j)]<heap[j]){
				swap(heap[parent(j)],heap[j]);
				j=parent(j);
			}
		}
		void heapify(int i){
			int m=i;
			int l=left(i);
			int r=right(i);
			if(l<heap_size && heap[l]>heap[m]){
				m=l;
			}
			if(r<heap_size && heap[r]>heap[m]){
				m=r;
			}
			if(m!=i){
				swap(heap[m],heap[i]);
				heapify(m);
			}
		}
		int extractMax(){
			if(heap_size<=0){
				return INT_MAX;
			}
			if (heap_size == 1){
       	 		heap_size--;
        		return heap[0];
    		}
			int root=heap[0];
			heap[0]=heap[heap_size-1];
			heap_size--;
			heapify(0);	
			return root;		
		}
};
int main(){
    int n;scanf("%d",&n);
    vector<int>v;
    for(int i=0;i<n;i++){
    	int d;scanf("%d",&d);
    	v.push_back(d);
    }
    if(n>2){
    	printf("-1\n-1\n");
    	for(int i=2;i<n;i++){
    		maxHeap H(i);
    		for(int j=0;j<=i;j++){
    			H.insertKey(v[j]);
    		}
    		int pro=1;
    		for(int i=0;i<3;i++){
    			int o=H.extractMax();
    			pro*=o;
    		}
    		printf("%d\n",pro);
    	}    	
    }
    else{
    	for(int i=0;i<n;i++){
    		printf("-1\n");
    	}
    }
    return 0;
}

