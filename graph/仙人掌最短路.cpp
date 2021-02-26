const int N = 5e5 + 5;
const int inf = 0x3f3f3f3f;
int n , m , q;
vector<pii> ng[N<<1],g[N];
int fa[N],low[N],dfn[N],dep[N<<1],tot,d[N],dis[N<<1],f[N<<1][20],len[N<<1];
int cnt;
void init(int n){
	cnt = n;tot = 0;
	rep(i , 1 , n + 1)dfn[i] = low[i] = fa[i] = d[i] = 0,g[i].clear();
	rep(i , 1 , 2*n + 1)dis[i] = dep[i] = len[i] = 0,ng[i].clear();
}
void solve(int v,int u,int w){
	int now = ++cnt; 
	len[now] = d[v] - d[u] + w;
	while(v != u){
		int c = min(d[v] - d[u],len[now] + d[u] - d[v]);
		ng[now].pb(pii(v,c)),ng[v].pb(pii(now,c));
		v = fa[v];
	}
	ng[now].pb(pii(u,0)),ng[u].pb(pii(now,0));
}
void dfs(int u,int p){
	fa[u] = p;
	low[u] = dfn[u] = ++tot;
	for(auto it:g[u]){
		int v = it.fi;
		if(v == p)continue;
		if(!dfn[v]){
			d[v] = d[u] + it.se;
			dfs(v , u);
			low[u] = min(low[u],low[v]);
		}
		else low[u] = min(low[u] , dfn[v]);
		if(low[v] > dfn[u]){
			ng[u].pb(pii(v,it.se)),ng[v].pb(pii(u,it.se));
		}
	}
	for(auto it:g[u]){
		int v = it.fi;
		if(fa[v] != u && dfn[v] > dfn[u]){
			solve(v,u,it.se);
		}
	}
}
void dfs1(int u,int p){
	f[u][0] = p;dep[u] = dep[p] + 1;
	rep(i , 1 , 20)f[u][i] = f[f[u][i-1]][i-1];
	for(auto it:ng[u]){
		if(it.fi == p)continue;
		dis[it.fi] = dis[u] + it.se;
		dfs1(it.fi , u);
	}
}
int qry(int u,int v){
	if(dep[u] > dep[v])swap(u,v);
	int x = u , y = v;
	int dd = dep[v] - dep[u];
	rep(i , 0 , 20)if(dd>>i&1)v = f[v][i];
	if(v == u)return dis[y] - dis[x];
	for(int i = 19;i >= 0;--i){
		if(f[u][i] != f[v][i])u = f[u][i],v = f[v][i];
	}
	if(f[u][0] > n){
		int tmp = abs(d[u] - d[v]);
		return dis[x] - dis[u] + dis[y] - dis[v] + min(tmp , len[f[u][0]] - tmp);
	}
	else return dis[y] + dis[x] - 2*dis[f[u][0]];
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	init(n);
	int u , v , w;
	rep(i , 1 , m + 1){
		scanf("%d%d%d",&u,&v,&w);
		g[u].pb(pii(v,w)),g[v].pb(pii(u,w));
	}
	dfs(1,0);
	dfs1(1,0);
	while(q--){
		scanf("%d%d",&u,&v);
		printf("%d\n",qry(u,v));
	}
	return 0;
}

