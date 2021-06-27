#include <cstdio> // Range Update Range Query!!
#include <cstring>
#define LSOne(S) (S & (-S))
using namespace std;
typedef long long ll;
// B1 and B2 are two fenwick trees
// Original array entries are assumed to be 0
// and only updates are stored.
ll B1[100005], B2[100005];
// Array size
int N;
// Point query
// Returns value at position b in the array for ft = B1
// Returns value to be subtracted from query(B1, b) * b for ft = B2
ll query(ll* ft, int b) {
	ll sum = 0;
	for (; b; b -= LSOne(b))
	 sum += ft[b];
	return sum;
}
// Range query: Returns the sum of all elements in [1...b]
ll query(int b) {
	return query(B1, b) * b - query(B2, b);
}
// Range query: Returns the sum of all elements in [i...j]
ll range_query(int i, int j) {
	return query(j) - query(i - 1);
}
// Point update: Adds v to the value at position k in the array
// ft is the fenwick tree which represents that array
void update(ll* ft, int k, ll v) {
	for (; k <= N; k += LSOne(k)) ft[k] += v;
}
// Range update: Adds v to each element in [i...j]
void range_update(int i, int j, ll v) {
	update(B1, i, v);
	update(B1, j + 1, -v);
	update(B2, i, v * (i - 1));
	update(B2, j + 1, -v * j);
}
int main() {
	int T, C, p, q, cmd;
	ll v;
	scanf("%d", &T);
	while (T--) {
		// C -> No. of operations
		scanf("%d %d", &N, &C);
		memset(B1, 0, (N+1) * sizeof(ll));
		memset(B2, 0, (N+1) * sizeof(ll));
		while (C--) {
			scanf("%d %d %d", &cmd, &p, &q);
			// cmd is 0 for a range update and 1 for a range query
			if (cmd == 0) {
				scanf("%lld", &v);
				range_update(p, q, v);
			} 
			else
				printf("%lld\n", range_query(p, q));
		}
	}
return 0;
}

/*
Explanation:

BIT B1 is used like in the earlier case with range updates/point queries such that query(B1, p) gives A[p].

Consider a range update query: Add v to [a…b]. Let all elements initially be 0. Now, Sum(1…p) for different p is as follows:

    1 <= p < a : 0
    a <= p <= b : v * (p – (a – 1))
    b < p <= N : v * (b – (a – 1))

Thus, for a given index p, we can find Sum(1…p) by subtracting a value X from p * Sum(p,p) (Sum(p,p) is the actual value stored at index p) such that

    1 <= p < a : Sum(1..p) = 0, X = 0
    a <= p <= b : Sum(1…p) = (v * p) – (v * (a-1)), X = v * (a-1)
    b < p <= N: Sum(1…p) = (v * b) – (v * (a-1)), X = -(v * b) + (v * (a-1))

To maintain this extra factor X, we use another BIT B2 such that

    Add v to [a…b] -> Update(B2, a, v * (a-1)) and Update(B2, b+1, -v * b)
    Query(B2, p) gives the value X that must be subtracted from A[p] * p

*/
