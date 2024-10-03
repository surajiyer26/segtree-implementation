struct segtree {

    int size;
    vector<int> tree, lazy;

    void init (int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        tree.assign(2 * size, 0);
        lazy.assign(2 * size, -1);
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
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build (vector<int> &vec) {
        build(vec, 0, 0, size);
    }

    void propagate(int x, int lx, int rx) {
        if (lazy[x] == -1) return;
        tree[x] = lazy[x];

        if (rx - lx > 1) {
            lazy[2 * x + 1] = lazy[x];
            lazy[2 * x + 2] = lazy[x];
        }

        lazy[x] = -1;
    }

    void range_set(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            lazy[x] = v;
            propagate(x, lx, rx);
            return;
        }
        int mid = lx + (rx - lx) / 2;
        range_set(l, r, v, 2 * x + 1, lx, mid);
        range_set(l, r, v, 2 * x + 2, mid, rx);
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void range_set(int l, int r, int v) {
        range_set(l, r, v, 0, 0, size);
    }

    int query (int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return tree[x];
        int mid = lx + (rx - lx) / 2;
        int max1 = query(l, r, 2 * x + 1, lx, mid);
        int max2 = query(l, r, 2 * x + 2, mid, rx);
        return max(max1, max2);
    }

    int query (int l, int r) {
        return query(l, r, 0, 0, size);
    }

    void print () {
        for (int i = 0; i < size; ++i) cout << tree[i] << " ";
        cout << "\n";
    }
};
