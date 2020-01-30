struct segTree{
	ll mx[N<<2],b[N<<2],add[N<<2];
	void Build(int l ,int r,int rt){
		add[rt] = mx[rt] = 0;
		if(l == r){return;}
		int m = ( l + r)/2;
		Build(l,m,rt<<1);
		Build(m + 1, r,rt<<1|1);
	}
	void update(int L,int R,ll c,int l,int r,int rt){
		if( L <= l && r <= R){
			add[rt] += c;
			return ;
		}
		int m = ( l + r)/2;	
		if(L <= m)update(L,R,c,l,m,rt<<1);
		if(R  > m)update(L,R,c,m + 1,r,rt<<1|1);
		mx[rt] = max(mx[rt<<1] + add[rt<<1],mx[rt<<1|1] + add[rt<<1|1]);
	}
	ll qry(ll L,ll R,int l ,int r,int rt){
		if(L <= l && r <= R){
			return mx[rt] + add[rt];
		}
		int m = ( l + r)/2;
		ll ans = -1e18;
		if(L <= m )ans = max(ans,qry(L,R,l,m,rt<<1));
		if(R  > m )ans = max(ans,qry(L,R,m + 1,r,rt<<1|1));
		return ans + add[rt];
	}
};
