#include<bits/stdc++.h>
using namespace std;

// gets the p->k if p exists, otherwise returns 0
#define GET(p, k) ((p) ? ((p)->k) : 0)

struct node {
	node* p;
	node* c[2];

	int d() { return this == p->c[1]; }

	int val;
	int sz;
	int sum;

	bool lazy;
	int lval;

	bool flip;

	int ssum[2];
	int msum;

	void update() {
		sz = 1 + GET(c[0], sz) + GET(c[1], sz);

		if(lazy) {
			val = lval;
			sum = lval * sz;

			ssum[0] = ssum[1] = max(0, sum);
			msum = max(lval, sum);
		} else {
			sum = val + GET(c[0], sum) + GET(c[1], sum);

			msum = GET(c[0], ssum[1]) + val + GET(c[1], ssum[0]);
			if(c[0]) msum = max(msum, c[0]->msum);
			if(c[1]) msum = max(msum, c[1]->msum);
			ssum[0] = max(GET(c[0], ssum[0]), GET(c[0], sum) + val + GET(c[1], ssum[0]));
			ssum[1] = max(GET(c[1], ssum[1]), GET(c[1], sum) + val + GET(c[0], ssum[1]));
		}

		if(flip) {
			swap(ssum[0], ssum[1]);
		}
	}

	void propogate() {
		if(lazy) {
			val = lval;
			if(c[0]) {
				c[0]->lazy = true;
				c[0]->lval = lval;
			}
			if(c[1]) {
				c[1]->lazy = true;
				c[1]->lval = lval;
			}
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
		node* pa = p;
		node* ch = c[!x];

		pa->propogate();
		propogate();

		if(pa->p) pa->p->c[pa->d()] = this;
		this->p = pa->p;

		pa->c[x] = ch;
		if(ch) ch->p = pa;

		this->c[!x] = pa;
		pa->p = this;

		pa->update();
		update();
	}

	void splay(node* r) {
		propogate();
		if(this == r) return;
		while(p != r) {
			if(p->p != r) {
				if(p->d() == d()) p->rot();
				else rot();
			}
			rot();
		}
	}

	void updateall(node* r) {
		node* cur = this;
		while(cur) {
			cur->update();
			cur = cur->p;
		}
		splay(r);
	}

	node* nxt(int t) {
		propogate();
		assert(t >= 0);
		if(!t) return this;
		node* cur = c[1];
		while(true) {
			cur->propogate();
			assert(t <= GET(cur, sz));
			if(t == GET(cur->c[0], sz) + 1) break;
			else if(t <= GET(cur->c[0], sz)) cur = cur->c[0];
			else t -= GET(cur->c[0], sz) + 1, cur = cur->c[1];
		}
		cur->splay(this);
		return cur;
	}

	node* getrange(int i, int t) {
		assert(t);
		propogate();
		node* res;
		if(!i) {
			assert(t == sz);
			res = this;
		} else {
			node* st = nxt(i - 1);
			if(GET(st->c[1], sz) == t) {
				res = st->c[1];
			} else {
				node* en = st->nxt(t + 1);
				res = en->c[0];
			}
		}
		assert(GET(res, sz) == t);
		res->propogate();
		return res;
	}

	void set(int i, int t, int v) {
		if(!t) return;
		node* n = getrange(i, t);
		n->lazy = true;
		n->lval = v;
		n->updateall(this);
	}

	void ins(int i, node* n) {
		if(!n) return;
		if(i == GET(c[1], sz)) {
			node* cur = getrange(i, 1);
			assert(!cur->c[1]);
			cur->c[1] = n;
			n->p = cur;
		} else {
			node* cur = getrange(i+1, 1);
			assert(!cur->c[0]);
			cur->c[0] = n;
			n->p = cur;
		}
		n->updateall(this);
	}

	void del(int i, int t) {
		if(!t) return;
		node* cur = getrange(i, t);
		node* par = cur->p;
		par->c[cur->d()] = cur->p = NULL;
		par->updateall(this);
	}

	void rev(int i, int t) {
		if(!t) return;
		node* n = getrange(i, t);
		n->flip ^= true;
		n->propogate();
		n->updateall(this);
	}

	int get(int i, int t) {
		if(!t) return 0;
		node* cur = getrange(i, t);
		int res = cur->sum;
		cur->splay(this);
		return res;
	}

	int getm() {
		assert(c[1]);
		return c[1]->msum;
	}

	node(int v = 0) {
		val = v;
		lazy = false;
		flip = false;
		p = NULL;
		c[0] = c[1] = NULL;
		update();
	}
};

const int MAXV = 5e6;
int V;
node NODES[MAXV];

const int MAXS = 1e6;
int seq[MAXS];

inline node* newnode(int v = 0) {
	assert(V < MAXV);
	return &(NODES[V++] = node(v));
}

node* getseq(int l, int r) {
	if(!(l <= r)) return NULL;
	int m = (l + r) / 2;
	node* n = newnode(seq[m]);
	n->c[0] = getseq(l, m - 1);
	if(n->c[0]) n->c[0]->p = n;
	n->c[1] = getseq(m + 1, r);
	if(n->c[1]) n->c[1]->p = n;
	n->update();
	return n;
}

char str[50];

int main() {
	int T; scanf("%d", &T);
	//int T = 1;
	for(int z = 0; z < T; z++) {
		V = 0;

		node* root = newnode();

		int N, M; scanf("%d %d", &N, &M);

		M++;
		for(int q = 0; q < M; q++) {
			if(q) {
				scanf(" %s", str);
			} else {
				str[0] = 'I';
			}
			if(str[0] == 'M' && str[2] == 'K') {
				int i, t, v;
				scanf("%d %d %d", &i, &t, &v);
				root->set(i, t, v);
			} else if(str[0] == 'I') {
				int i, t;
				if(q) {
					scanf("%d %d", &i, &t);
				} else {
					i = 0, t = N;
				}
				for(int j = 0; j < t; j++) {
					scanf("%d", &(seq[j]));
				}
				node* n = getseq(0, t - 1);
				assert(GET(n, sz) == t);
				root->ins(i, n);
			} else if(str[0] == 'D') {
				int i, t;
				scanf("%d %d", &i, &t);
				root->del(i, t);
			} else if(str[0] == 'R') {
				int i, t;
				scanf("%d %d", &i, &t);
				root->rev(i, t);
			} else if(str[0] == 'G') {
				int i, t;
				scanf("%d %d", &i, &t);
				int res = root->get(i, t);
				printf("%d\n", res);
			} else if(str[0] == 'M' && str[2] == 'X') {
				int res = root->getm();
				printf("%d\n", res);
			} else assert(false);

			assert(root->c[1]);
			//cerr << root->c[1]->sz << '\n';
		}
	}
}
