int ls[N],rs[N],rt[N],mn[N],cnt;
void update(int &u,int l,int r,int pos,int val){
	if(!u)u=++cnt;
	mn[u]=min(mn[u],val);
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos <= mid)update(ls[u],l,mid,pos,val);
	else update(rs[u],mid+1,r,pos,val);
}
int qry(int L,int R,int l,int r,int u){
	if(!u)return 2e9;
	if(L <= l && r <= R)
		return mn[u];
	int mid=(l+r)>>1;
	int ans=2e9;
	if(L <= mid) ans = min(ans,qry(L,R,l,mid,ls[u]));
	if(R > mid)ans = min(ans,qry(L,R,mid+1,r,rs[u]));
	return ans; 
}
int merge(int u,int v,int l,int r){
	if(!u)return v;
	if(!v)return u;
	int t=++cnt;
	mn[t]=min(mn[u],mn[v]);
	if(l == r)
		return t;
	int mid = (l + r) >> 1;
	ls[t]=merge(ls[u],ls[v],l,mid);
	rs[t]=merge(rs[u],rs[v],mid+1,r);
	return t;
}
