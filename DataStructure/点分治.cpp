// calc the number of pair(i,j) ,i < j dis(i,j) == k 
bool vis[N];
int q[N] , r , mx , rt , big[N] , tot  ,d[N],cnt[N];
vi g[N];
ll ans = 0;
void findRoot(int u,int p){
	big[u] = 1;int cur = 0;
	for(auto v:g[u]){
		if(vis[v] || v == p)continue;
		findRoot(v , u);
		big[u] += big[v];
		cur = max(big[v] , cur);
	}
	cur = max(cur, tot - big[u]);
	if(cur < mx)mx = cur, rt = u;
}
int getDis(int u,int p){
	d[u] = d[p] + 1;q[++r] = d[u];
	for(auto v:g[u]){
		if(vis[v] || v == p)continue;
		getDis(v , u);
	}
}
void calc(int u){
	r = 0;d[0] = 0;
	int pr;cnt[0]++;
	ll res = 0;
	for(auto v:g[u]){
		if(vis[v])continue;
		pr = r;
		getDis(v , 0);
		for(int i = pr + 1;i <= r;i++){
			if(q[i] <= k)res += cnt[k - q[i]];
		}
		for(int i = pr + 1;i <= r;i++)
			cnt[q[i]]++;
	}
	cnt[0]--;
	for(int i = 1;i <= r;i++)cnt[q[i]]--;
	ans += res;
}
void dfs(int u){
	vis[u] = true;
	int tmp = tot;
	calc(u);
	for(auto v:g[u]){
		if(vis[v])continue;
		if(big[v] > big[u])tot = tmp - big[u];
		else tot = big[v];
		mx = inf;
		findRoot(v, 0);
		dfs(rt);	
	}
}
