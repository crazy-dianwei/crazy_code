
#include <algorithm>

const int maxn = 10000 + 6;
int n, a[maxn], q;

struct Node {
  int sum;
  int lazy;
  int max_v;
  int min_v;
  int l, r;
}tree[4 * maxn];

void push_up(int x) {
  tree[x].sum = tree[x << 1].sum + tree[x << 1 | 1].sum;
  tree[x].max_v = std::max(tree[x << 1].max_v, tree[x << 1 | 1].max_v);
  tree[x].min_v = std::min(tree[x << 1].min_v, tree[x << 1 | 1].min_v);
}

void push_down(int x) {
  if (tree[x].lazy > 0) {
    tree[x << 1].lazy += tree[x].lazy; 
    tree[x << 1].sum += (tree[x << 1].r - tree[x << 1].l + 1) * tree[x].lazy;
    tree[x << 1 | 1].lazy += tree[x].lazy; 
    tree[x << 1 | 1].sum += (tree[x << 1 | 1].r - tree[x << 1 | 1].l + 1) * tree[x].lazy;
    tree[x].lazy = 0;
  }
}

void build(int x, int l, int r) {
  tree[x].l = l;
  tree[x].r = r;
  if (l == r) {
    tree[x].lazy = 0;
    tree[x].sum = tree[x].max_v = tree[x].min_v = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  // left
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  push_up(x);
}

void add_seg_v(int x, int l, int r, int val) {
  int L = tree[x].l;
  int R = tree[x].r;
  if (L >= l && R <= r) {
    tree[x].sum += (R - L + 1) * val;
    tree[x].min_v += val;
    tree[x].max_v += val;
    tree[x].lazy += val;
    return;
  }
  push_down(x);
  int mid = (L + R) >> 1;
  if (l > mid) {
    add_seg_v(x << 1 | 1, l, r, val);
  } else if ( mid >= r ) {
    add_seg_v(x << 1, l, r, val);
  } else {
    add_seg_v(x << 1, l, mid, val);
    add_seg_v(x << 1 | 1, mid + 1, r, val);
  }
  push_up(x);
}

int query_max(int x, int l, int r) {
  int L = tree[x].l;
  int R = tree[x].r;
  if (L >= l && R <= r) {
    return tree[x].max_v;
  }
  push_down(x);
  int mid = (L + R) >> 1;
  if (l > mid) {
    return query_max(x << 1 | 1, l, r);
  } else if ( mid >= r ) {
    return query_max(x << 1, l, r);
  }
  return std::max(query_max(x << 1, l, mid), query_max(x << 1 | 1, mid + 1, r));
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1;i <= n; i++) {
    scanf("%d", &a[i]);
  }
  build(1, 1, n);
}
