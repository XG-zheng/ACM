//µã[1,n] 
template<class T>
struct Dinic{
	const static int N=10101,M=10*N;
	int s,t,n,h[N],cur[N],dep[N],q[N],e,nxt[M],to[M];
	T cap[M],flow;
	void liu(int u,int v,T w){to[e]=v,nxt[e]=h[u],cap[e]=w,h[u]=e++;}
	void link(int u,int v, T w){liu(u,v,w);liu(v,u,0);}
	void init(int _n=N){n=_n;fill(h+1,h+n+1,-1);e=0;}
	bool bfs(){
		int L=0,R=0;
		fill(dep+1,dep+n+1,0);
		dep[q[R++]=s]=1;
		while(L<R && !dep[t]){
			int c=q[L++];
			for(int k=h[c];~k;k=nxt[k])
				if(cap[k]>0 && !dep[to[k]])
					dep[ q[R++]=to[k] ] = dep[c] + 1;
		}
		return dep[t];
	}
	T dfs(int c,T mx){
		if(c==t)return mx;
		T ret=0;
		for(int &k = cur[c]; ~k ; k = nxt[k] ){
			if(dep[to[k]] == dep[c] + 1 && cap[k]>0 ){
				T flow = dfs(to[k],min(mx,cap[k]));
			
				ret+=flow;cap[k]-=flow,cap[k^1]+=flow;mx-=flow;
				if(!mx) return ret; 
			}
		}
		dep[c]=-1;
		return ret;
	}
	T run(int _s,int _t){
		s=_s,t=_t;
		flow=0;
		while(bfs()){
			copy(h,h+n+1,cur);
			flow+=dfs(s,~0U>>1);
		}
		return flow;
	}
};
Dinic<int> t1;
