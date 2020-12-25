const int N = 5e5 + 5;
const int inf = 0x3f3f3f3f;
struct node{
	ll sum;
	int mx,sx,cntx,tagx,mn,sn,cntn,len,tagn,add;
	inline void init(int val){sum = mx = mn = val,sx = -inf,sn = inf,cntx = cntn = 1;}
	inline void _add(const int x){sum += (ll)x*len;mx += x,sx += x,mn += x,sn += x;add += x;}
	inline void _max(const int x){
		sum += (ll)cntn*x;(mx == mn)&&(mx += x),(sx == mn) && (sx += x);
		mn += x;tagn += x;
	}
	inline void _min(const int x){
		sum+= (ll)cntx*x;(mn == mx)&&(mn += x),(sn == mx) && (sn += x);
		mx += x,tagx += x;
	}
	inline void pu(const node &lc,const node & rc){
		sum = lc.sum + rc.sum;mn = min(lc.mn,rc.mn),mx = max(lc.mx,rc.mx);
		cntn = 0,(mn == lc.mn) && (cntn += lc.cntn),(mn == rc.mn) && (cntn += rc.cntn);
		cntx = 0,(mx == lc.mx) && (cntx += lc.cntx),(mx == rc.mx) && (cntx += rc.cntx);
		sn = min(lc.sn,rc.sn),(lc.mn > mn) && (sn = min(sn,lc.mn)),(rc.mn > mn) && (sn = min(sn,rc.mn));
		sx = max(lc.sx,rc.sx),(lc.mx < mx) && (sx = max(sx,lc.mx)),(rc.mx < mx) && (sx = max(sx,rc.mx));
	}
}t[N<<2];
void build(int *a,int l,int r,int rt){
	t[rt].len = r - l + 1;t[rt].tagn = t[rt].tagx = t[rt].add = 0;
	if(l == r){
		t[rt].init(a[l]);
		return;
	}
	int m = l + r>>1;
	build(a , l , m , rt<<1);
	build(a , m + 1, r  , rt<<1|1);
	t[rt].pu(t[rt<<1],t[rt<<1|1]);
}
inline void pd(int rt){
	if(t[rt].add){
		t[rt<<1]._add(t[rt].add),t[rt<<1|1]._add(t[rt].add);
		t[rt].add = 0;
	}
	if(t[rt].tagn){
		if(t[rt<<1].mn <= t[rt<<1|1].mn)t[rt<<1]._max(t[rt].tagn);
		if(t[rt<<1|1].mn <= t[rt<<1].mn)t[rt<<1|1]._max(t[rt].tagn);
		t[rt].tagn = 0;
	}
	if(t[rt].tagx){
		if(t[rt<<1].mx >= t[rt<<1|1].mx)t[rt<<1]._min(t[rt].tagx);
		if(t[rt<<1|1].mx >= t[rt<<1].mx)t[rt<<1|1]._min(t[rt].tagx);
		t[rt].tagx = 0;
	}
}
// a[i] += x
void add(int L,int R,int x,int l,int r,int rt){
	if(L <= l && r <= R){
		t[rt]._add(x);return;
	}
	int m = l + r>>1;
	pd(rt);
	if(L <= m)add(L ,R,x,l , m , rt<<1);
	if(R > m)add(L,R,x,m + 1, r,rt<<1|1);
	t[rt].pu(t[rt<<1],t[rt<<1|1]);
}
// a[i] = max(a[i] , x)
void _MAX(int L,int R,int x,int l,int r,int rt){
	if(x <= t[rt].mn)return;
	if(L <= l && r <= R && x < t[rt].sn){
		t[rt]._max(x - t[rt].mn);
	}
	else{
		int m = l + r>>1;
		pd(rt);
		if(L <= m)_MAX(L ,R ,x , l , m , rt<<1);
		if(R > m)_MAX(L,R,x,m + 1 , r , rt<<1|1);
		t[rt].pu(t[rt<<1],t[rt<<1|1]); 
	}
}
// a]i] = min(a[i] , x) 
void _MIN(int L,int R,int x,int l,int r,int rt){
	if(x >= t[rt].mx)return;
	if(L <= l && r <= R && x > t[rt].sx){
		t[rt]._min(x - t[rt].mx);
	}
	else{
		int m = l + r>>1;
		pd(rt);
		if(L <= m)_MIN(L ,R ,x , l , m , rt<<1);
		if(R > m)_MIN(L,R,x,m + 1 , r , rt<<1|1);
		t[rt].pu(t[rt<<1],t[rt<<1|1]); 
	}
}
ll qrySum(int L,int R,int l,int r,int rt){
	if(L <= l && r <= R)return t[rt].sum;
	int m = l + r>>1;
	pd(rt);
	ll ans = 0;
	if(L <= m)ans += qrySum(L,R,l,m,rt<<1);
	if(R > m)ans += qrySum(L,R,m + 1,r,rt<<1|1);
	return ans;
}
int qryMin(int L,int R,int l,int r,int rt){
	if(L <= l && r <= R)return t[rt].mn;
	int m = l + r>>1;
	pd(rt);
	int ans = inf;
	if(L <= m)ans = qryMin(L,R,l,m,rt<<1);
	if(R > m)ans = min(ans,qryMin(L,R,m + 1,r,rt<<1|1));
	return ans;
}
int qryMax(int L,int R,int l,int r,int rt){
	if(L <= l && r <= R)return t[rt].mx;
	int m = l + r>>1;
	pd(rt);
	int ans = -inf;
	if(L <= m)ans = qryMax(L,R,l,m,rt<<1);
	if(R > m)ans = max(ans,qryMax(L,R,m + 1,r,rt<<1|1));
	return ans;
}
