#include <iostream>
#include <unordered_set>

size_t count_common(const int a[], const size_t n, const int b[], const size_t m) {
    std::unordered_set<int> s;
    size_t ans = 0;

    if (n < m) {
        for (size_t i = 0; i != m; i++) {
            s.insert(b[i]);
        }

        for (size_t i = 0; i != n; i++) {
            if (s.find(a[i]) != s.end()) {
                ans++;
            }
        }
    } else {
        for (size_t i = 0; i != n; i++) {
            s.insert(a[i]);
        }

        for (size_t i = 0; i != m; i++) {
            if (s.find(b[i]) != s.end()) {
                ans++;
            }
        }
    }

    return ans;
}