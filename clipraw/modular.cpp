template<class T, T M> class modular {
	T value;

	public:
	template<class P> modular(P val=P()) : value(val) {
		if(value>=M)value%=M;
		while(value<0)value+=M;
		while(value>=M)value-=M;
	}
	
	T pow(T a, T b) {
		T ret=1;
		for(a%=M; b; b>>=1, a=a*a%M) if(b&1) ret=ret*a%M;
		return ret;
	}
	modular operator+(modular m) {return modular(value+m.value);}
	modular operator-(modular m) {return modular(value-m.value);}
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
	template<class P> friend modular operator-(P v, modular m) {return modular(v-m.value);}
	template<class P> friend modular operator/(P v, modular m) {return modular(v)/m;}
	T get() {return value;}
	//operator T() {return value;}

	bool operator==(modular m) {return value==m.value;}
	bool operator!=(modular m) {return value!=m.value;}
	bool operator<(modular m) {return value<m.value;}
	bool operator>(modular m) {return value>m.value;}
	bool operator<=(modular m) {return value<=m.value;}
	bool operator>=(modular m) {return value>=m.value;}

	friend istream& operator>>(istream& is, modular& m) {is>>m.value; return is;}
	friend ostream& operator<<(ostream& os, modular m) {os<<m.value; return os;}
};
