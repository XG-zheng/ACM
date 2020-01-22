//col-> Number of SCC
//id[x] -> color of x
// big[x] size of  xth SCC 
// n -> [1,n] 
//ng new graph
namespace SCC{ 
	const int N = 101010;
	int dfn[N],low[N],st[N],top,id[N],col,cnt,big[N];
	void dfs(int u,vi g[]){
		dfn[u] = low[u] = ++cnt;
		st[top++] = u;
		for(int i = 0 ;i < sz(g[u]);++i){
			int v= g[u][i];
			if(!dfn[v]){
				dfs(v,g);
				low[u] = min(low[u],low[v]);
			}
			else if(!id[v])
				low[u] = min(low[u],dfn[v]);
		}
		if(low[u] == dfn[u]){
			++col;
			do{
				id[st[--top]] = col;
				big[col] ++;
			}while(st[top] != u);
		}
	}
	vi ng[N];
	int solve(int n,vi g[]){
		fill_n(big,n + 1,0);
		fill_n(dfn,n + 1,top = 0);
		fill_n(low,n + 1,col = 0);
		fill_n(id, n + 1,cnt = 0);
		rep( i , 1 ,n + 1)if(!dfn[i])dfs(i,g);
		fill_n(ng,col + 1,vi());
		rep( i , 1 , n + 1)
			for(int v = 0;v < sz(g[i]);++v){
				int j= g[i][v];
				if(id[i] != id[j])ng[id[i]].pb(id[j]);
			}
		return col;
	}
} 
