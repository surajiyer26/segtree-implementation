struct node {

	int seg; // maximal subsegment sum
	int pre; // maximal prefix sum
	int suf; // maximal suffix sum
	int sum; // sum of the entire segment

};

struct segtree {

	int size;
	vector<node> tree;

	node empty = {0, 0, 0, 0};

	void init (int n) {
		size = 1;
		while (size < n) {
			size *= 2;
		}
		tree.assign(2 * size, empty);
	}

	node make_node (int x) {
		node tmp;
		if (x >= 0) tmp = {x, x, x, x};
		else tmp = {0, 0, 0, x};
		return tmp;
	}

	node combine (node &a, node &b) {
		node tmp;
		tmp.seg = max({a.seg, b.seg, a.suf + b.pre});
		tmp.pre = max(a.pre, a.sum + b.pre);
		tmp.suf = max(b.suf, b.sum + a.suf);
		tmp.sum = a.sum + b.sum;
		return tmp;
	}

	void build (vector<int> &vec, int x, int lx, int rx) {
		if (rx - lx == 1) {
			if (lx < (int)vec.size()) {
				tree[x] = make_node(vec[lx]);
			}
			return;
		}
		int mid = lx + (rx - lx) / 2;
		build(vec, 2 * x + 1, lx, mid);
		build(vec, 2 * x + 2, mid, rx);
		tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
	}

	void build (vector<int> &vec) {
		build(vec, 0, 0, size);
	}

	void set (int i, int v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			tree[x] = make_node(v);
			return;
		}
		int mid = lx + (rx - lx) / 2;
		if (i < mid) {
			set(i, v, 2 * x + 1, lx, mid);
		}
		else {
			set(i, v, 2 * x + 2, mid, rx);
		}
		tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
	}

	void set (int i, int v) {
		set(i, v, 0, 0, size);
	}

	node query (int l, int r, int x, int lx, int rx) {
		if (lx >= r || rx <= l) return empty;
		if (lx >= l && rx <= r) return tree[x];
		int mid = lx + (rx - lx) / 2;
		node seg1 = query(l, r, 2 * x + 1, lx, mid);
		node seg2 = query(l, r, 2 * x + 2, mid, rx);
		return combine(seg1, seg2);
	}

	node query (int l, int r) {
		return query(l, r, 0, 0, size);
	}

	void print () {
		for (int i = 0; i < size; ++i) cout << tree[i].seg << " " << tree[i].pre << " " << tree[i].suf << " " << tree[i].sum << "\n"; 
		cout << "\n";
	}

};
