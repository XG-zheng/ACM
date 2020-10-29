struct Trie{
	static const int M = 26,N = ::N;
	bool ep[N];
	int ne[N][M],fail[N],fa[N],rt,L,top[N];// top[v]  fail 指针从 v 往上跳最近的一个完整字符串 
	int newnode(){fill_n(ne[L],M,0);return L++;}
	void ini(){
		fill_n(ne[fail[0] = N - 1],M ,0);
		L = 0,rt = newnode();
	}
	int add(char *s){
		int p = rt;
		for(int i = 0;s[i];i++){
			int c = s[i] - 'a';
			if(!ne[p][c])ne[p][c] = newnode(),fa[L-1] = p;
			p = ne[p][c];
		}
		ep[p] = 1;
		return p;
	}
	void build(){
	    vi v;v.pb(rt);
	    rep(i,0,sz(v)){
	        int c = v[i];
	        ep[fail[c]] == 1 ? top[c] = fail[c]:top[c] = top[fail[c]];
	        rep(i,0,M) ne[c][i] ?
	            v.pb(ne[c][i]) , fail[ne[c][i]] = ne[fail[c]][i] :
	            ne[c][i] = ne[fail[c]][i]; 
		}
	}
}tr; 
