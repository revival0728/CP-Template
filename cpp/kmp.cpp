struct KMP {
  vector<int> ret, failure;
  void operator()(const string& t, const string& p) {
    assert(t.size() >= t.size());
    for (int i=1, j=failure[0]=-1; i<p.size(); ++i){
      while (j >= 0 && p[j+1] != p[i])
        j = failure[j];
      if (p[j+1] == p[i]) j++;
      failure[i] = j;
    }
    for (int i=0, j=-1; i<t.size(); ++i){
      while (j >= 0 && p[j+1] != t[i])
        j = failure[j];
      if (p[j+1] == t[i]) j++;
      if (j == p.size()-1){
        ret.push_back( i - p.size() + 1 );
        j = failure[j];
      }   
    }   
    return;
  }
  KMP(const string& t, const string& p) { 
    failure.resize(t.size());
    this->operator()(t, p); 
  }
  KMP(int max_length) { failure.resize(max_length); }
};
