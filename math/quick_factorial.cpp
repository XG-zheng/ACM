// F(n)=n!=1*2*3*....*n=(1*3*5*7*9*....)*(2*4*6*8*....)=(1*3*5*7*9*....)*(2^{(x/2)}*F(x/2)) 
//��mod (2^32) ������Ƚ����е�2��ȡ����������ģ�����ƴ��� 
 //���߷ֿ���Ԥ�����Ұ�ߵݹ鴦��
 // ����C_{n}^{k} 
const int N=2e6+5;
const ll mod=(1ll<<32ll);
const ll len=(1ll<<22);		//��Ĵ�С 
const ll sec=3862953985;    //mod=(2^32) �Ƚ����⣬ÿ���ֵ������ͬ�� ==sec 
const ll alp=2147483648;  //euler(mod) 
ll n,k;
ll cnt=0;
ll qpow(ll x,ll n){
	ll res=1;
	while(n){
		if(n&1)res=res*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return res;
}
ll solve(ll x){
	if(x==1 || x==0)return 1ll;
	ll res=1;
	ll y=x%mod;
	res=qpow(sec,y/len);
	for(ll i=y/len*len+1;i<=y;i+=2){
		res=res*i%mod;
	}
	ll t=solve(x/2);
	res=res*t%mod;
	cnt+=x/2;    //��ȡ���е�2���� 
	return res;
}
int main()
{
	cin>>n>>k;
	ll ans=solve(n);
	ll num=cnt;
	cnt=0;
	ll p=solve(k);
	p=p*solve(n-k)%mod;
	if(num-cnt>=32){
		cout<<0<<endl;
		return 0;
	}
	num-=cnt;
	ll inv=qpow(p,alp-1);
	ans=ans*inv%mod;
	ll t=qpow(2,num);
	ans=ans*t%mod;
	cout<<ans<<endl; 
	return 0;
}
