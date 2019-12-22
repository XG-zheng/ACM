//统计本质不同的字串，每个后缀贡献n-sa[i]+1-height[i] 
const int N=2e5+5;
struct SA{
	//sa[i] 表示排名为i的后缀起始位置下标
	//rk[i] 表示下标i起始的后缀的排名
	//LCP(i,j) 排名为i和j的的后缀的最长公共前缀
	//height[i]==LCP(i,i-1) height[1]=0; 
	//LCP(i,j)=min(LCP(i,k),LCP(k,j)){i<=k<=j}=min(height[k]){i<k<=j} 
	int x[N],y[N],c[N];
    char s[N];
	int n,m,num,sa[N],rk[N],height[N];
    
    void getsa(){
        m=122;
        n=strlen(s+1);
        for(int i=1;i<=n;i++) x[i]=s[i],c[x[i]]++;
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i;i--) sa[c[x[i]]--]=i;
        for(int k=1;num=0,k<=n;k<<=1){
            for(int i=n-k+1;i<=n;i++) y[++num]=i;
            for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
            //y[i]->第二关键字排名为i的是第几个后缀
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=n;i++) c[x[i]]++;
            //x[i]->第i个后缀的第一关键字排名是多少
            for(int i=2;i<=m;i++) c[i]+=c[i-1];
            for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
            //双关键字的基数排序 
            swap(x,y);
            x[sa[1]]=1;num=1;
            for(int i=2;i<=n;i++) 
                x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
                //因为之前交换过了x,y数组所以这里的y实际上是上一次的x
            if(num==n) return;
            m=num;
        }
    }
	void getheight(int k=0){
	    for(int i=1;i<=n;i++) rk[sa[i]]=i;
	    for(int i=1;i<=n;i++){
	        if(rk[i]==1) continue;
	        if(k) --k;
	        int j=sa[rk[i]-1];
	        while(i+k<=n and j+k<=n and s[i+k]==s[j+k]) k++;
	        height[rk[i]]=k;
	    }
	}
}ss;
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",ss.s+1);
	ss.getsa();
	ss.getheight();
	ll ans=0;
	rep(i,1,n+1){
		ans+=n-ss.sa[i]+1-ss.height[i];
	}
	printf("%lld\n",ans);
	return 0;
}
