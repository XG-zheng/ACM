const int N=1e5+5;
vi V;
int rk(int x){return lower_bound(all(V),x)-V.begin()+1;};
int cnt=0,n,m,a[N],rt[N];
struct node{
	int l,r,sum;
	node(){sum=0;};
}T[N*50];
void update(int l,int r,int pos,int &x,int y){
	T[++cnt]=T[y],T[cnt].sum++,x=cnt;
	if(l==r)return;
	int mid = (l+r)/2;
	if(mid>=pos)update(l,mid,pos,T[x].l,T[y].l);
	else update(mid+1,r,pos,T[x].r,T[y].r);
}
int qry(int x,int y,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)/2;
	int sum=T[T[y].l].sum-T[T[x].l].sum;
	if(sum>=k)return qry(T[x].l,T[y].l,l,mid,k);
	else return qry(T[x].r,T[y].r,mid+1,r,k-sum);
} 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		V.pb(a[i]);
	}
	sort(all(V));
	V.erase(unique(all(V)),V.end());
	for(int i=1;i<=n;++i){
		update(1,n,rk(a[i]),rt[i],rt[i-1]);
	}
	for(int i=1;i<=m;++i){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",V[qry(rt[l-1],rt[r],1,n,k)-1]);
	}
	return 0;
}

