const int N=2e3+5;
const int inf = 0x3f3f3f3f;
vector<pii> g[N];
int dp[N][1025],pw[N];
bool vis[N];
queue<int> q;
void spfa(int msk){
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vis[u] = false;
		rep(i , 0 , sz(g[u])){
			int v = g[u][i].fi,w = g[u][i].se;
			int cur = (pw[v]|msk);
			if(dp[v][cur] > dp[u][msk] + w){
				dp[v][cur] = dp[u][msk] + w;
				if(!vis[v] && cur == msk){
					vis[v] = true;
					q.push(v);
				}
			}
		}
	}
}
// n个点,m个需连通的点
//pw[i] 将点映射到状态上,如果是待连通的点则为2^k，否则为0  
int SteinerTree(int n,int m){
	rep(i , 1 , n + 1){
		rep(j ,  0 , (1<<m))dp[i][j] = inf;
		pw[i] = 0;
	}
	rep(i , 1 , m + 1)
		pw[i] = (1<<(i - 1)),dp[i][1<<(i - 1)] = 0;
	rep(msk , 1 , (1<<m)){
		rep(i , 1 , n + 1){
			if(pw[i] && !(pw[i]&msk))continue;
			for(int sub = msk & (msk - 1) ; sub > 0;sub = (sub - 1) & msk){
				if(dp[i][sub|pw[i]] + dp[i][msk^sub|pw[i]] < dp[i][msk])
					dp[i][msk] = dp[i][sub|pw[i]] + dp[i][msk^sub|pw[i]];
			}
			if(dp[i][msk] < inf)q.push(i),vis[i] = 1;
		}
		spfa(msk);
	}
	int ans = inf;
	rep(i , 1 , n + 1){	
		ans = min(ans,dp[i][(1<<m) - 1]);
	}
	return ans;
}
