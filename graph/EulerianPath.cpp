const int N=2e6+5;
//Hierholzers�㷨 �������Ϊŷ��·��
//���ֵ�����С��·���������С�������򼴿� 
vi ans;
bool vis[N];
vector<pii> g[N];  //pii<�㣬�߱��> 
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



