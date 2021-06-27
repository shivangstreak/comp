#include<stdio.h>
#define maxx 100001
__int64 i,j,n,m,k,x,y,a[maxx],l[maxx],r[maxx],d[maxx],cnt[maxx],add[maxx];
int main()
{
    scanf("%I64d%I64d%I64d",&n,&m,&k);
	for(i=1;i<=n;i++)scanf("%I64d",a+i);
	for(i=1;i<=m;i++)scanf("%I64d%I64d%I64d",l+i,r+i,d+i);
	for(i=1;i<=k;i++){
		scanf("%I64d%I64d",&x,&y);
		cnt[x]++;cnt[y+1]--;
	}
	for(i=1;i<=m;i++){
		cnt[i+1]+=cnt[i];
		d[i]=d[i]*cnt[i];
		add[l[i]]+=d[i];
		add[r[i]+1]-=d[i];
	}
	for(i=1;i<n;i++){
		add[i+1]+=add[i];
		printf("%I64d ",a[i]+add[i]);
	}
	printf("%I64d\n",a[n]+add[n]);
	return 0;
}
