namespace cp_template {
  template<class IT, int B1=12721, int B2=556679, int MOD=(int)1e9+7>
  class HashIterable {  //1-base && []
    using ll = long long;
    using ull = unsigned long long;
    private:
    std::vector<ll> v1, v2, p1, p2;
    void build_single_hash(const IT& i, std::vector<ll>& v, std::vector<ll>& p, int b) {
      v.reserve(i.size() + 1);
      p.reserve(i.size() + 1);
      v.push_back(0);
      p.push_back(1);
      for(auto it = i.rbegin(); it != i.rend(); ++it) {
        ll e = (ll)(*it);
        v.push_back(v.back() * b % MOD + e);
        v.back() %= MOD;
        p.push_back(p.back() * b);
        p.back() %= MOD;
      }
    }
    void build_hash(const IT& i) {
      build_single_hash(i, v1, p1, B1);
      build_single_hash(i, v2, p2, B2);
    }
    ll single_hash(std::vector<ll>& v, std::vector<ll>& p, int l, int r) {
      return (v[r] + MOD - v[l - 1] * p[r - l + 1] % MOD) % MOD;
    }

    public:
    HashIterable() {}
    HashIterable(const IT& i) { build_hash(i); }
    ull operator()(const IT& i) {
      build_single_hash(i, v1, p1, B1);
      return single_hash(v1, p1, 1, i.size());
    }
    std::pair<ll, ll> hash(int l, int r) { 
      return {
        single_hash(v1, p1, l, r),
        single_hash(v2, p2, l, r)
      }; 
    }
  };
}
