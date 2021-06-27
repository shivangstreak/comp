/*
Kasai construction Algorithm in C++

Kasai's algorithm is pretty easy and works in O(n).

Let's look at the two continuous suffixes in the suffix array. Let their indexes in suffix array be i1 and i1+1. 
If their lcp>0, then if we delete first letter from both of them, we can easily see that new strings will have the same relative order.
Also we can see that lcp of new strings will be exactly lcp-1.

Let's now look at the string which we have got from the ith suffix by deleting its first character. 
Obviously it is some suffix of the string too. Let its index be i2. 
Let's look at the lcp of suffixes i2 and i2+1. We can see that it's lcp will be at least already mentioned lcp-1. 
This is associated with certain properties of lcp array, in particular, that lcp(i,j)=min(lcpi,lcpi+1,...,lcpj-1).

And finally let's make the algorithm based on the mentioned above.
 We will need an additional array rank[n], which will contain the index in the suffix array of the suffix starting in index i.
 Firstly we should calculate the lcp of the suffix with index rank[0].
 Then let's iterate through all suffixes in order in which we meet them in the string and calculate lcp[rank[i]] in naive way,
 																							BUT starting it from lcp[rank[i-1]]-1.
Easy to see that now we have O(n) algorithm because on the each step our lcp is decreasing not more than by 1 
																				(except the case when rank[i]=n-1).
*/

vector<int> kasai(string s, vector<int> sa) //sa is suffix array
{
    int n=s.size(),k=0;
    vector<int> lcp(n,0);
    vector<int> rank(n,0);

    for(int i=0; i<n; i++) rank[sa[i]]=i;

    for(int i=0; i<n; i++, k?k--:0)
    {
        if(rank[i]==n-1) {k=0; continue;}
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]]=k;
    }
    return lcp;
}
