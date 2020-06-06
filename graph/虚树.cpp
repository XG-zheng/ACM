

struct VTree{
	int dfn[N] , fa[N][20] , mn[N][20] , tot = 0 , h[N] ,top = 0;
	vi vg[N]; //Vtree
	int stk[N];
	void dfs(int u,vector<pii> g[]){
		dfn[u] = ++tot;
		rep( i , 1 , 20)
			if(fa[u][i - 1])fa[u][i] = fa[fa[u][i - 1]][i - 1] ,mn[u][i] = min(mn[u][i-1] , mn[fa[u][i - 1]][i - 1]);
		rep(i , 0 , sz(g[u])){
			int v = g[u][i].fi, w = g[u][i].se;
			if(v == fa[u][0])continue;
			mn[v][0] = w,fa[v][0] = u , h[v] = h[u] + 1;	
			dfs(v , g);
		}
	}
	int LCA(int u,int v){
		if(h[u] < h[v])swap(u , v);
		int d = h[u] - h[v];
		for(int i = 18;i >= 0;--i)
			if(d>>i&1)u = fa[u][i];
		if(u == v)return v;
		for(int i = 18;i >= 0;--i)
			if(fa[u][i] != fa[v][i])
				u = fa[u][i],v = fa[v][i];
		return fa[u][0];
	}
	
	void insert(int v){
		if(top == 0){stk[++top] = v;return;}
		int lca = LCA(v , stk[top]);
		if(stk[top] == lca){stk[++top] = v;return;}
		while(top > 1 && dfn[stk[top - 1]] >= dfn[lca]){
			vg[stk[top - 1]].pb(stk[top]);
			top--;
		}
		if(lca != stk[top])vg[lca].pb(stk[top]),stk[top] = lca;
		stk[++top] = v;
	}
	//the set of V(sorted by dfn)
	void solve(vi V){
		top = 0;
		rep(i , 0 ,sz(V))
			insert(V[i]);
		while(top > 1){
			vg[stk[top - 1]].pb(stk[top]);
			top--;
		}
	}
}VT;



