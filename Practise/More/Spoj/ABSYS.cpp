#include<bits/stdc++.h>
using namespace std;
int main(){
 int t;
 scanf("%d\n",&t);
 while(t--){
  char str1[1000],str2[1000],str3[1000];
  scanf("%s",str1);
  getchar();
  getchar();
  scanf("%s",str2);
  getchar();
  getchar();
  scanf("%s",str3);
  getchar();
  
  
  if(strstr(str1,"machula"))
  {
   int len2=strlen(str2);
   int len3=strlen(str3);
   int num3=0;
   int num2=0,i;
   for(i=0;i<len2;i++)
   num2=10*num2+(str2[i]-'0');
   for(i=0;i<len3;i++)
   num3=10*num3+(str3[i]-'0');
   int ans=num3-num2;
   printf("%d + %s = %s\n",ans,str2,str3);
   continue;
  }
   if(strstr(str2,"machula"))
  {
   int len1=strlen(str1);
   int len3=strlen(str3);
   int num3=0;
   int num1=0,i;
   for(i=0;i<len1;i++)
   num1=10*num1+(str1[i]-'0');
   for(i=0;i<len3;i++)
   num3=10*num3+(str3[i]-'0');
   int ans=num3-num1;
   printf("%s + %d = %s\n",str1,ans,str3);
   continue;
  }
   if(strstr(str3,"machula"))
  {
   int len2=strlen(str2);
   int len1=strlen(str1);
   int num1=0;
   int num2=0,i;
   for(i=0;i<len2;i++)
   num2=10*num2+(str2[i]-'0');
   for(i=0;i<len1;i++)
   num1=10*num1+(str1[i]-'0');
   int ans=num1+num2;
   printf("%s + %s = %d\n",str1,str2,ans);
   continue;
  }
 }
 return 0;
}
