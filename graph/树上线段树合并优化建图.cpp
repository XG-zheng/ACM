const int N=1e6+5;
const int inf = ~0U>>1;
template<class T>
struct Dinic{
    const static int N = 10101*50, M = N * 2;
    int s , t , n , h[N] , cur[N] , lv[N] , q[N] , e , ne[M] , to[M];
    T cap[M] , flow;
    void liu(int u,int v,T w){ to[e] = v;ne[e] = h[u];cap[e] = w;h[u] = e++;}
    void link(int u,int v,T w){ liu(u , v , w);liu(v , u , 0);}
    void ini(int _n = N) { fill(h , h + (n=_n) , -1);e = 0;}
    bool bfs(){
        int L = 0 , R = 0;
        fill(lv , lv + n , -1);
        lv[q[R++] = s] = 0;
        while(L < R && !~lv[t]){
            int c = q[L++];
            for(int k = h[c]; ~k ; k = ne[k]){
				if(cap[k] > 0 && !~lv[to[k]]) 
                    lv[q[R++] = to[k]] = lv[c] + 1;
            }
        }
        return ~lv[t];
    }
    T dfs(int c,T mx){
        if(c == t) return mx;
        T ret = 0;
        for(int &k = cur[c]; ~k; k = ne[k]){
            if(lv[to[k]] == lv[c] + 1 && cap[k] > 0){
                T flow = dfs(to[k] , min(mx , cap[k]));
                ret += flow;cap[k] -= flow , cap[k^1] += flow;mx -= flow;
                if(!mx) return ret;
            }
        }
        lv[c] = -1;
        return ret;
    }
    T run(int _s,int _t){
        s = _s , t = _t;
        flow = 0;
        while(bfs()){
            copy(h , h + n , cur);
            flow += dfs(s, ~0U>>1);
        }
        return flow;
    }
};
Dinic<int> flow;
struct node{
	int l,r,sum;
	node(){sum = 0;}
}T[N];
int s , t;
int n,rt[N],cnt = 0;
//link u to ( subTree x &&  L<= w[i] <= R)
void add(int x,int L,int R,int l,int r,int u){
	if(x == 0 )return;
	if(L <= l && r <= R){
		flow.link(u , x, inf);  //addedge
		return;
	}
	int m = l + r>>1;
	if(L <= m)add(T[x].l,L,R,l,m,u);
	if(R > m)add(T[x].r , L , R , m + 1,r,u);
}
void upd(int &u,int l,int r,int pos,int id){
	if(!u) u = ++cnt;
	if(l == r){
		flow.link(u , id , inf);  //addedge
		return ;
	}
	int m = l + r>>1;
	if(pos <= m)upd(T[u].l , l , m , pos , id),flow.link(u , T[u].l , inf); //addedge
	else upd(T[u].r , m + 1, r , pos , id),flow.link(u , T[u].r , inf); //addedge
}
int merge(int u ,int v,int l,int r){
	if(!u)return v;
	if(!v)return u;
	int t = ++cnt;
	if(l == r){
		flow.link(t , u , inf); //addedge
		flow.link(t , v , inf);  //addedge
		return t;
	}
	int m = l + r>>1;
	T[t].l = merge(T[u].l,T[v].l,l,m);
	T[t].r = merge(T[u].r,T[v].r , m + 1, r);
	flow.link(t , T[t].l , inf); //addedge
	flow.link(t , T[t].r , inf); //addedge
	return t;
}
vi g[N];
int h[N],m;
void dfs(int u){
	upd(rt[u] , 1 , n , h[u] , u + m); //insert first!! 
	for(auto v:g[u]){
		dfs(v);
		rt[u] = merge(rt[u] , rt[v] , 1 , n); 		
	}
}




