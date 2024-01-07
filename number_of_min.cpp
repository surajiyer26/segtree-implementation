struct segtree {

	int size;
	vector<pair<int, int>> tree;

	void init (int n) {
		size = 1;
		while (size < n) {
			size *= 2;
		}
		tree.assign(2 * size, {0, 0});
	}

	pair<int, int> combine (pair<int, int> &a, pair<int, int> &b) {
		if (a.first < b.first) {
			return a;
		}
		else if (b.first < a.first) {
			return b;
		}
		else {
			return {a.first, a.second + b.second};
		}
	}

	void build (vector<int> &vec, int x, int lx, int rx) {
		if (rx - lx == 1) {
			if (lx < (int)vec.size()) {
				tree[x].first = vec[lx];
				tree[x].second = 1;
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
			tree[x].first = v;
			tree[x].second = 1;
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

	pair<int, int> query (int l, int r, int x, int lx, int rx) {
		if (lx >= r || rx <= l) return {INT_MAX, INT_MAX};
		if (lx >= l && rx <= r) return tree[x];
		int mid = lx + (rx - lx) / 2;
		pair<int, int> tmp1 = query(l, r, 2 * x + 1, lx, mid);
		pair<int, int> tmp2 = query(l, r, 2 * x + 2, mid, rx);
		return combine(tmp1, tmp2);
	}

	pair<int, int> query (int l, int r) {
		return query(l, r, 0, 0, size);
	}

	void print () {
		for (int i = 0; i < size; ++i) cout << tree[i].first << " " << tree[i].second << "\n";
		cout << "\n";
	}

};
