namespace int128IO {
	istream& operator>>(istream& is, __int128& i) {
		string s; is>>s; i = 0;
		auto c=s.begin(); c+=(s[0]=='-');
		for(; c!=s.end(); ++c) i=i*10+(*c-'0');
		if(s[0]=='-') i=-i;
		return is;
	}
	ostream& operator<<(ostream& os, __int128 i) {
		string s; bool neg=false; if(i<0) neg=true, i=-i;
		while(i) s+=('0'+i%10), i/=10;
		if(neg) os<<'-';
		for(auto c=s.rbegin();c!=s.rend();++c) os<<*c;
		return os;
	}
}
