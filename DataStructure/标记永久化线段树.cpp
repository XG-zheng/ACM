struct segTree{
	ll mx[N<<2],b[N<<2],add[N<<2],sum[N];
	void Build(int l ,int r,int rt){
		add[rt] = 0;
		if(l == r){ mx[rt] = sum[rt] = b[l];return;}
		int m = ( l + r)/2;
		Build(l,m,rt<<1);
		Build(m + 1, r,rt<<1|1);
		mx[rt] = max(mx[rt<<1],mx[rt<<1|1]);
		sum[rt] = sum[rt<<1] + sum[rt<<1|1];
	}
	void update(int L,int R,ll c,int l,int r,int rt){
		sum[rt] += (ll)(min(r,R) - max(l,L) + 1)*c; 
		if( L <= l && r <= R){
			add[rt] += c;
			return ;
		}
		int m = ( l + r)/2;	
		if(L <= m)update(L,R,c,l,m,rt<<1);
		if(R  > m)update(L,R,c,m + 1,r,rt<<1|1);
		mx[rt] = max(mx[rt<<1] + add[rt<<1],mx[rt<<1|1] + add[rt<<1|1]);
	}
	ll qryMax(int L,int R,int l ,int r,int rt){
		if(L <= l && r <= R){
			return mx[rt] + add[rt];
		}
		int m = ( l + r)/2;
		ll ans = -1e18;
		if(L <= m )ans = max(ans,qryMax(L,R,l,m,rt<<1));
		if(R  > m )ans = max(ans,qryMax(L,R,m + 1,r,rt<<1|1));
		return ans + add[rt];
	}
	ll qrySum(int L,int R,int l ,int r,int rt){
		if(L <= l && r <= R){
			return sum[rt];
		}
		int m = ( l + r)/2;
		ll ans = 0;
		if(L <= m )ans += qrySum(L,R,l,m,rt<<1);
		if(R  > m )ans += qrySum(L,R,m + 1,r,rt<<1|1);
		return ans + (ll)(min(r,R) - max(l,L) + 1)*add[rt];
	}
}sg;
