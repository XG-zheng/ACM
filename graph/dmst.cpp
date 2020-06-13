// n start from 0
struct edge {
	int u, v, U, V;int d;bitset<1005> b; //u->v,cost d(type follow with template T), b:index of edge
	edge(int _u,int _v,int _d,int _U,int _V){
		u = _u,v = _v,d = _d,U = _U,v = _V;
	}
	edge(){}	
};
template<class T>
struct DMST{
	static const int N = ::N , M = N * N , inf = 2e9;
	edge e[M];int n, m, vis[N], pre[N], id[N], index[N];
	bitset<1005> fang; //the task of edge
	T in[N];
	void ini(int n) {this->n = n, m = 0;}
	void addedge(int u, int v, T d) {e[m] = edge(edge(u,v,d,u,v)); e[m].b.reset();e[m].b[m] = 1;m++;}
	T run(int root){
		T ans = 0;
		while(1){
			rep(i, 0, n) in[i] = inf;
			rep(i, 0, m){
				int u = e[i].u ,v = e[i].v;
				if(e[i].d < in[v] && u != v) in[v] = e[i].d, pre[v] = u, index[v] = i;
			}
			rep(i, 0, n) {
				if(i == root) continue; 
				if(in[i] == inf) return -1;
				fang ^= e[index[i]].b;
			}
			int cnt = 0;in[root] = 0;
			memset(id, -1, sizeof(*id)*n);
			memset(vis, -1, sizeof(*vis)*n);
			rep(i, 0, n){
				ans += in[i]; int v = i;
				while(vis[v] != i && id[v] == -1 && v!=root) vis[v] = i, v = pre[v];
				if(v != root && id[v] == -1) {
					for(int u=pre[v];u != v;u = pre[u]) id[u] = cnt;
					id[v] = cnt++;
				}
			}
			if(cnt == 0) break;
			rep(i, 0, n) if(id[i] == -1) id[i] = cnt++;
			rep(i, 0, m) {
				int v=e[i].v;
				e[i].u = id[e[i].u]; e[i].v = id[e[i].v];
				if(e[i].u != e[i].v) {e[i].d -= in[v];e[i].b ^= e[index[v]].b;}
			}
			n = cnt; root = id[root];
		}
		return ans;
	}
};
DMST<int> dmst;
