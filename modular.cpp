#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<class T, T M> class modular {
	T value;

	public:
	modular(T val=0) : value(val%M) {}
	template<class P> modular(P val) : value(val) {value%=M;}
	
	T pow(ll a, ll b) {
		ll ret=1;
		for(a%=M; b; b>>=1, a=a*a%M) if(ret&1) ret=ret*a%M;
		return ret;
	}
	modular operator+(modular m) {return modular(value+m.value);}
	modular operator-(modular m) {T v=value-m.value; while(v<0)v+=M; return modular(v);}
	modular operator*(modular m) {return modular(value*m.value);}
	modular operator/(modular m) {return modular(value*pow(m.value, M-2));} // works if M is prime
	modular operator+=(modular m) {*this=operator+(m);}
	modular operator-=(modular m) {*this=operator-(m);}
	modular operator*=(modular m) {*this=operator*(m);}
	modular operator/=(modular m) {*this=operator/(m);}
	modular operator++() {*this=operator+(1); return *this;}
	modular operator++(int) {modular r=*this; operator++(); return r;}
	modular operator--() {*this=operator-(1); return *this;}
	modular operator--(int) {modular r=*this; operator--(); return r;}
	operator T() {return value;}

	bool operator==(modular m) {return value==m.value;}
	bool operator!=(modular m) {return value!=m.value;}
	bool operator<(modular m) {return value<m.value;}
	bool operator>(modular m) {return value>m.value;}
	bool operator<=(modular m) {return value<=m.value;}
	bool operator>=(modular m) {return value>=m.value;}

	friend istream& operator>>(istream& is, modular& m) {is>>m.value; return is;}
	friend ostream& operator<<(ostream& os, modular m) {os<<m.value; return os;}
};

//using Mod = modular<ll, (ll)1e9+7>;

int main() {}
