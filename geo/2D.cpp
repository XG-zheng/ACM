/* ע��
  1. �㡢����
    1. ����Ƕȳ��� -pi �����Լ��� 2pi ����Ϊ pi
    2. atan2(y, x) �Ĳ����Ǹ�����ʱ�����ܳ��� -pi ���� atan2(-0.0, -1.0)
  2. �߶Ρ�ֱ��
    1. �߶��ϸ��ཻ����Ϊ��ÿ���߶ε������˵�������һ���߶����ߣ�������˵�����ǿ�����ͼ���￴���ĸ��˵��һ������
*/

typedef db T;
const db eps = 1e-7, pi = acosl(-1.);
int sgn(T x) { return (x > eps) - (x < -eps); }
bool inMid(T l, T x, T r) { return sgn(l - x) * sgn(r - x) <= 0; }  // �� x ������ [l, r] �ڣ������߽磩

// �㡢����
struct P {
    T x, y; P () {} P(T x, T y) : x(x), y(y) {}
    P operator + (const P &b) const { return P(x + b.x, y + b.y); }  // ������
    P operator - (const P &b) const { return P(x - b.x, y - b.y); }  // ������
    T operator * (const P &b) const { return x * b.x + y * b.y; }    // �������
    T operator / (const P &b) const { return x * b.y - y * b.x; }    // �������
    P operator * (const T &k) const { return P(x * k, y * k); }      // ��������
    P operator / (const T &k) const { return P(x / k, y / k); }      // ��������
    bool operator < (const P &b) const { return sgn(x - b.x) ? x < b.x : y < b.y; }  // ��С�Ҵ���С�ϴ�
    bool operator == (const P &b) const { return !sgn(x - b.x) && !sgn(y - b.y); }   // �������
    P rot(T t) { return P(x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)); }  // ������ʱ����ת t ����
    P rot90() { return P(-y, x); }           // ������ʱ����ת 90 ��
    db arg() const { return atan2(y, x); }   // ��λ�� (-pi, pi] ���ٶ�������Ҫ���ڼ�������
    T abs() { return sqrt(x * x + y * y); }  // ����ģ��
    T abs2() { return x * x + y * y; }       // ����ģ����ƽ��
    P unit() { return (*this) / abs(); }     // ��λ����
    void scan() { db tx, ty; scanf("%lf%lf", &tx, &ty); x = tx; y = ty; }  // ����
    void print() { printf("%.11lf %.11lf\n", x, y); }                      // ���
    P toR() { return (sgn(x) == -1 || !sgn(x) && sgn(y) == -1) ? (*this)*(-1) : (*this); }  // �������� 2 3 ���ޣ���ȡ�෴����
    bool isUp() const { return sgn(y) == 1 || !sgn(y) && sgn(x) == -1; }                    // �����Ƿ��� 1 2 ����
};
T dis(P a, P b) { return (b - a).abs(); }   // �� a ���� b �ľ���
P symmetry(P p, P a) { return a + a - p; }  // �� p ���ڵ� a �����ĶԳƵ�
T cross(P o, P a, P b) { return (a - o) / (b - o); }         // ���� oa �� ob �Ĳ��
int crossSgn(P o, P a, P b) { return sgn(cross(o, a, b)); }  // ���� oa �� ob �Ĳ������
db rad(P a, P b) { return atan2(a / b, a * b); }             // ���� a �� b �ļнǣ������ƣ�
bool order(const P &a, const P &b) { return a.isUp() < b.isUp() || a.isUp() == b.isUp() && sgn(a/b) > 0; }  // ��������

