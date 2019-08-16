//mod p 下 1-n的逆元 
//p=k*i+r k*i+r=0(%p) 
// 同乘i^-1*r^-1  k*r^-1+i^-1=0
//i^-1 = -k*r^-1 = - (p/i)*(p mod i)^-1 
rep(i,2,N)
        ifac[i] = mod - mul(ifac[mod % i] , mod / i);
