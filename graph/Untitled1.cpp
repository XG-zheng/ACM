// e_st[i] -> the set of edge of the ith connected component 
// by tagging edge   vis[];
// n[0,n)
// g pii fi -> v se-> the lable of edge 
namespace DCC{
    const int N = 202020;
    vi key , dcc[N],e_st[N];
    vi e;
    int dfn[N] , low[N] , st[N] , _st , _;
    bool vis[N];
    void dfs(int c,int fa,int dep,const vector<pii> g[]){
		int cc=0,out=1<dep;st[_st++]=c;
        dfn[c]=low[c]=dep;
        for(auto it:g[c]){
        	int t = it.fi;
        	if(vis[it.se])continue;
			vis[it.se] = true;
            if(!dfn[t]){
            	e.pb(it.se);
                dfs(t,c,dep+1,g);
                low[c]=min(low[c],low[t]);
                if(low[t]>=dfn[c]){
                    if(++out==2) key.pb(c);
					while(e.back()!=it.se){
                    	e_st[_].pb(e.back());
                    	e.pop_back();
					}
					e_st[_].pb(e.back()),e.pop_back();
					int cnt = 2;
                    while(st[--_st]!=t) dcc[st[_st]].pb(_),cnt++;
                    dcc[c].pb(_);dcc[t].pb(_++);		
				}
            } else if(dfn[t] != dfn[c] - 1 || cc++){
                low[c] = min(low[c] , dfn[t]);
				e.pb(it.se);
            }
        }
    }
    int solve(int n,const vector<pii> g[]){// n is size of points
        fill_n(dfn,n,_=0);
        fill_n(low,n,_st=0);
        fill_n(dcc,n,key=vi());
        rep(i,0,n) if(!dfn[i]) dfs(i,-1,1,g);
        rep(i,0,n) if(sz(dcc[i]) == 0) dcc[i].pb(_++);
        return _;
    }
}