// �߶Ρ�ֱ��
struct L { P s, t; L () {} L(P s, P t) : s(s), t(t) {} };
bool onPS(P p, L a) { return sgn((a.t-a.s)/(p-a.s))==0 && sgn((p-a.s)*(p-a.t))<=0; }   // �� p �Ƿ����߶� a ��
bool inRec(P p, L a) { return inMid(a.s.x, p.x, a.t.x) && inMid(a.s.y, p.y, a.t.y); }  // �� p ����ֱ�� a Ϊ�Խ��ߵľ�����
P proj(P p, L a) { return (a.t-a.s) * ( (p-a.s) * (a.t-a.s) / (a.t-a.s).abs2() ) + a.s; }  // �� p ����ֱ�� a ��ͶӰ��
P reflect(P p, L a) { return proj(p, a) * 2 - p; }                                         // �� p ����ֱ�� a �ĶԳƵ�
bool xSSr(const L &a, const L &b) {  // �߶� a ���߶� b �ϸ��ཻ
    T c1 = (a.t-a.s) / (b.s-a.s), c2 = (a.t-a.s) / (b.t-a.s);
    T c3 = (b.t-b.s) / (a.s-b.s), c4 = (b.t-b.s) / (a.t-b.s);
    return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}
bool xSS(L a, L b) {                 // �߶� a ���߶� b ���ϸ��ཻ
    T c1 = (a.t-a.s) / (b.s-a.s), c2 = (a.t-a.s) / (b.t-a.s);
    T c3 = (b.t-b.s) / (a.s-b.s), c4 = (b.t-b.s) / (a.t-b.s);
    return sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0 &&
           sgn(max(a.s.x,a.t.x) - min(b.s.x,b.t.x)) >= 0 &&
           sgn(max(b.s.x,b.t.x) - min(a.s.x,a.t.x)) >= 0 &&
           sgn(max(a.s.y,a.t.y) - min(b.s.y,b.t.y)) >= 0 &&
           sgn(max(b.s.y,b.t.y) - min(a.s.y,a.t.y)) >= 0;
}
bool xSL(L a, L b) {  // �߶� a ��ֱ�� b �ཻ ( ���ϸ� : <= ; �ϸ� : < )
    return sgn( (b.t - b.s) / (a.s - b.s) ) * sgn( (b.t - b.s) / (a.t - b.s) ) <= 0;
}
P xLL(L a, L b) {  // ֱ�� a ��ֱ�� b �Ľ���
    T s1 = (b.t - b.s) / (a.s - b.s), s2 = (a.t - b.s) / (b.t - b.s);
    return (a.s * s2 + a.t * s1) / (s1 + s2);
}
db disPL(P p, L a) { return fabs( (a.t-a.s) / (p-a.s) ) / (a.t-a.s).abs(); }  // �� p ��ֱ�� a �ľ���
db disPS(P p, L a) {                                                          // �� p ���߶� a �ľ���
    return sgn( (a.t-a.s) * (p-a.s) ) * sgn( (a.s-a.t) * (p-a.t) ) == 1
           ? disPL(p, a) : min( (p-a.s).abs(), (p-a.t).abs() );
}
db disSS(L a, L b){                                                           // �߶� a ���߶� b �ľ���
    if (xSS(a,b)) return 0;
    return min( min( disPS(a.s,b), disPS(a.t,b) ), min( disPS(b.s,a), disPS(b.t,a) ) );
}
db disLL(L a, L b) { return (a.t-a.s) / (b.t-b.s) ? 0 : disPL(a.s, b); }      // ֱ�� a ��ֱ�� b �ľ���

