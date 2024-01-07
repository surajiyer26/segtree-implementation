0. Consider `vector<int> vec` of size `n`
1. To declare a segtree named st - `segtree st;`
2. To initialize the segtree - `st.init(n);`
3. To build the segtree - `st.build(vec);`
4. To set/update element at index i (0-indexing) to value v - `st.set(i, v);`
5. To call query on range [l, r) - `st.query(l, r);`
