struct segtree {

	int size;
	vector<int> tree;

	void init (int n) {
		size = 1;
		while (size < n) {
			size *= 2;
		}
		tree.assign(2 * size, 0);
	}

	void build (vector<int> &vec, int x, int lx, int rx) {
		if (rx - lx == 1) {
			if (lx < (int)vec.size()) {
				tree[x] = vec[lx];
			}
			return;
		}
		int mid = lx + (rx - lx) / 2;
		build(vec, 2 * x + 1, lx, mid);
		build(vec, 2 * x + 2, mid, rx);
		tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
	}

	void build (vector<int> &vec) {
		build(vec, 0, 0, size);
	}

	void set (int i, int v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			tree[x] = v;
			return;
		}
		int mid = lx + (rx - lx) / 2;
		if (i < mid) {
			set(i, v, 2 * x + 1, lx, mid);
		}
		else {
			set(i, v, 2 * x + 2, mid, rx);
		}
		tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
	}

	void set (int i, int v) {
		set(i, v, 0, 0, size);
	}

	int query (int l, int r, int x, int lx, int rx) {
		if (lx >= r || rx <= l) return INT_MAX;
		if (lx >= l && rx <= r) return tree[x];
		int mid = lx + (rx - lx) / 2;
		int min1 = query(l, r, 2 * x + 1, lx, mid);
		int min2 = query(l, r, 2 * x + 2, mid, rx);
		return min(min1, min2);
	}

	int query (int l, int r) {
		return query(l, r, 0, 0, size);
	}

	void print () {
		for (int i = 0; i < size; ++i) cout << tree[i] << " ";
		cout << "\n";
	}

};
