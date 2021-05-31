#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

namespace cp_template {
	using ll = long long;
	using ld = long double;
	template<class T, long long unsigned int N>
	using Ar = array<T, N>;
	template<class T>
	using Vt = vector<T>;
	template<class T, class C>
	using Pq = priority_queue<T, vector<T>, C>;
	template<class T>
	using Ud_set = unordered_set<T>;
	template<class K, class V>
	using Ud_map = unordered_map<K, V>;
	template<class T, class C>
	using Pset = tree<T, null_type, C, rb_tree_tag, tree_order_statistics_node_update>;

#define sz(x) (int)x.size()
#define All(x) x.begin(), x.end()
#define rsz(x, v) resize((x), (v))
#define pb(x) push_back((x))
#define eb(x) emplace_back((x))
#define F first
#define S second

#define loop(x, b, e, s) for(int x=(b); (s)>0?x<(e):x>(e); x+=(s))
#define loop1(e) loop(i, 0, e, 1)
#define loop2(x, e) loop(x, 0, e, 1)
#define loop3(x, b, e) loop(x, b, e, 1)
#define loop4(x, b, e, s) loop(x, b, e, s)
#define PICKER1(a, b, c, d, e, ...) e
#define LOOP(...) PICKER1(__VA_ARGS__, loop4, loop3, loop2, loop1)
#define FOR(...) LOOP(__VA_ARGS__)(__VA_ARGS__)
#define iter1(x) for(auto& i : x)
#define iter2(x, v) for(auto& x : v)
#define PICKER2(a, b, c, ...) c
#define ITER(...) PICKER2(__VA_ARGS__, iter2, iter1)
#define EACH(...) ITER(__VA_ARGS__)(__VA_ARGS__)

	template<class T, class P> bool umax(T& a, P b) {
		return a<b? a=b, 1:0;
	}
	template<class T, class P> bool umin(T& a, P b) {
		return a>b? a=b, 1:0;
	}
	template<class T, class V> typename T::iterator lwb(T& c, const V v) {
		return lower_bound(c.begin(), c.end(), v);
	}
	template<class T, class V> typename T::iterator upb(T& c, const V v) {
		return uppper_bound(c.begin(), c.end(), v);
	}

	template<class T> istream& operator>>(istream&, vector<T>&);
	template<class T, long long unsigned int N> istream& operator>>(istream&, array<T, N>&);
	template<class T1, class T2> istream& operator>>(istream&, pair<T1, T2>&);

	template<class T>
	istream& operator>>(istream& is, vector<T>& vt) {
		for(auto& i : vt)
			is >> i;
		return is;
	}
	template<class T, long long unsigned int N>
	istream& operator>>(istream& is, array<T, N>& ary) {
		for(auto& i : ary)
			is >> i;
		return is;
	}
	template<class T1, class T2>
	istream& operator>>(istream& is, pair<T1, T2>& pr) {
		is >> pr.first >> pr.second;
		return is;
	}
	template<class T> void read(T& x) {
		cin >> x;
		cin.get();
	}
	template<class T, class ... P> void read(T& x, P& ... t) {
		cin >> x;
		read(t...);
	}
	template<class T> void readl(T& x) { // readline
		getline(cin, x);
	}
	template<class T, class ... P> void readl(T& x, P& ... t) {
		getline(cin, x);
		readl(t...);
	}

	// Don't use them to output answer
	template<class T> ostream& operator<<(ostream&, vector<T>&);
	template<class T, long long unsigned int N> ostream& operator<<(ostream&, array<T, N>&);
	template<class T1, class T2> ostream& operator<<(ostream&, pair<T1, T2>&);

	template<class T>
	ostream& operator<<(ostream& os, vector<T>& vt) {
		auto end = vt.end();
		for(auto i = vt.begin(); i != end; ++i)
			os << *i << (i+1==end?"\n":" ");
		return os;
	}
	template<class T, long long unsigned int N>
	ostream& operator<<(ostream& os, array<T, N>& ary) {
		auto end = ary.end();
		for(auto i = ary.begin(); i != end; ++i)
			os << *i << (i+1==end?"\n":" ");
		return os;
	}
	template<class T1, class T2>
	ostream& operator<<(ostream& os, pair<T1, T2>& pr) {
		os << pr.first << ' ' << pr.second << '\n';
		return os;
	}
	template<class T> void write(T x) {
		cout << x;
	}
	template<class T, class ... P> void write(T x, P ... t) {
		cout << x;
		write(t...);
	}
	void print() { cout << '\n'; }
	template<class T> void print(vector<T>& vt) {
		for(auto& i : vt)
			cout << i << ' ';
		cout << '\n';
	}
	template<class T> void print(T x) {
		cout << x << '\n';
	}
	template<class T, class ... P> void print(T x, P ... t) {
		cout << x << ' ';
		print(t...);
	}
	template<class T> void DEF(T v) {
		cerr << v << "\n-----\n";
	}
	template<class T, class ... P> void DEF(T v, P ...t) {
		cerr << v << ", ";
		DEF(t...);
	}
#define de(...) cerr<<"[LINE: "<<__LINE__<<"]["<<#__VA_ARGS__<<"]\n", DEF(__VA_ARGS__)

	//#define AC_freopen
#ifdef AC_freopen
	void setIO(string f = "") {
		if(f.size()) {
			freopen((f+".in").c_str(), "r", stdin);
			freopen((f+".out").c_str(), "w", stdout);
		} else {
			cin.tie(nullptr);
			ios_base::sync_with_stdio(false);
		}
	}
#endif
#ifndef AC_freopen
#define IO_opt cin.tie(nullptr), ios_base::sync_with_stdio(false);
#endif
	template<class F>
	void multi_tc(F& option) {
		int t;
		cin >> t;
		while(t--)
			option();
	}
}
using namespace cp_template;

int main() {
	;
}
