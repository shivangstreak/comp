#include <bits/stdc++.h>
using namespace std;

int a, b, c, n;

class BIT
{
public:
    int d[100000];

    void pointUpdate(int id, int val)
    {
        while(id <= n) d[id] += val, id += (id & (-id));
    }
    int rangeQuery(int id, int ans)
    {
        while(id > 0) ans += d[id], id -= (id & (-id));
        return ans;
    }
    void rangeUpdate(int start, int finish, int val)
    {
        pointUpdate(start, val);
        pointUpdate(finish + 1, -val);
    }
};

class UltraBIT
{
public:
    BIT bit1, bit2;
    void rangeUpdate(int start, int finish, int val)
    {
        bit1.rangeUpdate(start, finish, val);
        bit2.pointUpdate(start, val*(start - 1));
        bit2.pointUpdate(finish + 1, -val*finish);
    }
    int rangeQuery(int id)
    {
	cout<<" bit1.rangeQuery(id, 0) "<<bit1.rangeQuery(id, 0)<<" id "<<id<<" bit1.rangeQuery(id, 0) * id "<<bit1.rangeQuery(id, 0) * id<<" bit2.rangeQuery(id, 0) "<<bit2.rangeQuery(id, 0)<<"\n";
        return bit1.rangeQuery(id, 0) * id - bit2.rangeQuery(id, 0);
    }
};
int main()
{
    cin >> n;
    UltraBIT Bit;

    for(int i = 0 ; i < n ; i++) cin >> a >> b >> c, Bit.rangeUpdate(a, b, c);

    while (cin >> a) cout << Bit.rangeQuery(a)<<endl;
    return 0;
}
