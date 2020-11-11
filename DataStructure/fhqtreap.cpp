struct node{
	int val,cnt,sz,ls,rs;
	ll r,sum;
	bool rev;
}nd[N*24];
struct fhqTreap{
	int rt,L;
	void init(){rt = L = 0;}
	inline ll Rand(){return ((rand()*1ll<<32)^(rand()*1ll<<16)^rand());}
	inline int newnode(int c){
		nd[++L].r = Rand();
		nd[L].val = c;nd[L].sum = c;
		nd[L].cnt = nd[L].sz = 1;
		nd[L].ls = nd[L].rs = nd[L].rev = 0;
		return L;
	}
	void up(int x){
		if(!x)return;
		int ls = nd[x].ls,rs = nd[x].rs;
		nd[x].sz = nd[ls].sz + nd[rs].sz + nd[x].cnt;
		nd[x].sum = nd[ls].sum + nd[rs].sum + nd[x].val;
	}
	void splitc(int u,int c,int &x,int &y){
		if(u){
			if(nd[u].val <= c)x = u , splitc(nd[u].rs,c,nd[u].rs,y);
			else y = u,splitc(nd[u].ls , c , x , nd[u].ls);
			up(u);
		}else x = y = 0;
	}
	void splitk(int u,int k ,int &x,int &y){
		if(u){
			int sz = nd[nd[u].ls].sz;
			if(sz < k)x = u ,splitk(nd[u].rs , k - sz - 1,nd[u].rs , y);
			else y = u ,splitk(nd[u].ls , k , x , nd[u].ls);
		}else x = y = 0;
	}
	int merge(int x,int y){
		if(x && y){
			if(nd[x].r < nd[y].r){nd[x].rs = merge(nd[x].rs,y),up(x);return x;}
			else {nd[y].ls = merge(x , nd[y].ls),up(y);return y;}
		}else return x + y;
	}
	inline void insert(int val){
		int x , y;
		splitc(rt , val , x , y);
		rt = merge(merge(x , newnode(val)) , y);
	}
	inline void del(int val){
		int x , y , z;
		splitc(rt , val , x, y);
		splitc(x , val - 1,x , z);
		z = merge(nd[z].ls , nd[z].rs);
		rt = merge(merge(x , z) , y);
	}
}tr[N<<2];



