const int N=2e6+5;
//Hierholzers算法 倒序输出为欧拉路径
//求字典序最小的路径，将点从小到大排序即可 
vi ans;
bool vis[N];
vector<pii> g[N];  //pii<点，边编号> 
int p[N];
void dfs(int u){
	for(;p[u] < sz(g[u]);++p[u]){
		pii it = g[u][p[u]];
		if(vis[it.se])continue;
		vis[it.se] = true;
		dfs(it.fi);
	}
	ans.pb(u);
}



