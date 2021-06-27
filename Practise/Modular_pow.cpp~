ll Modified_pow(ll x,ll y){ //Reccursive
	if(y==0)
		return 1;
	ll result=Modified_pow(x,y>>1);
	result=(result *result)%MOD;
	if(y&1)
		result=(result *x)%MOD;
	return result;		
}

ll Modified_pow(ll x,ll y){  //Iteartive
        ll res=1;
        while(y>0){
                if(y&1){
                        res*=x;
                        res%=MOD;        
                }
                x*=x;
                x%=MOD;
                y>>=1;
        }
        return res;
}
