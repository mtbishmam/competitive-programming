#include<bits/stdc++.h>
using namespace std;

template<class T> void setmax(T &a, T b) { if(b > a) a = b; }

struct node {
	node *p;
	node *c[2];

	int d() { return this == p->c[1]; }

	bool flip;
	int sz;
	bool lazy;
	int lval;
	int val;

	int sum;

	int ssum[2];
	int msum;

	void update() {
		sz = 1 + (c[0] ? c[0]->sz : 0) + (c[1] ? c[1]->sz : 0);

		if(lazy) {
			sum = sz * lval;
			val = lval;
			ssum[0] = ssum[1] = max(0, sum);
			msum = max(val, sum);
		} else {
			sum = val + (c[0] ? c[0]->sum : 0) + (c[1] ? c[1]->sum : 0);

			msum = val + (c[0] ? c[0]->ssum[1] : 0) + (c[1] ? c[1]->ssum[0] : 0);
			if(c[0]) setmax(msum, c[0]->msum);
			if(c[1]) setmax(msum, c[1]->msum);

			ssum[0] = max((c[0] ? c[0]->ssum[0] : 0), (c[0] ? c[0]->sum : 0) + val + (c[1] ? c[1]->ssum[0] : 0));
			ssum[1] = max((c[1] ? c[1]->ssum[1] : 0), (c[1] ? c[1]->sum : 0) + val + (c[0] ? c[0]->ssum[1] : 0));
		}

		if(flip) {
			swap(ssum[0], ssum[1]);
		}
	}

	void propogate() {
		if(lazy) {
			val = lval;
			if(c[0]) c[0]->lazy = true, c[0]->lval = lval;
			if(c[1]) c[1]->lazy = true, c[1]->lval = lval;
			lazy = false;
		}

		if(flip) {
			if(c[0]) c[0]->flip ^= true;
			if(c[1]) c[1]->flip ^= true;
			swap(c[0], c[1]);
			flip = false;
		}

		if(c[0]) c[0]->update();
		if(c[1]) c[1]->update();
		update();
	}

	void rot() {
		assert(p);

		int x = d();
		node * pa = p;
		node * ch = c[!x];

		pa->propogate();
		propogate();

		if(pa->p) pa->p->c[pa->d()] = this;
		p = pa->p;

		pa->c[x] = ch;
		if(ch) ch->p = pa;

		c[!x] = pa;
		pa->p = this;

		pa->update();
		update();
	}

	node* splay(node *r = NULL) {
		propogate();
		while(p != r) {
			if(p->p != r) {
				if(p->d() == d()) p->rot();
				else rot();
			}
			rot();
		}
		return this;
	}

	node* find(int t) {
		node* cur = this;
		while(true) {
			cur->propogate();
			assert(t >= 0 && t < cur->sz);
			int l = (cur->c[0] ? cur->c[0]->sz : 0);
			if(t == l) return cur;
			else if(t < l) return cur->c[0]->find(t);
			else return cur->c[1]->find(t - l - 1);
		}
	}

	node* nxt(int t) {
		propogate();
		node* res = (t ? c[1]->find(t - 1)->splay(this) : this);
		return res;
	}

	node* getrange(int a, int t) {
		node* l = nxt(a);
		assert(l->c[1]);
		if((l->c[1] ? l->c[1]->sz : 0) == t) return l->c[1];
		node* r = l->nxt(t + 1);
		return r->c[0];
	}

	//inserts node after t others
	node* insert(node *n, int t) {
		node* r; int d;
		if(!c[1]) {
			assert(!t);
			r = this;
			d = 1;
		} else if(t == c[1]->sz){
			r = getrange(t-1, 1);
			d = 1;
		} else {
			r = getrange(t, 1);
			d = 0;
		}
		r->propogate();
		assert(!(r->c[d]));
		r->c[d] = n;
		n->p = r;
		while(r) {
			update();
			r = r->p;
		}
		n->splay(this);

		return n;
	}


	void set(int v) {
		lazy = true;
		lval = v;
		node * n = this;
		while(n) {
			n->update();
			n = n->p;
		}
	}

	void rev() {
		flip = !flip;
		node * n = this;
		while(n) {
			n->update();
			n = n->p;
		}
	}

	// delete self
	void del() {
		assert(p);
		p->c[d()] = NULL;
		node * n = p;
		while(n) {
			n->update();
			n = n->p;
		}
	}

	node (int v = 0) : val(v){
		p = NULL;
		c[0] = c[1] = NULL;
		flip = false;
		lazy = false;
		update();
	}

};

int V = 0;
node NODES[int(5e6)];

node* seq[int(1e6)]; // sequence to be inserted

node* makenode(int l, int r) {
	if(l > r) return NULL;
	int m = (l + r) / 2;
	node* n = seq[m];
	n->c[0] = makenode(l, m - 1);
	if(n->c[0]) n->c[0]->p = n;
	n->c[1] = makenode(m + 1, r);
	if(n->c[1]) n->c[1]->p = n;
	n->update();
	return n;
}

int main() {
	ios_base::sync_with_stdio(0);
	int T; cin >> T;
	//int T = 1;
	for(int t = 0; t < T; t++) {
		V = 0;
		node *root = &(NODES[V++] = node());
		int N, M;
		cin >> N >> M;
		for(int q = 0; q <= M; q++) {
			string s;
			if(q) cin >> s;
			else s = "INSERT";
			if(s == "MAKE-SAME") {
				int i, t; cin >> i >> t; i--;
				int v; cin >> v;
				if(!t) continue;
				node *r = root->getrange(i, t);
				r->set(v);
			} else if(s == "INSERT") {
				int i, t;
				if(q) cin >> i >> t;
				else i = 0, t = N;
				if(!t) continue;
				for(int j = 0; j < t; j++) {
					int v; cin >> v;
					node *cur = &(NODES[V++] = node(v));
					seq[j] = cur;
				}
				node* n = makenode(0, t - 1);
				root->insert(n, i);
			} else if(s == "DELETE") {
				int i, t; cin >> i >> t; i--;
				if(!t) continue;
				node *r = root->getrange(i, t);
				r->del();
			} else if(s == "REVERSE") {
				int i, t; cin >> i >> t; i--;
				if(!t) continue;
				node *r = root->getrange(i, t);
				r->rev();
			} else if(s == "GET-SUM") {
				int i, t; cin >> i >> t; i--;
				if(!t) {cout << 0 << '\n'; continue;}
				node *r = root->getrange(i, t);
				int v = r->sum;
				cout << v << '\n';
			} else if(s == "MAX-SUM") {
				int v = root->c[1]->msum;
				cout << v << '\n';
			} else { }
			//cerr << root->c[1]->sz << '\n';
			//cerr << root->c[1]->sum << '\n';
		}
		assert(V < int(5e6));
	}
	return 0;
}
