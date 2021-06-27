#include<bits/stdc++.h> // This generates all the prime numbers upto n
using namespace std;
bool isPrime(int a){  // Use this to chk if a number is prime or not....
	if(a<=3){
		if(a>1)
			return true;
		else
			return false;	
	}
	if(a%2==0||a%3==0)
		return false;
	else{
		for(int i=5;i*i<a;i+=6){
			if(a%i==0)
				return false;
		}
		return true;
	}	
}
int main(){
	bool a[100]; // Here n=100
	memset(a,true,sizeof(a));
	a[0]=false;a[1]=false;
	for(int j=2;j<sqrt(100);j++){
		if(a[j]==true){
			for(int k=j*j;k<100;k+=j){
				a[k]=false;
			}
		}	
	}
	for(int i=0;i<100;i++){
		if(a[i]==true)
			cout<<i<<"\n";
	}
	return 0;
}
std::vector<bool> sieve(int largest)
{
    std::vector<bool> is_prime(largest+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= largest; ++i) {
        if (is_prime[i]) {
            for (int j = 2*i; j <= largest; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}
   memset(prm,1,sizeof(prm));
     prm[1]=0;
     prm[0]=0;
     for (int i=2;i<=1200000;i++){
          if (!prm[i]) continue;
          prm[i]=1;
          for (int j=2;j*i<1200000;j++) prm[i*j]=0;
     }
 bool isprime(int a)
{
    if(a % 2 == 0) return false  ;
    else
    {
        for(int j = 3 ; j <= a / 2 ; j ++)
        {
            if( a % j == 0)
            {
                return false ;
            }
        }
        return true ;
    }
}    

bool isPrime(int n) {   // O(sqrt(N))
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void sieve()
{
    for(int i=2;i<=100;i++)
    {
        if(!check[i])
        {
            for(int j=i*i;j<=10000;j+=i)
                check[j] = true;
        }
    }
}
