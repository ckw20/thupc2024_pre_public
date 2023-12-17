#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, l, r;
    double p;
    scanf("%d%lf%d%d", &n, &p, &l, &r);
    assert(1 <= l && l <= r && r <= n);
    printf("%.6lf\n", (r - l + 1) * p);
    return 0;
}