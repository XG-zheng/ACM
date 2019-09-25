const int N=2e5+5;
struct SA{
	//sa[i] ��ʾ����Ϊi�ĺ�׺��ʼλ���±�
	//rk[i] ��ʾ�±�i��ʼ�ĺ�׺������
	//LCP(i,j) ����Ϊi��j�ĵĺ�׺�������ǰ׺
	//height[i]==LCP(i,i-1) height[1]=0; 
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
            //y[i]->�ڶ��ؼ�������Ϊi���ǵڼ�����׺
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=n;i++) c[x[i]]++;
            //x[i]->��i����׺�ĵ�һ�ؼ��������Ƕ���
            for(int i=2;i<=m;i++) c[i]+=c[i-1];
            for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
            //˫�ؼ��ֵĻ������� 
            swap(x,y);
            x[sa[1]]=1;num=1;
            for(int i=2;i<=n;i++) 
                x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
                //��Ϊ֮ǰ��������x,y�������������yʵ��������һ�ε�x
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
