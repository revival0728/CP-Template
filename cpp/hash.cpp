namespace cp_template {
  template<class IT, int B=12721, int MOD1=987654361,int MOD2=999991231>
  class HashIterable {  //1-base && []
    using ll = long long;
    using ull = unsigned long long;
    private:
    std::vector<ll> v1, v2, p1, p2;
    void build_single_hash(const IT& i, std::vector<ll>& v, std::vector<ll>& p, int MOD) {
      v.reserve(i.size() + 1);
      p.reserve(i.size() + 1);
      v.push_back(0);
      p.push_back(1);
      for(auto it = i.rbegin(); it != i.rend(); ++it) {
        ll e = (ll)(*it);
        v.push_back(v.back() * B % MOD + e);
        v.back() %= MOD;
        p.push_back(p.back() * B);
        p.back() %= MOD;
      }
    }
    void build_hash(const IT& i) {
      build_single_hash(i, v1, p1, MOD1);
      build_single_hash(i, v2, p2, MOD2);
    }
    ll single_hash(std::vector<ll>& v, std::vector<ll>& p, int MOD, int l, int r) {
      return (v[r] + MOD - v[l - 1] * p[r - l + 1] % MOD) % MOD;
    }

    public:
    HashIterable() {}
    HashIterable(const IT& i) { build_hash(i); }
    ull operator()(const IT& i) {
      build_hash(i);
      return single_hash(v1, p1, MOD1, 1, i.size()) * single_hash(v2, p2, MOD2, 1, i.size());
    }
    std::pair<ll, ll> hash(int l, int r) { 
      return {
        single_hash(v1, p1, MOD1, l, r),
        single_hash(v2, p2, MOD2, l, r)
      }; 
    }
    ull mdhash(int l, int r) { return single_hash(v1, p1, MOD1, l, r) * single_hash(v2, p2, MOD2, l, r); }
  };
}
