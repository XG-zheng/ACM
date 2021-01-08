#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int>pii;
typedef vector<int>vi;

#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define fi first
#define se second
#define de(x) cout<<#x<<"="<<x<<"\n"
#define dd(x) cout<<#x<<"="<<x<<" "
#define pb(x) push_back(x)
#define all(x) x.begin(),x.end()
#define sz(x) (int)x.size()
#define lowbit(a) ((a)&-(a))
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define mp make_pair
#define sec ((clock_t)1000)
const int N = 1e6 + 5;
const int inf = 0x3f3f3f3f;
int f[N];
struct PAM {
	static const int N = ::N, M = 26;
	// dif[x] = len[u] - len[fail[u]] , slink[u] -> jump along fail[] ,the first v ,satisfy dif[v] != dif[u]
	int s[N], len[N], ne[N][M], fail[N], cnt[N], dep[N], id[N], no[N], last, n, p,slink[N],dif[N];
	inline int newnode(int l) { fill_n(ne[p], M, 0); cnt[p] = dep[p] = 0; len[p] = l; return p++; }
	inline void init() { newnode(p = 0), newnode(s[0] = -1), fail[last = n = 0] = 1; }
	inline int getfail(int x) { 
		while(s[n - len[x] - 1] != s[n]) x = fail[x]; 
		return x; 
	}
	inline void add(int c) {
		s[++n] = c;
		int cur = getfail(last);
		if(!ne[cur][c]) {
			int now = newnode(len[cur] + 2);
			fail[now] = ne[getfail(fail[cur])][c];
			ne[cur][c] = now;
			dep[now] = dep[fail[now]] + 1;
		}
		last = ne[cur][c], cnt[last]++; 
		id[n] = last, no[last] = n; 
		dif[last] = len[last] - len[fail[last]];
		dif[last] == dif[fail[last]]?slink[last] = slink[fail[last]]:slink[last] = fail[last];
	}
	inline void build() { per(i, 0, p) cnt[fail[i]] += cnt[i]; }
}pam;
char s[N],t1[N],t2[N];
int n;
int pre[N];
int g[N]; 
int main(){
	scanf("%s",s + 1);
	n = strlen(s + 1);
	memset(f,0x3f,sizeof(f));
	f[0] = 0;
	pam.init();
	rep(i , 1 , n + 1){
		pam.add(s[i] - 'a');
		for(int j = pam.last;j > 1;j = pam.slink[j]){
			g[j] = i - pam.len[pam.slink[j]] - pam.dif[j];
			int fj = pam.fail[j];
			if(pam.dif[j] == pam.dif[fj] && f[g[j]] > f[g[fj]]) g[j] = g[fj];
			if(f[i] > f[g[j]] + 1)f[i] = f[g[j]] + 1,pre[i] = g[j];
		}
	}
	if(f[n] == inf){
		printf("-1");
	}
	else{
		printf("%d\n",f[n]);
	}
	return 0;
}

