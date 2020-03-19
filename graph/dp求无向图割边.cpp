//dp[u] == 1 ,edge<fa[u],u) is a bridge
//g[][]  <v,id> 
// dp[u] = (# of back-edges going up from u)-(# of back-edges going down from u)? + $\sum dp[v]$

vector<pii> g[N];
int h[N],dp[N];
bool vis[N];
void dfs(int u,int p){
	h[u] = h[p] + 1;
	vis[u] = true;
	for(auto it:g[u]){
		if(vis[it.fi])continue;
		dfs(it.fi,u);
		dp[u] += dp[it.fi];
	}
	for(auto it:g[u]){
		if(h[it.fi] > h[u])dp[u]--;
		else dp[u]++;
	}
}
