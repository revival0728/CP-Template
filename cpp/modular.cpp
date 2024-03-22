/*
 *
 * The Modular Class template
 * Author: revival0728
 *
 * Test with: https://cses.fi/problemset/task/1079/
 * Status: AC
 * 
 */

#include <bits/stdc++.h>
using namespace std;


namespace cp_template {
	using ll = long long;

	template<class T, T M> class modular {
		T value;

		public:
		modular(T val=T()) {
			value = val;
			value %= M; if(value < 0) value += M;
		}
		template<class P> modular(P val) {
			value = val;
			value %= M; if(value < 0) value += M;
		}
		
		T pow(T a, T b) {
			T ret=1;
			for(a%=M; b; b>>=1, a=a*a%M) if(b&1) ret=ret*a%M;
			return ret;
		}
		modular pow(T p) {return pow(value, p);}
		modular operator+(modular m) {return modular(value+m.value);}
		modular operator-(modular m) {return modular(value-m.value);}
		modular operator*(modular m) {return modular(value*m.value);}
		modular operator/(modular m) {return modular(value*pow(m.value, M-2));} // works if M is prime
		modular operator+=(modular m) {*this=operator+(m); return *this;}
		modular operator-=(modular m) {*this=operator-(m); return *this;}
		modular operator*=(modular m) {*this=operator*(m); return *this;}
		modular operator/=(modular m) {*this=operator/(m); return *this;}
		modular operator++() {*this=operator+(1); return *this;}
		modular operator++(int) {modular r=*this; operator++(); return r;}
		modular operator--() {*this=operator-(1); return *this;}
		modular operator--(int) {modular r=*this; operator--(); return r;}
		template<class P> friend modular operator-(P v, modular m) {return modular(v-m.value);}
		template<class P> friend modular operator/(P v, modular m) {return modular(v)/m;}
		T get() {return value;}

		bool operator==(modular m) {return value==m.value;}
		bool operator!=(modular m) {return value!=m.value;}
		bool operator<(modular m) {return value<m.value;}
		bool operator>(modular m) {return value>m.value;}
		bool operator<=(modular m) {return value<=m.value;}
		bool operator>=(modular m) {return value>=m.value;}

		friend istream& operator>>(istream& is, modular& m) {is>>m.value; return is;}
		friend ostream& operator<<(ostream& os, modular m) {os<<m.value; return os;}
	};
}

using namespace cp_template;

using Mod = modular<ll, (ll)1e9+7>;

constexpr int mxNUM = 1e6;
 
Mod fac[mxNUM + 1], rfac[mxNUM + 1];
 
void init() {
  fac[0] = fac[1] = 1;
  for(int i = 2; i <= mxNUM; ++i)
    fac[i] = fac[i - 1] * i;
  rfac[mxNUM] = 1 / fac[mxNUM];
  for(int i = mxNUM - 1; i >= 0; --i)
    rfac[i] = rfac[i + 1] * (i + 1);
	for(int i = 0; i <= mxNUM; ++i)
		assert(fac[i] * rfac[i] == 1);
}
 
int main() {
  cin.tie(0), ios_base::sync_with_stdio(0);
 
  init();
  int n;
  cin >> n;
  while(n--) {
    int a, b;
    cin >> a >> b;
    cout << fac[a] * rfac[b] * rfac[a - b] << '\n';
  }
}
