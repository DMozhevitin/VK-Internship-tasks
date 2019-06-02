#include <set>
#include <random>
#include <cassert>
#include <vector>
#include <iostream>
#include <math.h>

class UniqCounter {

public:
    UniqCounter() {
        bloom.resize(3200000);
        bloom.shrink_to_fit();
        cnt_uniq = 0;
    }

    void add(int x) {
        if (!bloom[x % bloom.size()]) {
            bloom[x % bloom.size()] = 1;
            cnt_uniq++;
        }
    }

    int get_uniq_num() const {
        return cnt_uniq;
    }

private:
    int cnt_uniq;
    std::vector<bool> bloom;
};

double relative_error(int expected, int got) {
    return abs(got - expected) / (double) expected;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    const int N = (int) 1e6;
    for (int k : {1, 10, 1000, 10000, N / 10, N, N * 10}) {
        std::uniform_int_distribution<> dis(1, k);
        std::set<int> all;
        UniqCounter counter;
        for (int i = 0; i < N; i++) {
            int value = dis(gen);
            all.insert(value);
            counter.add(value);
        }
        int expected = (int) all.size();
        int counter_result = counter.get_uniq_num();
        double error = relative_error(expected, counter_result);
        printf("%d numbers in range [1 .. %d], %d uniq, %d result, %.5f relative error\n", N, k, expected, counter_result, error);
        assert(error <= 0.1);
    }

    return 0;
}