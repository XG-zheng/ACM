//n  the number of vertex in left part   [1,n]
// m  the number of vertex in right part [1,m]
// edge (left)u->v(right) 
struct MaxMatch{
	const static int N = 1010;
	int link[N];
	bool vis[N];
	bool dfs(int u,vi g[]){
		for(auto v:g[u]){
			if(vis[v])continue;
			vis[v] = 1;
			if(!link[v]  || dfs(link[v],g)){
				link[v] = u;
				return true;
			}
		}
		return false;
	}
	int solve(int n,int m,vi g[]){
		fill(link,link + m + 1,0);
		int res = 0;
		rep(i , 1 , n + 1){
			fill(vis,vis + m + 1,0);
			res += dfs(i,g);
		}
		return res;
	}
};
