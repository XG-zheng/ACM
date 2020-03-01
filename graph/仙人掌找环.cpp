//œ…»À’∆’“ª∑ 
vector<pii> g[N];
vi s[N];
int fa[N],w[N],dep[N];
void dfs(int u,int p){
	fa[u] = p,dep[u] = dep[p] + 1;
	for(auto it:g[u]){
		if(it.fi == p)continue;
		w[it.fi] = it.se;
		if(dep[it.fi]){
			if(dep[it.fi] < dep[u]){
				cnt++;
				s[cnt].pb(it.se);
				int cur = u;
				while(cur != it.fi){
					s[cnt].pb(w[cur]);
					cur = fa[cur];
				}
			}	
		}
		else dfs(it.fi,u);
	}
}
