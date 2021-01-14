const int N = 5e5 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n , m , q ,u[N],v[N],w[N];
ll d[2][N];
bool vis[N];
vector<pii> g[N];
pii pre[N];
void dij(int s,ll d[]){
	rep(i , 1 , n + 1)d[i] = inf,vis[i] = 0;
	d[s] = 0;
	priority_queue<pii> q;
	q.push(pii(0,s));
	while(!q.empty()){
		int u = q.top().se;
		q.pop();
		if(vis[u])continue;
		vis[u] = 1;
		for(auto it:g[u]){
			if(d[u] + w[it.se] < d[it.fi]){
				d[it.fi] = d[u] + w[it.se];
				pre[it.fi] = pii(u , it.se);
				q.push(pii(-d[it.fi],it.fi));
			}
		}
	}
}
int k[N],e[N];
bool used[N],in[N];
vector<ll> ad[N],del[N];
ll mn[N];
int main(){
	scanf("%d%d%d",&n,&m,&q);
	rep(i , 1 , m + 1){	
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
		g[u[i]].pb(pii(v[i],i));
		g[v[i]].pb(pii(u[i],i));
	}
	dij(n , d[1]);
	dij(1 , d[0]);
	vi vec;
	rep(i , 2 , n + 1)used[pre[i].se] = 1;
	pre[1] = pii(0,0);
	for(int i = n;i >= 1;i = pre[i].fi)in[pre[i].se] = 1,vec.pb(i);
	int cnt = 0;
	reverse(all(vec));
	for(auto v:vec)k[v] = ++cnt;
	rep(i , 1 , n + 1){
		if(d[0][i] == inf)continue;
		if(!k[i]){
			int u = i;
			for(;!k[u];u = pre[u].fi);
			for(int v = i;!k[v];v = pre[v].fi)k[v] = k[u];
		}
	}
	rep(i , 1 , m + 1){
		if(used[i])continue;
		int l = k[u[i]] , r = k[v[i]];
		if(l == r)continue;
		if(l > r)swap(u[i],v[i]),swap(l , r);
		ad[l].pb(d[0][u[i]] + w[i] + d[1][v[i]]);
		del[r].pb(d[0][u[i]] + w[i] + d[1][v[i]]);
	}
	multiset<ll> S;
	S.insert(inf);
	rep(i , 1 , cnt){
		for(auto v:del[i])
			S.erase(S.find(v));
		for(auto v:ad[i])
			S.insert(v);
		mn[i] = *(S.begin());
	}
	int x , y;
	while(q--){
		scanf("%d%d",&x,&y);
		ll ans = min(d[0][u[x]] + d[1][v[x]],d[0][v[x]] + d[1][u[x]]) + y;
		if(!in[x]){
			ans = min(ans , d[0][n]);
		}
		else{
			 ans = min(ans, mn[min(k[u[x]],k[v[x]])]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

