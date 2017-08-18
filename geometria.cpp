/*Template dos Campeoes
menos que isso falta
mais que isso sobra*/
//TESTADO = TRUE

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <stack>

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef vector < int > vi;
typedef vector < vi > vvi;
typedef pair < int, int > ii;
typedef vector < ii > vii;
typedef vector < vii > vvii;
typedef vector < bool > vb;
typedef vector < ll > vll;

#define f first
#define s second
#define pb push_back
#define mp make_pair
#define buff ios::sync_with_stdio(false)
#define db(x) cout<<#x<<": "<<x<<endl
#define for0(i, n) for(int i = 0; i < n; i++)

const int inf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;
const ld pi=acos(-1.0);
const int mod=1e9+7;
const int maxn=100050;

/*Como um ult, vamos para geometria
Espero que essa biblioteca funcione*/
//TESTADO = rand()%2

const ld eps = 1e-9;

struct point_i {
	int x, y;
	point_i() { x = y = 0; }
	point_i(int a, int b): x(a), y(b) {}
	bool operator < (point_i other) const {
		if(x != other.x)	return x < other.x;
		else return y < other.y;
	}
	bool operator == (point_i other) const {
		return x == other.x and y == other.y;
	}
	void operator = (point_i other) {
		x = other.x, y = other.y;
	}
	point_i operator + (point_i other) const {
		return point_i(x + other.x, y + other.y);
	}
	point_i operator * (int esc) const {
		return point_i(x * esc, y * esc);
	}
};

struct point {
	ld x, y;
	point() { x = y = 0; }
	point(ld a, ld b): x(a), y(b) {}
	bool operator < (point other) const {
		if(fabs(x - other.x) > eps) return x < other.x;
		return y < other.y;
	}
	bool operator == (point other) const {
		return fabs(x - other.x) < eps and fabs(y - other.y) < eps;
	}
	void operator = (point other) {
		x = other.x, y = other.y;
	}
	point operator + (point other) const {
		return point(x + other.x, y + other.y);
	}
	point operator * (ld esc) const {
		return point(x * esc, y * esc);
	}
};

struct line {
	ld a, b, c;
	line() { a = b = c = 0; }
	line(ld x, ld y, ld z):
		a(x), b(y), c(z) {}
	void operator = (line other) {
		a = other.a, b = other.b, c = other.c;
	}
};

struct vec {
	ld x, y;
	vec() { x = y = 0; }
	vec(ld a, ld b): x(a), y(b) {}
	vec(point a, point b): x(b.x - a.x), y(b.y - a.y) {}
	bool operator == (point other) const {
		return fabs(x - other.x) < eps and fabs(y - other.y) < eps;
	}
	void operator = (vec other) {
		x = other.x, y = other.y;
	}
	vec operator + (vec other) const {
		return vec(x + other.x, y + other.y);
	}
	vec operator * (ld esc) const {
		return vec(x * esc, y * esc);
	}
	ld operator * (vec other) const {
		return x * other.x + y * other.y;
	}
	ld norm2() {
		return x * x + y * y;
	}
};

ld dist2(point p, point q) {
	return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

point rotate(point p, ld ang) {
	point r;
	r.x = p.x * cos(ang) - p.y * sin(ang);
	r.y = p.x * sin(ang) + p.y * cos(ang);
	return r;
}

line create_line(point p, point q) {
	if(fabs(p.x - q.x) < eps) {
		return line(1, 0, -p.x);
	}
	else {
		line l;
		l.a = -(p.y - q.y) / (p.x - q.x);
		l.b = 1.0;
		l.c = -(l.a * p.x) - p.y;
		return l;
	}
}

bool parallel(line r, line s) {
	return fabs(r.a - s.a) < eps and fabs(r.b - s.b) < eps;
}

bool same(line r, line s) {
	return parallel(r, s) and fabs(r.c - s.c) < eps;
}

bool intersect(line l1, line l2, point &p) {
	if(parallel(l1, l2))	return false;
	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if(fabs(l1.b) > eps) p.y = -(l1.a * p.x + l1.c);
	else p.y = -(l2.a * p.x + l2.c);
	return true;
}

point translate(point p, vec v) {
	return point(p.x + v.x, p.y + v.y);
}

ld distPL(point p, point a, point b, point &c) {
	vec ap(a, p), ab(a, b);
	ld u = ap * ab / ab.norm2();
	c = translate(a, ab * u);
	return sqrt(dist2(p, c));
}

ld distPLS(point p, point a, point b, point &c) {
	vec ap(a, b), ab(a, b);
	ld u = ap * ab / ab.norm2();
	if(u < 0.0) {
		c = a;
		return sqrt(dist2(p, a));
	}
	else if(u > 1.0) {
		c = b;
		return sqrt(dist2(p, b));
	}
	else return distPL(p, a, b, c);
}

ld angle(point a, point o, point b) {
	vec oa(o, a), ob(o, b);
	return acos( oa * ob / sqrt(oa.norm2() * ob.norm2()) ); 
}

ld cross(vec a, vec b) {
	return a.x * b.y - a.y * b.x;
}

bool ccw(point p, point q, point r) {
	return cross(vec(p, q), vec(p, r)) > 0;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(vec(p, q), vec(p, r))) < eps;
}

int main() {
	buff;
	
	return 0;
}
