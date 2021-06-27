#include<bits/stdc++.h>
using namespace std;
char D[105][105];
int visited[105][105],w,h,flag=0;
struct node{
    int x,y;
    int m;
    int dir;
    node() {x=y=m=dir=-1;}
    node(int x1,int y1,int m1,int d1) {x=x1; y=y1; m=m1; dir=d1;}
};
bool checkBound(node temp){
    if(temp.x>=0 && temp.x<h && temp.y>=0 && temp.y<w && D[temp.x][temp.y]!='*')
        return true;
    return false;
}
 
int bfs(node s1){
    int result=1000000;
    queue<node>q;   
    q.push(s1);
    node temp,top;
    memset(visited,1000000,sizeof(visited));
    while(!q.empty()){
        top=q.front();
        q.pop();
        if(checkBound(top)==false)
            continue;
        if(D[top.x][top.y]=='T' && top.m<result){
            result=top.m;
            continue;
        }
        if(top.m <= visited[top.x][top.y])
            visited[top.x][top.y]=top.m;
        else
            continue;
        int x=top.x;
        int y=top.y;
        int m=top.m;
        int d=top.dir;
        
        if(d==0)
        {
            q.push( node(x-1,y,m+1,1) );
            q.push( node(x,y+1,m+1,2) );
            q.push( node(x+1,y,m+1,3) );
            q.push( node(x,y-1,m+1,4) );
        }
        else if(d==1)
        {
            q.push( node(x-1,y,m,1) );
            q.push( node(x,y-1,m+1,4) );
            q.push( node(x,y+1,m+1,2) );
        }
        else if(d==2)
        {
            q.push( node(x-1,y,m+1,1) );
            q.push( node(x,y+1,m,2) );
            q.push( node(x+1,y,m+1,3) );
        }
        else if(d==3)
        {
            q.push( node(x,y+1,m+1,2) );
            q.push( node(x+1,y,m,3) );
            q.push( node(x,y-1,m+1,4) );
        }
        else if(d==4)
        {
            q.push( node(x+1,y,m+1,3) );
            q.push( node(x,y-1,m,4) );
            q.push( node(x-1,y,m+1,1) );
        }
    }
    return result;
}
 
int main()
{
    node temp;
    cin>>w>>h;
    for(int i=0;i<h;i++)
    {
    	cin>>D[i];
		for(int j=0;j<w;j++)
        {
            if(D[i][j]=='C')
            {
                if(!flag)
                {
                    flag=1;
                    temp.x=i;
                    temp.y=j;
                    temp.m=-1;
                    temp.dir=0;
                }
                else
                    D[i][j]='T';
            }
        }
    	
        /*for(int j=0;j<w;j++)
        {
            cin>>D[i][j];
            if(D[i][j]=='C')
            {
                if(!flag)
                {
                    flag=1;
                    temp.x=i;
                    temp.y=j;
                    temp.m=-1;
                    temp.dir=0;
                }
                else
                    D[i][j]='T';
            }
        }*/
    }
    flag=0;
    int res=bfs(temp);
    cout<<res;
}
