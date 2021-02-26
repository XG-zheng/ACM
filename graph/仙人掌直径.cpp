const int N = 8e5 + 5;
const int inf = 0x3f3f3f3f;
int n , m;
vi g[N];
int low[N],ans,dfn[N],tot,dep[N],fa[N];
int f[N];
int q[N<<1],Q[N<<1];
void solve(int v,int u){
	int len = dep[v] - dep[u] + 1;
	int can = len/2;
	int now = v;
	int cnt = 0;
	while(now != u)q[++cnt] = now,now = fa[now];
	q[++cnt] = u;
	rep(i , 1 , cnt + 1)q[cnt + i] = q[i];
	cnt*=2;
	int l = 1,r = 0;
	rep(i , 1 , cnt + 1){
		if(l <= r && i - Q[l] > can)l++;
		if(l <= r)ans = max(ans , f[q[Q[l]]] + f[q[i]] + i - Q[l]); 
		while(l <= r && f[q[Q[r]]] - Q[r] <= f[q[i]] - i)r--;
		Q[++r] = i; 
	}
	while(v != u){
		f[u] = max(f[u],f[v] + min(len - dep[v] + dep[u],dep[v] - dep[u]));
		v = fa[v];
	}
}
void dfs(int u,int p){
	dep[u] = dep[p] + 1,fa[u] = p;
	low[u] = dfn[u] = ++tot;
	int mx1 = 0,mx2 = 0;
	for(auto v:g[u]){
		if(v == p)continue;
		if(!dfn[v])dfs(v , u);
		low[u] = min(low[u] , low[v]);
		if(low[v] > dfn[u]){
			f[u] = max(f[u] , f[v] + 1);
			ans = max(ans,f[u]);
			if(f[v] + 1 > mx1)mx2 = mx1,mx1 = f[v] + 1;
			else if(f[v] + 1 > mx2)mx2 = f[v] + 1;	
		}
	}
	ans = max(ans,mx1 + mx2);
	for(auto v:g[u]){
		if(fa[v] != u && dfn[v] > dfn[u]){
			solve(v,u);
		}
	}
}


