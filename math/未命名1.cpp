#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int>vi;

#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define fi first
#define all(x) x.begin(),x.end()
#define sz(x)  (int)x.size()
#define se second
#define de(x) cout<<#x<<"="<<x<<endl;
#define dd(x) cout<<#x<<"="<<x<<" " ;
#define pb(x) push_back(x)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
const int N=5e5+5;
int n,m;
ll a[N],ss[N];
struct node{
	ll sum,mx,add,st;
	int l,r;
	node(){
		sum=mx=add=0;
		st=-1;
	}
}t[N<<2];
void Build(int l,int r,int rt){
	t[rt].l=l,t[rt].r=r,t[rt].sum=t[rt].mx=t[rt].add=0,t[rt].st=-1;
	if(l==r)return ;
	int mid=(l+r)>>1;
	Build(l,mid,rt<<1);
	Build(mid+1,r,rt<<1|1);
}
void pushUp(int rt){
	t[rt].mx=max(t[rt<<1].mx,t[rt<<1|1].mx);
	t[rt].sum=t[rt<<1].sum+t[rt<<1|1].sum;
}
void pushDown(int rt){
	if(t[rt].st!=-1){
		t[rt<<1].st=t[rt<<1|1].st=t[rt].st;
		t[rt<<1].add=t[rt<<1|1].add=0;
		t[rt<<1].sum=t[rt].st*(t[rt<<1].r-t[rt<<1].l+1);
		t[rt<<1|1].sum=t[rt].st*(t[rt<<1|1].r-t[rt<<1|1].l+1);
		t[rt<<1].mx=t[rt<<1|1].mx=t[rt].st;
		t[rt].st=-1; 
	}
	if(t[rt].add){
		t[rt<<1].add+=t[rt].add; 
		t[rt<<1|1].add+=t[rt].add; 
		t[rt<<1].mx+=a[t[rt<<1].r]*t[rt].add;
		t[rt<<1|1].mx+=a[t[rt<<1|1].r]*t[rt].add;
		t[rt<<1].sum+=(ss[t[rt<<1].r]-ss[t[rt<<1].l-1])*t[rt].add;
		t[rt<<1|1].sum+=(ss[t[rt<<1|1].r]-ss[t[rt<<1|1].l-1])*t[rt].add;	
		t[rt].add=0;
	}
}
void upd1(int L,int R, ll c,int l,int r,int rt){
	if(L<=l && r <= R){
		t[rt].mx=c;
		t[rt].sum=(r-l+1)*c;
		t[rt].st=c;
		t[rt].add=0;
		return ;
	}
	int mid=(l+r)>>1;
	pushDown(rt);
	if(L<=mid) upd1(L,R,c,l,mid,rt<<1);
	if(R>mid) upd1(L,R,c,mid+1,r,rt<<1|1);
	pushUp(rt);
}
void upd2(int L,int R,ll c,int l,int r,int rt){
	if(L<=l && r<=R){
		t[rt].add+=c;
		t[rt].sum+=c*(ss[r]-ss[l]+1);
		t[rt].mx+=a[r]*c;
		return ;
	}
	int mid=(l+r)>>1;
	pushDown(rt);
	if(L<=mid)upd2(L,R,c,l,mid,rt<<1);
	if(R>mid) upd2(L,R,c,mid+1,r,rt<<1|1);
	pushUp(rt);
}
int qry(ll c,int l,int r,int rt){
	if(l==r){
		return l;
	}
	int mid=(l+r)>>1;
	pushDown(rt);
	node ans;
	ans.mx=0;
	if(t[rt<<1].mx>=c){
		return qry(c,l,mid,rt<<1);
	}
	else if(t[rt<<1|1].mx>=c)return qry(c,mid+1,r,rt<<1|1);
	else return -1;
}
ll qrysum(int L,int R,int l,int r,int rt){
	if(L<=l && r<= R){
		return t[rt].sum;
	}
	int mid=(l+r)>>1;
	pushDown(rt);
	ll ans=0;
	if(L<=mid) ans+=qrysum(L,R,l,mid,rt<<1);
	if(R>mid) ans+=qrysum(L,R,mid+1,r,rt<<1|1);
	return ans; 
}
int main(){
	
	scanf("%d%d",&n,&m);
	rep(i,1,n+1)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	rep(i,1,n+1)
		ss[i]=ss[i-1]+a[i]; 
	ll d,b;
	Build(1,n,1);
	int pre=0;
	while(m--){
		scanf("%lld%lld",&d,&b);
		upd2(1,n,d-pre,1,n,1);
		int p=qry(b,1,n,1);
		if(p==-1){
			printf("0\n");
		}
		else{
			ll s=qrysum(p,n,1,n,1);
			ll del=s-(n-p+1)*b;
			printf("%lld\n",del);
			upd1(p,n,b,1,n,1);
		}
	/*	for(int i=1;i<=n;++i){
			cout<<qrysum(i,i,1,n,1)<<" ";
		}
		cout<<endl;
		de(qrysum(1,4,1,n,1))*/
		pre=d;
	}
	return 0;
}
