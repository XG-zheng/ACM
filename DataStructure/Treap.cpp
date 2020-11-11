struct node{
	int val,cnt,sz,ls,rs;
	ll r,sum;
}nd[N*24];
int L = 0;
struct pp{
	ll fi;int se;
	pp(ll _x = 0,ll _y = 0){fi = _x,se = _y;}
};
struct Treap{
	int rt ;
	void init(){rt = 0;srand(time(0));}
	inline ll Rand(){return ((rand()*1ll<<32)^(rand()*1ll<<16)^rand());}
	inline int newnode(int c){
		nd[++L].r = Rand();
		nd[L].val = c;nd[L].sum = c;
		nd[L].cnt = nd[L].sz = 1;
		nd[L].ls = nd[L].rs = 0;
		return L;
	}
	inline void up(int x){
		if(!x)return;
		int ls = nd[x].ls,rs = nd[x].rs;
		nd[x].sz = nd[ls].sz + nd[rs].sz + nd[x].cnt;
		nd[x].sum = nd[ls].sum + nd[rs].sum + nd[x].val;
	}
	inline void zig(int &k){   // L 
		int v = nd[k].rs;nd[k].rs = nd[v].ls;
		nd[v].ls = k;nd[v].sz = nd[k].sz;nd[v].sum = nd[k].sum;
		up(k);k = v;
	}
	inline void zag(int &k){ // R
		int v = nd[k].ls;nd[k].ls = nd[v].rs;
		nd[v].rs = k;nd[v].sz = nd[k].sz;nd[v].sum = nd[k].sum;
		up(k);k = v;
	}
	void ins(int &u,int val){
		if(!u){ u = newnode(val);return;}
		if(val < nd[u].val){
			ins(nd[u].ls , val);
			if(nd[nd[u].ls].r < nd[u].r)zag(u);
		}
		else{
			ins(nd[u].rs,val);
			if(nd[nd[u].rs].r < nd[u].r)zig(u); 
		}
		up(u);
	}
	void del(int &u,int val){
		if(!u)return;
		if(nd[u].val == val){
			if(!nd[u].ls || !nd[u].rs)u = nd[u].ls|nd[u].rs;
			else if(nd[nd[u].ls].r < nd[nd[u].rs].r)zag(u),del(nd[u].rs , val);
			else zig(u),del(nd[u].ls , val);	
		}
		else if(nd[u].val < val)del(nd[u].rs , val);
		else del(nd[u].ls , val);
		up(u);
	} 
	pp qry(int u,int val){
		pp res,tmp;
		if(!u)return res;
		if(nd[u].val >= val){
			res.fi = nd[u].sum - nd[nd[u].ls].sum,res.se = nd[u].sz - nd[nd[u].ls].sz;
			tmp = qry(nd[u].ls , val);
			res.fi += tmp.fi;
			res.se += tmp.se;
			return res;	
		}
		else{
			return qry(nd[u].rs , val); 
		}
	}
}tr;
