namespace cp_template {
  template<class IT, int B=12721, int MOD1=987654361,int MOD2=999991231>
  class HashIterable {  //1-base && []
    using ll = long long;
    using ull = unsigned long long;
    using ET = typename IT::value_type;

    protected:
    int rb, size;
    std::vector<ll> v1, v2, p1, p2;

    private:
    void init_vp(std::vector<ll>& v, std::vector<ll>& p) {
      v.reserve(size);
      p.reserve(size);
      v.push_back(0);
      p.push_back(1);
    }

    protected:
    void build_single_hash(const IT& i, std::vector<ll>& v, std::vector<ll>& p, int MOD) {
      size = i.size() + 1;
      rb = size - 1;
      init_vp(v, p);
      for(auto it = i.begin(); it != i.end(); ++it) {
        ll e = (ll)(*it);
        v.push_back(v.back() * B % MOD + e);
        v.back() %= MOD;
        p.push_back(p.back() * B);
        p.back() %= MOD;
      }
    }
    void single_push_back(const ET& ei, std::vector<ll>& v, std::vector<ll>& p, int MOD) {
      ll e = (ll)(ei);
      v.push_back(v.back() * B % MOD + e);
      v.back() %= MOD;
      p.push_back(p.back() * B);
      p.back() %= MOD;
    }
    void single_append(const IT& i, std::vector<ll>& v, std::vector<ll>& p, int MOD) {
      for(auto it = i.begin(); it != i.end(); ++it) {
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
    HashIterable(int _reserve_size) : size(_reserve_size + 1), rb(0) {
      init_vp(v1, p1);
      init_vp(v2, p2);
    }
    HashIterable(const IT& i) { build_hash(i); }
    ull operator()(const IT& i) {
      build_hash(i);
      return single_hash(v1, p1, MOD1, 1, i.size()) * single_hash(v2, p2, MOD2, 1, i.size());
    }
    void push_back(ET e) {
      ++rb;
      single_push_back(e, v1, p1, MOD1);
      single_push_back(e, v2, p2, MOD2);
    }
    void append(const IT& i) {
      rb += i.size();
      single_append(i, v1, p1, MOD1);
      single_append(i, v2, p2, MOD2);
    }
    std::pair<ll, ll> hashp(int l, int r) {
      assert(1 <= l && l <= r && r <= rb);
      return {
        single_hash(v1, p1, MOD1, l, r),
        single_hash(v2, p2, MOD2, l, r)
      }; 
    }
    ull hash(int l, int r) {
      assert(1 <= l && l <= r && r <= rb);
      return single_hash(v1, p1, MOD1, l, r) * single_hash(v2, p2, MOD2, l, r); 
    }
  };
}
