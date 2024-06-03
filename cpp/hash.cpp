namespace cp_template {
  template<class IT, int B=12721, int MOD1=987654361,int MOD2=999991231>
  class HashIterable {  //1-base && []
    using ll = long long;
    using ull = unsigned long long;
    using ET = typename IT::value_type;

    protected:
    int rb, size;
    std::vector<ll> v1, v2, p1, p2;

    ll fpow(ll a, ll b, int MOD) {
      ll ret = 1;
      for(; b; a = a * a % MOD, b >>= 1)
        if(b & 1)
          ret = ret * a % MOD;
      return ret;
    }
    void single_push_back(const ET& ei, std::vector<ll>& v, std::vector<ll>& p, int MOD) {
      ll e = (ll)(ei), inv_B = fpow(B, MOD - 2, MOD);
      p.push_back(p.back() * inv_B);
      p.back() %= MOD;
      v.push_back(v.back() + e * fpow(p.back(), MOD - 2, MOD) % MOD);
      v.back() %= MOD;
    }
    void single_append(const IT& i, std::vector<ll>& v, std::vector<ll>& p, int MOD) {
      for(auto it = i.begin(); it != i.end(); ++it)
        single_push_back(*it, v, p, MOD);
    }
    virtual ll single_hash(std::vector<ll>& v, std::vector<ll>& p, int MOD, int l, int r) {
      return (v[r] - v[l - 1] + MOD) % MOD * p[l] % MOD;
    }

    private:
    void init_vp(std::vector<ll>& v, std::vector<ll>& p) {
      v.reserve(size);
      p.reserve(size);
      v.push_back(0);
      p.push_back(1);
    }
    void build_single_hash(const IT& i, std::vector<ll>& v, std::vector<ll>& p, int MOD) {
      size = i.size() + 1;
      rb = size - 1;
      init_vp(v, p);
      single_append(i, v, p, MOD);
    }

    protected:
    void init_hash() {
      init_vp(v1, p1);
      init_vp(v2, p2);
    }
    void build_hash(const IT& i) {
      build_single_hash(i, v1, p1, MOD1);
      build_single_hash(i, v2, p2, MOD2);
    }

    public:
    HashIterable() {}
    HashIterable(int _reserve_size) : size(_reserve_size + 1), rb(0) { init_hash(); }
    HashIterable(const IT& i) { build_hash(i); }
    ull operator()(const IT& i) {
      build_hash(i);
      return single_hash(v1, p1, MOD1, 1, i.size()) * single_hash(v2, p2, MOD2, 1, i.size());
    }
    virtual void push_back(ET e) {
      ++rb;
      single_push_back(e, v1, p1, MOD1);
      single_push_back(e, v2, p2, MOD2);
    }
    virtual void append(const IT& i) {
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

  template<class IT, int B=12721, int MOD1=987654361,int MOD2=999991231>
  class MutableHash : public HashIterable<IT, B, MOD1, MOD2> { //1-base && []
    using ll = long long;
    using ET = typename IT::value_type;
    using super = HashIterable<IT, B, MOD1, MOD2>;
    using super::rb;
    using super::p1;
    using super::p2;
    using super::v1;
    using super::v2;
    using super::fpow;

    private:
    inline int lowbit(int x) { return x & -x; }
    inline ll mod(ll x, int MOD) {
      x %= MOD;
      return x < 0 ? x + MOD : x;
    }
    void ft_build(std::vector<ll>& v, int MOD) {
      for(int i = rb; i > 0; --i)
        v[i] = mod(v[i] - v[i - 1], MOD);
      for(int i = 1; i <= rb; ++i) {
        int j = i + lowbit(i);
        if(j <= rb)
          v[j] = mod(v[j] + v[i], MOD);
      }
    }
    ll ft_sum(std::vector<ll>& v, int MOD, int x) {
      ll ret = 0;
      for(; x; x -= lowbit(x))
        ret = mod(ret + v[x], MOD);
      return ret;
    }
    ll ft_qry(std::vector<ll>& v, int MOD, int l, int r) {
      return mod(ft_sum(v, MOD, r) - ft_sum(v, MOD, l - 1), MOD);
    }
    void ft_upd(std::vector<ll>& v, std::vector<ll>& p, int MOD, int x, const ET& ei) {
      ll e = (ll)(ei) * fpow(B, x, MOD) % MOD, o = ft_qry(v, MOD, x, x) % MOD;
      for(; x <= rb; x += lowbit(x))
        v[x] += mod(e - o, MOD), v[x] = mod(v[x], MOD);
    }

    // x = i + (i & -i), find all i
    // i_max = lowbit(x) - 1
    // i_min = (1 << (popcount(i_max) - 1))
    // time complexity: O(logN)
    // not tested
    void ft_push_back(std::vector<ll>& v, std::vector<ll>& p, int MOD, const ET& ei) {
      v.push_back(v.back() * ei % MOD);
      p.push_back(p.back() * fpow(B, MOD - 2, MOD) % MOD);
      int i = 0;
      for(int k = __builtin_popcount(lowbit(rb) - 1) - 1; k >= 0; --k) {
        i |= (1 << k);
        v[rb] = mod(v[rb] + v[i], MOD);
      }
    }
    void ft_double_push_back(const ET& ei) {
      ft_push_back(v1, p1, MOD1, ei);
      ft_push_back(v2, p2, MOD2, ei);
    }
    void ft_double_upd(int x, const ET& ei) {
      ft_upd(v1, p1, MOD1, x, ei);
      ft_upd(v2, p2, MOD2, x, ei);
    }

    protected:
    void build_hash(const IT& i) {
      ft_build(v1, MOD1);
      ft_build(v2, MOD2);
    }
    ll single_hash(std::vector<ll>& v, std::vector<ll>& p, int MOD, int l, int r) override {
      return ft_qry(v, MOD, l, r) * p[l] % MOD;
    }

    public:
    MutableHash() {}
    MutableHash(int _reserve_size) : super(_reserve_size) { super::init_hash(); }
    MutableHash(const IT& i) : super(i) { build_hash(i); }
    void push_back(ET ei) override { ++rb; ft_double_push_back(ei); }
    void append(const IT& i) override {
      rb += i.size();
      for(auto it = i.begin(); it != i.end(); ++it)
        ft_double_push_back(*it);
    }
    void modify(int x, ET ei) { ft_double_upd(x, ei); }
  };
}
