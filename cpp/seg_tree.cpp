#include <bits/stdc++.h>
using namespace std;

namespace seg_tree_space {
#define uit unsigned int
#define seg_func_ret function<T(T,T)>
#define seg_func_void function<void(Node*,uit,uit,uit)>
#define seg_func_update function<void(Node*,uit,uit,uit,T)>
	template<class T> struct buildin_seg_tree_node {
		T value, tag;
		buildin_seg_tree_node(T _value=T(), T _tag=T()) : value(_value), tag(_tag) {}
	};
	template<class T, T Lim, class Container=vector<T>, class Node=buildin_seg_tree_node<T>> class seg_tree {
		static uit siz;
		Node *seg=nullptr;
		seg_func_void pull, push;
		seg_func_ret ret;
		seg_func_update update;

		public:
		seg_tree(uit _siz, seg_func_void _pull, seg_func_ret _ret, seg_func_update _update,
				seg_func_void _push=[](Node* nd, uit id, uit l, uit r){}) {
			siz = _siz;
			seg = new Node[siz<<2];
			pull = _pull, push = _push;
			ret = _ret;
			update = _update;
			for(uit i=1; i<(siz<<2); ++i) seg[i]=Node();
		}
		void build(Container& dt, uit id=1, uit l=1, uit r=siz) {
			if(l==r) {seg[id].value = dt[l]; return;}
			uit mid=(l+r)>>1;
			build(dt, id<<1, l, mid), build(dt, id<<1|1, mid+1, r);
			pull(seg, id, l, r);
		}
		T qry(uit ql, uit qr, uit id=1, uit l=1, uit r=siz) {
			push(seg, id, l, r);
			if(ql<=l && r<=qr) return seg[id].value;
			if(l>qr || ql>r) return Lim;
			uit mid=(l+r)>>1;
			return ret(qry(ql, qr, id<<1, l, mid), qry(ql, qr, id<<1|1, mid+1, r));
		}
		void upd(uit ql, uit qr, T v, uit id=1, uit l=1, uit r=siz) {
			push(seg, id, l, r);
			if(ql<=l && r<=qr) {update(seg, id, l, r, v); return;}
			if(l>qr || ql>r) return;
			uit mid=(l+r)>>1;
			upd(ql, qr, v, id<<1, l, mid), upd(ql, qr, v, id<<1|1, mid+1, r);
			pull(seg, id, l, r);
		}
	};
#undef uit
#undef seg_func_ret
#undef seg_func_void
#undef seg_func_update
}

using namespace seg_tree_space;

#define mid ((l+r)/2)
#define lc (id<<1)
#define rc (id<<1|1)

using uit = unsigned int;
using ll = long long;
using node = buildin_seg_tree_node<ll>;

int main() {
	auto pull = [](node *seg, uit id, uit l, uit r) {
		if(l != r)
			seg[id].value = seg[lc].value + seg[rc].value;
	};
	auto ret = [](ll a, ll b) {return a+b;};
	auto update = [](node *seg, uit id, uit l, uit r, ll v) {
		if(l != r) {
			seg[id].value += v*(r-l+1);
			seg[id].tag += v;
		}
	};
	auto push = [](node *seg, uit id, uit l, uit r) {
		if(seg[id].tag) {
			if(l != r) {
				seg[lc].value += seg[id].tag*(mid-l+1);
				seg[rc].value += seg[id].tag*(r-mid);
				seg[lc].tag += seg[id].tag, seg[rc].tag += seg[id].tag;
			}
			seg[id].tag = 0;
		}
	};
	int n, q;
	cin >> n >> q;
	cerr << 'x';
	seg_tree<ll, 0> tr(n, pull, ret, update, push);
	cerr << 'y';
	vector<ll> vt(n);
	for(auto& i : vt) cin >> i;
	tr.build(vt);
	cerr << 'z';
	while(q--) {
		int o, l, r, k;
		cin >> o;
		if(o) {
			cin >> l >> r;
			cout << tr.qry(l, r) << '\n';
		} else {
			cin >> l >> r >> k;
			tr.upd(l, r, k);
		}
	}
}
