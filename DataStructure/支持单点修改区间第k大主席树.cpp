const int N=2e6+5;
struct node{
	int l,r,sum;
	node(){sum = 0;};
};
struct ZXT{
	const static int N = 2e7 + 5;
	node T[N];
	int tot = 0,n,rt[N],ql[N],qr[N],cnt1,cnt2;	
	void ini(int _n){n = _n;}; 
	void upd(int &x,int pos,int c,int l,int r){
		if(!x)x = ++tot;
		T[x].sum += c;
		if(l == r)return;
		int mid = (l + r)/2;
		if(pos <= mid)upd(T[x].l,pos,c,l,mid);
		else upd(T[x].r,pos,c,mid + 1,r);
	}
	//c == 1,add,a[pos] = val
	//c == -1,delete,a[pos] = val
	void add(int pos,int c,int val){
		for(int i = pos;i <= n; i += lowbit(i)){
			upd(rt[i],val,c,1,n); 
		}
	}
	int solve(int l,int r,int k){
		if(l == r)return l;
		int mid = ( l + r)/2 ,cur = 0;
		rep(i , 1 , cnt1 + 1)cur -= T[T[ql[i]].l].sum;
		rep(i , 1 , cnt2 + 1)cur += T[T[qr[i]].l].sum;
		if(cur >= k){
			rep(i , 1 , cnt1 + 1)ql[i] = T[ql[i]].l;
			rep(i , 1 , cnt2 + 1)qr[i] = T[qr[i]].l;
			return solve(l , mid , k);
		}
		else{
			rep(i , 1 , cnt1 + 1)ql[i] = T[ql[i]].r;
			rep(i , 1 , cnt2 + 1)qr[i] = T[qr[i]].r;
			return solve(mid + 1,r,k - cur);
		}
	}
	int qry(int l,int r,int k){
		cnt1 = 0,cnt2 = 0;
		for(int i = l - 1;i > 0;i -= lowbit(i))ql[++cnt1] = rt[i];
		for(int i = r;i > 0;i -= lowbit(i))qr[++cnt2] = rt[i];
		return solve(1,n,k);
	}
}seg;
int n,m;
int op[N],l[N],r[N],k[N],a[N];
vi p;
int main()
{
	cin>>n>>m;
	rep(i ,1 ,n + 1)cin>>a[i],p.pb(a[i]);
	char c;
	rep(i ,1 , m + 1){
		cin>>c>>l[i]>>r[i];
		if(c == 'Q'){
			op[i] = 1;
			cin>>k[i];
		}
		else p.pb(r[i]);
	}
	sort(all(p));
	p.erase(unique(all(p)),p.end());
	seg.ini(sz(p) + 2);
	rep(i ,1 , n + 1){
		a[i] = lower_bound(all(p),a[i]) - p.begin() + 1;
		seg.add(i,1,a[i]);
	}	
	rep(i ,1 , m + 1){
		if(op[i]){
			//qry [l[i],r[i]] 
			cout<<p[seg.qry(l[i],r[i],k[i]) - 1]<<"\n";
		}
		else{
			//upd a[l[i]] = r[i]; 
			r[i] = lower_bound(all(p),r[i]) - p.begin() + 1;
			seg.add(l[i],-1,a[l[i]]);
			a[l[i]] = r[i];
			seg.add(l[i],1,a[l[i]]);
		}
	}
	return 0;
}
