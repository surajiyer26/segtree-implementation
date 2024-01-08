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
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
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
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set (int i, int v) {
        set(i, v, 0, 0, size);
    }

    int query (int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return INT_MIN;
        if (lx >= l && rx <= r) return tree[x];
        int mid = lx + (rx - lx) / 2;
        int min1 = query(l, r, 2 * x + 1, lx, mid);
        int min2 = query(l, r, 2 * x + 2, mid, rx);
        return max(min1, min2);
    }

    int query (int l, int r) {
        return query(l, r, 0, 0, size);
    }

    int first_ele_atleast_x (int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (tree[x] >= v) return lx;
            return -1;
        }
        int mid = lx + (rx - lx) / 2;
        int max1 = query(lx, mid);
        int max2 = query(mid, rx);
        if (max1 >= v) return first_ele_atleast_x(v, 2 * x + 1, lx, mid);
        if (max2 >= v) return first_ele_atleast_x(v, 2 * x + 2, mid, rx);
        return -1;
    }

    int first_ele_atleast_x (int v) {
        return first_ele_atleast_x(v, 0, 0, size);
    }

    void print () {
        for (int i = 0; i < size; ++i) cout << tree[i] << " ";
        cout << "\n";
    }

};
