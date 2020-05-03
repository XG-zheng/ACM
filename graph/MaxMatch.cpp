//n  the number of vertex in left part   [1,n]
// m  the number of vertex in right part [1,m]
// edge (left)u->v(right) 

//最大独立集输出方案 |最大独立集| = |V| - 最大匹配 
//先求最大匹配，每一对匹配的点只能选取左边或者右边，不在匹配上的点则要全选。 
//则从不在匹配上的左半图点开始搜索，能走到的左半图的点都可选，右半图走到的则不可选。 
//存在某对匹配左右都访问不到，那么默认选取了左边的点。

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