// ����Ρ�͹��
typedef vector<P> polygon;
polygon Convex(polygon A) {  // ��͹������ʱ������ �ڽ� <180 : (<=) ; �ڽ� <=180 : (<) ��
    int n = sz(A); if (n <= 1) return A;
    sort(all(A));
    polygon B;
    for (int i = 0; i < n; B.pb(A[i++]))
        while (sz(B) > 1 && crossSgn(B[sz(B)-2], B.back(), A[i]) < 0) B.pop_back();  // ��������� <
    for (int i = n - 2, t = sz(B); i >= 0; B.pb(A[i--]))
        while (sz(B) > t && crossSgn(B[sz(B)-2], B.back(), A[i]) < 0) B.pop_back();  // ͬ��
    B.pop_back(); return B;
}
T areaPoly(polygon A) {  // ����� A ����������Ϳ��Է�����������������־���
    T res = 0;
    rep(i, 0, sz(A)) res += A[i] / A[ (i+1) % sz(A) ];
    return fabs(res) / 2;
}
bool isConvex(polygon A) {  // ����� A �Ƿ���͹����Ҫ�� A �ĵ㼯����ʱ������
    rep(i, 0, 2) A.pb(A[i]);
    rep(i, 0, sz(A)-2) if ( sgn( (A[i+1]-A[i]) / (A[i+2]-A[i]) ) < 0 ) return 0;
    return 1;
}
int relPPoly(P p, polygon A) {  // ��Ͷ���ι�ϵ ( 2 : in , 1 : on , 0 : out )
    int res = 0; A.pb(A[0]);
    rep(i, 1, sz(A)) {
        P u = A[i-1], v = A[i];
        if (onPS(p, L(u, v))) return 1;
        if (sgn(u.y - v.y) > 0) swap(u, v);
        if (sgn(u.y - p.y) >= 0 || sgn(v.y - p.y) < 0) continue;
        if (crossSgn(v, u, p) < 0) res ^= 1;
    }
    return res << 1;
}
T ConvexDiameter(polygon A) {  // ͹�� A ��ֱ������͹�� A �ϵ���Զ���
    int now = 0, n = sz(A); T res = 0;
    if (n <= 1) return 0;
    rep(i, 0, sz(A)) {
        now = max(now, i);
        while (1) {
            T t1 = dis(A[i], A[now%n]), t2 = dis(A[i], A[(now+1)%n]);
            res = max(res, max(t1, t2));
            if (t2 > t1) now++; else break;
        }
    }
    return res;
}
polygon ConvexCut(polygon A, L a) {  // ��ƽ�� a �и�͹�� A �γɵ�͹����ֱ�� a ��ʱ�뷽��
    int n = sz(A); A.pb(A[0]); polygon res;
    rep(i, 0, n) {
        int w1 = crossSgn(a.s, a.t, A[i]), w2 = crossSgn(a.s, a.t, A[i+1]);
        if (w1 >= 0) res.pb(A[i]);
        if (w1 * w2 < 0) res.pb(xLL(a, L(A[i], A[i+1])));
    }
    return res;
}
T _closePP(polygon &A, int l, int r) {  // ��������� closePP(A)
    if (r - l < 6) {
        T res = 1e20;
        rep(i, l, r+1) rep(j, i+1, r+1) res = min(res, dis(A[i], A[j]));
        return res;
    }
    int m = l + r >> 1;
    T res = min(_closePP(A, l, m), _closePP(A, m+1, r));
    polygon B; rep(i, l, r+1) if (fabs(A[i].x - A[m].x) < res) B.pb(A[i]);
    sort(all(B), [&](P p1, P p2){ return p1.y < p2.y; });
    rep(i, 0, sz(B)) for (int j = i+1; j < sz(B) && B[j].y - B[i].y < res; j++)
        res = min(res, dis(B[i], B[j]));
    return res;
}
T closePP(polygon A) {  // �㼯 A �е�������
    sort(all(A), [&](P a, P b){ return a.x < b.x; });
    return _closePP(A, 0, sz(A)-1);
}

struct C { P o; T r; C () {} C (P o, T r) : o(o), r(r) {} };

int relCC(C A, C B) {  // ��Բ��ϵ�����ع��������� ( 4 : ���� ; 3 : ���� ; 2 : �ཻ ; 1 : ���� ; 0 : �ں� )
    T dis = (A.o - B.o).abs();
    if (sgn(dis - (A.r + B.r)) == 1) return 4;
    if (sgn(dis - (A.r + B.r)) == 0) return 3;
    if (sgn(dis - fabs(A.r - B.r)) == 1) return 2;
    if (sgn(dis - fabs(A.r - B.r)) == 0) return 1;
    return 0;
}

vector<P> xCL(C A, L b) {  // Բ A ��ֱ�� b �Ľ���
    P k = proj(A.o, b);
    T d = A.r * A.r - (k - A.o).abs2();
    if (sgn(d) == -1) return {};
    P del = (b.s - b.t).unit() * sqrt(max(d, 0.0));
    return { k - del, k + del };
}

