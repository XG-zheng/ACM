int n , m;
vi g[N];
int low[N],dfn[N],fa[N];
int f[N][2];
void solve(int v,int u){
	int x = f[v][1] , y = f[v][0];
	int now = fa[v];
	while(now != u){
		int nx = f[now][1] + y;
		int ny = max(x,y) + f[now][0];
		x = nx,y = ny;
		now = fa[now];
	}
	f[u][0] += max(x,y);
	x = 0 , y = f[v][0];
	now = fa[v];
	while(now != u){
		int nx = f[now][1] + y;
		int ny = max(x,y) + f[now][0];
		x = nx,y = ny;
		now = fa[now];
	}
	f[u][1] += y;
}
int tot;
void dfs(int u,int p){ 
	low[u] = dfn[u] = ++tot;fa[u] = p;
	f[u][1] = 1;
	for(auto v:g[u]){
		if(v == p)continue;
		if(!dfn[v])dfs(v , u);
		else low[u] = min(low[u] , dfn[v]);
		if(low[u] > dfn[v]){
			f[u][1] += f[v][0],f[u][0] += max(f[v][0],f[u][0]);
		}
	}
	for(auto v:g[u]){
		if(fa[v] != u && dfn[u] < dfn[v]){ 
			solve(v,u);
		}
	}	
}
