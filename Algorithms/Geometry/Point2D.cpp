// Author: Ulf Lundstrom, Victor Lecomte, chilli
// Description: Class to handle points in the plane.
// T can be e.g. double or long long. (Avoid int.)
// Tested here:
// lineDist: https://cses.fi/problemset/task/2189/
// segInter: https://cses.fi/problemset/task/2190/


#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T> struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
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
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

typedef long long ll;
const double EPS = 1e-12;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    /*ll t, x, y;
    double ans;
    cin>>t;
    while(t--){
        cin>>x>>y;
        Point<ll> a(x, y);
        cin>>x>>y;
        Point<ll> b(x, y);
        cin>>x>>y;
        Point<ll> p(x, y);

        ans = lineDist(a, b, p);
        if (abs(ans) < EPS)
            cout<<"TOUCH"<<endl;
        else
            cout<<((ans < -EPS)? "RIGHT": "LEFT")<<endl;
    }*/

    ll t, x, y;
    cin>>t;
    while(t--){
        cin>>x>>y;
        Point<double> a(x, y);
        cin>>x>>y;
        Point<double> b(x, y);
        cin>>x>>y;
        Point<double> c(x, y);
        cin>>x>>y;
        Point<double> d(x, y);

        auto ans = segInter(a, b, c, d);
        cout<<((ans.empty())? "NO": "YES")<<endl;
    }

    return 0;
}
