typedef pair<ll,ll>pii;
const int N=2e5+5;
const ll Linf = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
template<class U,class V>
struct MCMF{
	static const int N = 5e5 + 500, M = N*6;
	int h[N] , pre[N] , to[M], ne[M] , e , s , t , n;
	U cap[M];V dis[N] , cost[M] ,phi[N];
	bool vis[N];
	void ini(int _n = N){ fill(h , h + (n=_n) , -1);e = 0;}
    void liu(int u,int v,U c,V w){ to[e] = v;ne[e] = h[u];cap[e] = c;cost[e] = w;h[u] = e++;}
    void link(int u,int v,U c,V w){ liu(u,v,c,w);liu(v,u,0,-w); }
	bool dij(){
		fill(dis , dis + n,Linf);
		fill(vis , vis + n , 0);
		priority_queue<pii> Q;
		Q.push(pii(0,s)) , dis[s] = 0;
		while(!Q.empty()){
			int c = Q.top().se;Q.pop();
			if(vis[c])continue;
			vis[c] = 1;
			for(int k = h[c];~k;k = ne[k])if(cap[k] > 0){
				int v = to[k];
				if(dis[v] > dis[c] + phi[c] - phi[v] + cost[k]){
					dis[v] = dis[c] + phi[c] - phi[v] + cost[k];
					pre[v] = k;
					Q.push(pii(-dis[v],v));
				}
			}
		}
		rep(i , 0 , n )
			if(dis[i] < Linf)phi[i] += dis[i]; 
		return dis[t] != Linf;
	}
	U flow;V mincost;
	void spfa(){
		queue<int> Q;
        fill(phi, phi+n, Linf);
        Q.push(s), vis[s] = 1, phi[s] = 0;
        while(!Q.empty()){
            int c = Q.front(); Q.pop(); vis[c] = 0;
            for(int k = h[c]; ~k; k = ne[k]) if (cap[k] > 0) {
                int v = to[k];
                if(phi[c] + cost[k] < phi[v]){
                    phi[v] = phi[c] + cost[k];
                    if(!vis[v]) Q.push(v) , vis[v] = 1;
                }
            }
        }
	}
	pair<U ,V> run(int _s,int _t){
		s = _s, t = _t;
		spfa();
		flow = mincost = 0;
		while(dij()){
			U pl = Linf;int p , k;
			for(p = t;p != s;p = to[k^1])pl = min(pl,cap[k = pre[p]]);
			for(p = t;p != s;p = to[k^1])cap[k = pre[p]] -= pl,cap[k^1] += pl;
			mincost += pl*phi[t];
			flow += pl;
		}
		return make_pair(flow,mincost);
	}
};
MCMF<ll,ll> flow;
