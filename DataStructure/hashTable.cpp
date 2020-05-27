struct hashTable{
    static const int N = 5e5 + 5;
    static const int hash = 10007 + 5;
    int h[hash],ne[N],sta[N],cnt;
    int v[N];
    void clear(){
        memset(h,-1,sizeof(h));
        cnt = 0;
    }
    int &operator[](int cur){
        int i,hs = cur%hash;
        for(i = h[hs];(~i) && sta[i] != cur;i = ne[i]);
        if(i == -1)sta[cnt] = cur,ne[cnt] = h[hs],h[hs] = i = cnt++,v[i] = -inf;
        return v[i];
    }
}f[2];
