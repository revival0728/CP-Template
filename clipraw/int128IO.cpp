namespace int128IO {
	istream& operator>>(istream& is, __int128& i) {
		string s; is>>s; i = 0;
		for(auto& c : s) i=i*10+(c-'0');
		return is;
	}
	ostream& operator<<(ostream& os, __int128 i) {
		string s; while(i) s+=('0'+i%10), i/=10;
		for(auto it=s.rbegin();it!=s.rend();++it) os<<*it;
		return os;
	}
}
