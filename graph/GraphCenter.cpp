//w initialize inf
// w[i][j] the weight of edge i -> j,w[i][i] = 0
// mx twice the maxium distance from the center 
// e center on the edeg e  
// dis Distance between center point and two sections
// time o(n^3)
const int inf = ~0U>>1;
pii GraphCenter(int n,int w[][N]){
	static int rk[N][N],d[N][N];
	rep(i , 1 , n + 1)
		rep(j , 1 , n + 1)
			d[i][j] = w[i][j],rk[i][j] = j;
	rep( k , 1 , n + 1)
		rep(i , 1 , n + 1)
			rep( j ,1 , n + 1) d[i][j] = min(d[i][j],d[i][k] + d[k][j]); 
	
	rep(i , 1 , n + 1)
		sort(rk[i] + 1,rk[i] + n + 1,[&](int a,int b){return  d[i][a] < d[i][b];});
	int mx = inf;
	pii e,dis; 
	rep(i , 1 , n + 1){
		if(d[i][rk[i][n]]*2 < mx)
			mx = d[i][rk[i][n]]*2,e = pii(i,i),dis = pii(0,0);
		rep( j , 1 , n + 1){
			for(int a = n , b = n - 1;b >= 1; --b){
				int y = rk[i][a], x = rk[i][b];
				if(d[j][y] < d[j][x]){
					int now = d[i][x] + d[j][y] + w[i][j];
					if(now < mx){
						mx = now,e = pii(i,j),dis = pii(now - d[i][x]*2,2*w[i][j] - (now - d[i][x]*2));
					}
					a = b;
				}
			}
		}
	}
	cout<<mx/2.0<<"\n";
	return e;
}
