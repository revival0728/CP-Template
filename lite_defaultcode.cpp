#include <bits/stdc++.h>
using namespace std;

namespace lite_template {
#define IO cin.tie(0), ios_base::sync_with_stdio(0)
#define sz(x) (int)x.size()
#define All(x) x.begin(), x.end()
#define F first
#define S second
using ll = long long;
using ld = long double;
template<class T, long long unsigned int N> using Ar = array<T, N>;
template<class T> using Vt = vector<T>;

template<class T> void DEF(T v) {
	cerr << v << "]\n";
}
template<class T, class ... P> void DEF(T v, P ...t) {
	cerr << v << ", ";
	DEF(t...);
}
#define de(...) cerr<<"[LINE: "<<__LINE__<<"]["<<#__VA_ARGS__<<"][", DEF(__VA_ARGS__)

template<class T, class P> void setVt(T& c, int s, P v) { // args(Vt, size1, size2,..., value)
	c.resize(s, v);
}
template<class T, class ...P> void setVt(T& c, int s, P ...t) {
	c.resize(s);
	for(auto& e : c)
		setVt(e, t...);
}
}

int main() {
	;
}
