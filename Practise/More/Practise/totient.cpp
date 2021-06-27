Description: phi(N) counts the number of integers from 1 to N inclusive that are relatively prime to N.

Implemention: let me remind you that factorization is the way to represent given number as a product of primes. And it's easy to see that for every number such representation is unique. For example:
8 = 23
11 = 11
36 = 22 * 32
935 = 5 * 11 * 17
5136 = 24 * 3 * 107
So, implemention is based on factorization:

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

It works in O(sqrt(N)) time. How to make it faster read further.
