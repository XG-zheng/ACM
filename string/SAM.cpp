<<<<<<< HEAD
//SAM统计子串出现数量 
=======
//SAM缁熻瀛愪覆鍑虹幇鏁伴噺 
>>>>>>> 1789cf67cf6500ddf015f4a142eed1915a9384a0
const int N=1e6+5;
struct state {
	int len, link;
	int ch[26];
};
state st[N * 2];
int sz, last;
<<<<<<< HEAD
int cnt[N*2]; //统计每个状态的子串出现次数 
=======
int cnt[N*2]; //缁熻姣忎釜鐘舵�佺殑瀛愪覆鍑虹幇娆℃暟 
>>>>>>> 1789cf67cf6500ddf015f4a142eed1915a9384a0

void sam_init() {
	st[0].len = 0;
	st[0].link = -1;
	sz++;
	last = 0;
}
void sam_extend(int c) {
	int cur = sz++;
	cnt[cur]=1;
	st[cur].len = st[last].len + 1;
	int p = last;
	while (p != -1 && !st[p].ch[c]) {
		st[p].ch[c] = cur;
		p = st[p].link;
	}
	if (p == -1) {
		st[cur].link = 0;
	} 
	else {
		int q = st[p].ch[c];
		if (st[p].len + 1 == st[q].len) {
			st[cur].link = q;
		} 
		else {
			int clone = sz++;
			st[clone] = st[q];
			st[clone].len = st[p].len + 1;
			st[clone].link = st[q].link;
			while (p != -1 && st[p].ch[c] == q) {
				st[p].ch[c] = clone;
				p = st[p].link;
			}
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}
vi G[N*2];
char s[N];
void dfs(int u) {
	for(auto v:G[u]) {
		dfs(v);
		cnt[u]+=cnt[v];
	}
}
int main() {
	scanf("%s",s+1);
	sam_init();
	int len=strlen(s+1);
	rep(i,1,len+1)
	sam_extend(s[i]-'a');
	for(int i=1; i<sz; ++i) {
		G[st[i].link].pb(i);
	}
	dfs(0);
	return 0;
}
