const int N = 1e5 + 5;
const double eps = 1e-5;
const int inf = 0x3f3f3f3f;
struct P{
	double x , y , z;P(){}
	P(double x, double y ,double z):x(x),y(y),z(z){}
	P operator + (const P &b) const {return P(x + b.x , y + b.y , z + b.z);}
	P operator - (const P &b) const {return P(x - b.x , y - b.y , z - b.z);}
	P operator * (const double &k) const {return P(x * k, y * k, z * k);}
	double abs(){return sqrt(x*x + y*y + z*z);}
}p[N];
double dis(P a,P b){return (a - b).abs();}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline double Rnd(){return double(rng()%10000000)/10000000;}
int n;
double SA(){
	double t = 1000 , start_t = 1000;
	P now = P(0 , 0 , 0),nxt;
	double ans = 1000000000,cur = 1000000000;
	while(t > eps){
		for(int k = 0;k < 1000;++k){
			double d = 0;
			int pos = 0;
			rep(i , 1 , n + 1)
				if(d < dis(now , p[i]))d = dis(now , p[i]),pos = i;
			nxt = now + (p[pos] - now)*(t/start_t);
			d = 0;
			rep(i , 1 , n + 1)
				if(d < dis(now , p[i]))d = dis(now , p[i]),pos = i;
			double delta = d - cur;
			ans = min(ans,d);
			cur = d;	
			now = nxt;
		}
		t *= 0.92;
	}
	return ans;
}
