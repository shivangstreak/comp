#include<bits/stdc++.h> //O(sqrt(n))
using namespace std; //phi(N) counts the number of integers from 1 to N inclusive that are relatively prime to N.
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n != 1) {
        res -= res / n;
    }
    return res;
}
int main(){
	
	return 0;
}

/*
First let us see the definition of Euler's Totient Function.
Euler's totient function denoted as φ(n), is an arithmetic function that counts the positive integers less than or equal to N that are relatively prime to N.

For this question we need to find the sum of all φ(n) for all i between 1 to N. We see that the constraints are very high and we have multiple test cases, so we would prefer to pre-process all the values in one go so that we can answer each query in O(1) time.

How can we find φ(N) for a single N?
Properties of Euler's Totient Function

    If N is prime then φ(N) = N-1, as all numbers less than N are relatively prime to N.
    If N is prime and k > 0, then φ(Nk) = Nk - Nk-1.
    If x and y are relatively prime, then φ(x.y) = φ(x) x φ(y).

Now we will use these properties to find φ(N) when N is not prime.
N = P1k1.P2k2...Pmkm, where Pi are the prime factors of N.
φ(N) = φ(P1k1).φ(P2k2)...φ(Pmkm)

Let X = P1k1.P2k2...Pm-1km-1
φ(N) = φ(X).φ(Pmkm)
φ(N) = (P1k1 - P1k1-1)(P2k2 - P2k2-1)....(Pmkm - Pmkm-1)
φ(N) = φ(X)(Pmkm(1-(1/Pm)))

Here we see that X will always be less than N thus if we use dynamic programming to solve for φ(N) we will always have the value of φ(X). All that remains is to find Pm and Pmkm.
Pmkm = N/X In order to find Pm we can simply modify the Sieve of Eratosthenes to store the largest prime that divides any number.

for (int i=2; i <= MAX; i++)
    if (prime[i] == 0)
        for (int j = i + i; j < = MAX; j += i)
            prime[j] = i;

If prime[N] is equal to 0, then the N is prime or else it represents the largest prime that divides N. When prime[N] is not equal to 0, we can find X by diving N with prime[N] until N is divisible by prime[N]. Now since we have all the requisites to calculate φ(N) we can do it dynamically by iterating from 1 to N.

Now once we have the values of φ(N) for all possible N, we can simply pre-process the sum till the ith position so that we can answer each query in O(1) after preprocessing of O(N log N).

*/CorpCorp Hackerearth



int tot[size+1]; //global
unsigned long long arr[size+1];

void euler_tot() { //Seive to build the array that stores totient values
    tot[1] = 1;
    for(int i=2; i<size; i++) 
    {
        if(!tot[i]) 
        {
            tot[i] = i-1;
            for(int j=(i<<1); j<=size; j+=i) 
            {
                if(!tot[j]) tot[j] = j;
                tot[j] = tot[j]/i*(i-1);
            }
        }
    }
}


