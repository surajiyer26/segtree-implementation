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
		tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
	}

	void build (vector<int> &vec) {
		build(vec, 0, 0, size);
	}

	void set (int i, int x, int lx, int rx) {
		if (rx - lx == 1) {
			tree[x] = 1 - tree[x];
			return;
		}
		int mid = lx + (rx - lx) / 2;
		if (i < mid) {
			set(i, 2 * x + 1, lx, mid);
		}
		else {
			set(i, 2 * x + 2, mid, rx);
		}
		tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
	}

	void set (int i) {
		set(i, 0, 0, size);
	}

	int query (int l, int r, int x, int lx, int rx) {
		if (lx >= r || rx <= l) return 0;
		if (lx >= l && rx <= r) return tree[x];
		int mid = lx + (rx - lx) / 2;
		int sum1 = query(l, r, 2 * x + 1, lx, mid);
		int sum2 = query(l, r, 2 * x + 2, mid, rx);
		return sum1 + sum2;
	}

	int query (int l, int r) {
		return query(l, r, 0, 0, size);
	}

	int kth_one (int k, int lx, int rx) {
		if (rx - lx == 1) return lx;
		int mid = lx + (rx - lx) / 2;
		int tmp = query(lx, mid);
		if (k > tmp) return kth_one(k - tmp, mid, rx);
		return kth_one(k, lx, mid);
	}

	int kth_one (int k) {
		return kth_one (k, 0, size);
	}

	void print () {
		for (int i = 0; i < size; ++i) cout << tree[i] << " ";
		cout << "\n";
	}

};
