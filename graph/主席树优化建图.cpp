const int N=5e5+5;
const int inf = ~0U>>1;
template<class T>
struct Dinic{
    const static int N = 10101*50, M = N * 10;
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
            for(int k = h[c]; ~k ; k = ne[k])
                if(cap[k] > 0 && !~lv[to[k]]) 
                    lv[q[R++] = to[k]] = lv[c] + 1;
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
int  s , t;
int n,rt[N],cnt = 0;
//build
void upd(int l,int r,int pos,int &x,int y,int id){
	T[++cnt] = T[y],T[cnt].sum++;
	x = cnt;
	flow.link(x , y ,inf);   //addedge (x - >y)
	if(l == r){
		flow.link(x,id,inf);
		return;
	}
	int m = l + r>>1;
	if(pos <= m){
		upd(l , m , pos , T[x].l , T[y].l,id);
		flow.link(x , T[x].l , inf); //addedge x - > lson
	}
	else{
		upd(m + 1,r , pos , T[x].r , T[y].r,id);
		flow.link(x , T[x].r , inf);	//addedge x -> rson
	}
}
//link u to (id in [1,x] &&  L<= w[i] <= R)
void add(int x,int L,int R,int l,int r,int u){
	if(T[x].sum == 0)return;
	if(L <= l && r <= R){
		flow.link(u , x, inf);   //addedge  u ->[l,r]
		return;
	}
	int m = l + r>>1;
	if(L <= m)add(T[x].l,L,R,l,m,u);
	if(R > m)add(T[x].r , L , R , m + 1,r,u);
}




