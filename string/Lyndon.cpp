// p = p[0-s[1]]p[(s[1] + 1)-s[2]]..p[(s[cnt-1] + 1)...s[cnt]] = q[1]q[2]q[3]...q[cnt]
//q[i] => ith lyndon substr  p[s[i-1]+1-s[i]]     
//q[1] >=q[2]>=....>=q[cnt]  in lexicographical order
//if string t is lyndon string => minsuf(t) = t and  min_period T = sz(t)
//time O(n)
struct Lyndon{
	int s[N],cnt = 0;
	void solve(string &p){
		int n = sz(p);
		for(int i = 0 , j , k;i < n;){
			ans[i] = i;
			
			//find (uva)^t 
			//if uva \in Lyndon,then ((uva)^t)ua':
			//      a < a':((uva)^t)ua' \in Lyndon ,reset T = sz(((uva)^t)ua') = k - j + 1,means j = i
			//      a == a':T is not change
			//      a > a': ((uva)^t)ua' should decompose => uva,uva.....uva(t times), then solve from ua'
			for(j = i,k = i + 1;k < n && p[k] >= p[j];k++){
				if(p[k] > p[j])j = i;
				else j++;
			}
			// s[cnt] = (uva) do t times 
			while(i <= j){s[++cnt] = i + k - j - 1,i += k - j;}
		}
	}
}ly;
