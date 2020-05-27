struct hashTable{
	static const int N = 5e5 + 5;
	int h[N],ne[N],sta[N],cnt;
	ll v[N];
	void clear(){
		memset(h,-1,sizeof(h));
		cnt = 0;
	}
	ll &operator[](int cur){
		int i;
		for(i = h[cur%N];(~i) && sta[i] != cur;i = ne[i]);
		if(i == -1)sta[cnt] = cur,ne[cnt] = h[cur%N],h[cur%N] = i = cnt++,v[i] = 0;
		return v[i];
	}
}f[2];
