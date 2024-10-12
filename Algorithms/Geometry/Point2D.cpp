// Author: Ulf Lundstrom, Victor Lecomte, chilli, Sahil Yasar
// Description: Class to handle points in the plane.
// T can be e.g. double or long long. (Avoid int.)
// Tested here:
// lineDist: https://cses.fi/problemset/task/2189/
// segInter: https://cses.fi/problemset/task/2190/
// circleInter: https://codeforces.com/problemset/problem/933/C

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
#define endl '\n'

// Cursed code
typedef long double ld;
#define double ld

const double EPS = 1e-12;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T> struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return (abs(x - p.x) < EPS)? (y < p.y): (x < p.x); }
    //                          return tie(x,y) < tie(p.x,p.y); ^^^
	bool operator==(P p) const { return abs(x - p.x) < EPS && abs(y - p.y) < EPS; }
    //                          return tie(x,y)==tie(p.x,p.y); ^^^
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
    // 0 if the 3 points are colinear
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

// If a unique intersection point of the lines going through s1,e1 and s2,e2 exists {1, point} is returned.
// If no intersection point exists {0, (0,0)} is returned and if infinitely many exists {-1, (0,0)} is returned.
template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P()};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

// Returns the signed distance between point p and the line containing points a and b.
// Positive value on left side and negative on right as seen from a towards b. a==b gives nan.
template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return (double)a.cross(b, p)/(b-a).dist();
}

// Returns true iff p lies on the line segment from s to e.
template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

// If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned.
// If no intersection point exists an empty vector is returned.
// If infinitely many exist a vector with 2 elements is returned, containing the endpoints of the common line segment.
template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {s.begin(), s.end()};
}

// Returns the shortest distance between point p and the line segment from point s to e.
typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
	if (s == e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max((ld).0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

// Finds the intersection between a circle and a line.
// Returns a vector of either 0, 1, or 2 intersection points.
// P is intended to be Point<double>.
vector<P> circleLine(P c, double r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

// Computes the pair of points at which two circles intersect.
// Returns 0 if no intersection points, -1 if infinite, 1 otherwise
int circleInter(P a, P b, double r1, double r2, pair<P, P>& out) {
	if (a == b) { return -(abs(r1 - r2) < EPS); }
	double d = (b - a).dist(), dt = (r1*r1 - r2*r2)/d, d1 = (d + dt)/2;
	if (r1+r2 < d - EPS || abs(r1-r2) > d + EPS) return 0;
    P dir = (b - a)/d, pcrs = a + dir*d1;
    dt = sqrt(fmax(0, r1*r1 - d1*d1)), dir = dir.perp();
	out = {pcrs + dir*dt, pcrs - dir*dt};
	return 1;
}

typedef long long ll;
const int MAX = 12;
vector<int> g[MAX];
vector<bool> vis(MAX, false);
void dfs(int source){
    vis[source] = true;
    for (int u: g[source])
        if (!vis[u])
            dfs(u);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, i, j, k, x, y, V, E, F, C;
    cin>>n;
    int r[n];
    vector<P> c;
    for (i = 0; i < n; ++i){
        cin>>x>>y>>r[i];
        c.emplace_back(x, y);
    }

    vector<P> all;
    E = 0;
    for (i = 0; i < n; ++i){
        vector<P> temp;
        for (j = 0; j < n; ++j){
            if (i == j) continue;
            pair<P, P> out;
            k = circleInter(c[i], c[j], r[i], r[j], out);
            if (k == 1){
                temp.push_back(out.first);
                temp.push_back(out.second);
                g[i].push_back(j);
            }
        }
        sort(temp.begin(), temp.end());
        E += unique(temp.begin(),temp.end()) - temp.begin();
        for (auto& p: temp)
            all.push_back(p);
    }
    sort(all.begin(), all.end());
    V = unique(all.begin(),all.end()) - all.begin();

    C = 0;
    for (i = 0; i < n; ++i)
        if (!vis[i]){
            dfs(i);
            ++C;
        }

    F = E-V+C+1;
    cout<<F<<endl;

    return 0;
}
