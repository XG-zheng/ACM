struct hashTable{
	static const int N = 1e5 + 5;
	int h[N],ne[N],sta[N],cnt;
	ll v[N];
	void clear(){
		memset(h,-1,sizeof(h));
		rep(i , 0  , N)h[i] = -1 , sta[i] = -1,ne[i] = -1,v[i] = 0;
		cnt = 0;
	} 
	ll &operator[](int cur){
		int i;
		for(i = h[cur%N] ;(~i) && sta[i] != cur ; i = ne[i]);
		if(i == -1)sta[cnt] = cur,ne[cnt] = h[cur%N],h[cur%N] = i = cnt++;
		return v[i];
	}
	
}f[2];
