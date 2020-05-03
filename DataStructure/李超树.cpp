struct Line{
	ll k,b;
	Line(ll k = 0,ll b = 0):k(k),b(b){}
	ll f(int pos){return k*pos + b;} 
};
struct Seg{
	static const int N = ::N << 2;
	Line mx[N],mn[N];
	void _max(Line cur,int l,int r,int rt){
		int m = (l + r)/2;
		if(cur.f(m) > mx[rt].f(m))swap(mx[rt],cur);
		if(l == r || min(mx[rt].f(l),mx[rt].f(r)) >= max(cur.f(l),cur.f(r)))return;
		if(mx[rt].f(l) < cur.f(l))_max(cur,l , m , rt<<1);
		else _max(cur , m + 1,r,rt<<1|1);
	}
	void _min(Line cur,int l,int r,int rt){
		int m = (l + r)/2;
		if(cur.f(m) < mn[rt].f(m))swap(mn[rt],cur);
		if(l == r || max(mn[rt].f(l),mn[rt].f(r)) <= min(cur.f(l),cur.f(r)))return;
		if(mn[rt].f(l) > cur.f(l))_min(cur,l , m , rt<<1);
		else _min(cur , m + 1,r,rt<<1|1);
	}
	void upd(Line c,int L,int R,int l,int r,int rt){
		if(L > R)return;
		if(L <= l && r <= R){
		//	_max(c,l ,r , rt);
			_min(c,l ,r , rt);
			return ;
		}
		int m = (l + r)/2;
		if(L <= m)upd(c,L,R,l,m,rt<<1);
		if(R > m)upd(c,L,R,m + 1,r,rt<<1|1);
	}
	ll qry(int pos,int l,int r,int  rt){
		ll ans = mn[rt].f(pos);
		if(l == r)return ans;
		int m = (l + r)/2;
		if(pos <= m)ans = min(ans,qry(pos,l , m ,rt<<1));
		else ans = min(ans,qry(pos,m + 1,r,rt<<1|1));
		return ans;
	}
}sg;