vector<P> xCC(C A, C B) {  // Բ A ��Բ B �Ľ���
    int pd = relCC(A, B); if (pd == 0 || pd == 4) return {};
    T a = (B.o - A.o).abs2();
    T cosA = (A.r * A.r + a - B.r * B.r) / (2 * A.r * sqrt(max(a, 0.0)));
    T b = A.r * cosA, c = sqrt(max(0.0, A.r * A.r - b * b));
    P k = (B.o - A.o).unit(), m = A.o + k * b, del = k.rot90() * c;
    return { m - del, m + del };
}

vector<P> tCP(C A, P p) {  // ���� p ��������Բ A ���е�
    T a = (p - A.o).abs(), b = A.r * A.r / a, c = sqrt(max(0.0, A.r * A.r - b * b));
    P k = (p - A.o).unit(), m = A.o + k * b, del = k.rot90() * c;
    return { m - del, m + del };
}

vector<L> extCC(C A, C B) {  // Բ A ��Բ B ���⹫����
    int pd = relCC(A, B); if (pd == 0) return {};
    if (pd == 1) { P k = xCC(A, B)[0]; return { L(k, k) }; }
    if (sgn(A.r - B.r) == 0) {
        P del = (B.o - A.o).unit().rot90().toR();
        return { L(A.o - del * A.r, B.o - del * B.r), L(A.o + del * A.r, B.o + del * B.r) };
    } else {
        P p = (B.o * A.r - A.o * B.r) / (A.r - B.r);
        vector<P> a = tCP(A, p), b  = tCP(B, p);
        vector<L> res;
        rep(i, 0, sz(a)) res.pb(L(a[i], b[i]));
        return res;
    }
}

vector<L> intCC(C A, C B) {  // Բ A ��Բ B ���ڹ�����
    int pd = relCC(A, B); if (pd <= 2) return {};
    if (pd == 3) { P k = xCC(A, B)[0]; return { L(k, k) }; }
    P p = (B.o * A.r + A.o * B.r) / (A.r + B.r);
    vector<P> a = tCP(A, p), b = tCP(B, p);
    vector<L> res;
    rep(i, 0, sz(a)) res.pb(L(a[i], b[i]));
    return res;
}

vector<L> tCC(C A, C B) {  // Բ A ��Բ B �Ĺ�����
    int f = 0; if (A.r < B.r) swap(A, B), f = 1;
    vector<L> a = extCC(A, B), b = intCC(A, B);
    for (L o : b) a.pb(o);
    if (f) for (L &o : a) swap(o.s, o.t);
    return a;
}

T areaCTri(T r, P s, P t) {  // Բ (o, r) �������� (o, s, t) �ཻ��������� areaCPoly() ���ã���������Բ�������ཻ�����
    vector<P> p12 = xCL(C(P(0, 0), r), L(s, t));
    if (sz(p12) == 0) return r * r * rad(s, t);
    P p1 = p12[0], p2 = p12[1];
    bool b1 = sgn(s.abs2() - r * r) == 1, b2 = sgn(t.abs2() - r * r) == 1;
    if (b1 && b2) {
        if (sgn((s - p1) * (t - p1)) <= 0 && sgn((s - p2) * (t - p2)) <= 0)
            return r * r * (rad(s, p2) + rad(p1, t)) + p2 / p1;
        else return r * r * rad(s, t);
    } else if (b1) return r * r * rad(s, p2) + p2 / t;
    else if (b2) return r * r * rad(p1, t) + s / p1;
    return s / t;
}

T areaCPoly(C A, polygon B) {  // Բ A ������ B �ཻ�����
    T res = 0; B.pb(B[0]);
    rep(i, 1, sz(B)) {
        P u = B[i-1], v = B[i];
        res += areaCTri(A.r, u - A.o, v - A.o);
    }
    return fabs(res) / 2;
}

C getC(P a,P b,P c){  // ����ȷ��һ��Բ �� ���������Բ ��
    db a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
    db a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
    db d = a1 * b2 - a2 * b1;
    P o = P(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d);
    return C(o, dis(a, o));
}
