#include <bits/stdc++.h>
using namespace std;
int a, b, c, d[10000], n;
void pointUpdate(int id, int val){
 while(id <= n) d[id] += val, id += (id & (-id));
}
int rangeQuery(int id, int ans){
 while(id > 0) ans += d[id], id -= (id & (-id));
 return ans;
}

void rangeUpdate(int start, int finish, int val)
{
 pointUpdate(start, val);
 pointUpdate(finish + 1, -val);
}

int main()
{
 cin >> n;
 for(int i = 0 ; i < n ; i++) cin >> a >> b >> c, rangeUpdate(a, b, c);

 while(cin >> a) cout << rangeQuery(a, 0) << endl;

 return 0;
}
