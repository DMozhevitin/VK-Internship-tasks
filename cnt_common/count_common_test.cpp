#include <random>
#include <unordered_set>
#include <algorithm>
#include "gtest.h"

size_t count_common(const int *, const size_t, const int *, const size_t);
std::mt19937 rd;
size_t small_arr_size = 32768;
size_t big_arr_size = 100000;
size_t TESTS_CNT = 100;

TEST(base_tests, default_test) {
    int a[] = {1, 2, 3};
    int b[] = {1, 2};
    EXPECT_TRUE(count_common(a, 3, b, 2) == 2);
}

TEST(base_tests, empty_arrays) {
    int a[] = {};
    int b[] = {};
    EXPECT_TRUE(count_common(a, 0, b, 0) == 0);
}

TEST(base_tests, empty_array1) {
    int a[] = {};
    int b[] = {0};
    EXPECT_TRUE(count_common(a, 0, b, 1) == 0);
}

TEST(base_tests, empty_array2) {
    int a[] = {0};
    int b[] = {};
    EXPECT_TRUE(count_common(a, 1, b, 0) == 0);
}

TEST(base_tests, intminmax1) {
    int a[] = {INT32_MAX};
    int b[] = {INT32_MIN};
    EXPECT_TRUE(count_common(a, 1, b, 1) == 0);
}

TEST(base_tests, intminmax2) {
    int a[] = {INT32_MAX, INT32_MIN};
    int b[] = {INT32_MIN, INT32_MAX};
    EXPECT_TRUE(count_common(a, 2, b, 2) == 2);
}

TEST(random_tests, rndtest_small_arrays) {
    for (size_t cnt_test = 0; cnt_test < TESTS_CNT; cnt_test++) {
        size_t n = rd() % small_arr_size;
        int a[n];
        size_t m = rd() % small_arr_size;
        int b[m];
        std::unordered_set<int> s;
        size_t common_cnt = rd() % std::min(n, m);

        //generate unique numbers in a
        for (size_t i = 0; i != n - common_cnt; i++) {
            a[i] = rd();
            while (s.find(a[i]) != s.end()) {
                a[i] = rd();
            }
            s.insert(a[i]);
        }

        //generate unique numbers in b
        for (size_t i = 0; i != m - common_cnt; i++) {
            b[i] = rd();
            while (s.find(b[i]) != s.end()) {
                b[i] = rd();
            }
            s.insert(b[i]);
        }

        //generate common numbers in arrays
        for (size_t i = 0; i != common_cnt; i++) {
            int r = rd();
            while (s.find(r) != s.end()) {
                r = rd();
            }
            s.insert(r);

            a[n - common_cnt + i] = r;
            b[m - common_cnt + i] = r;
        }

        std::shuffle(a, a + n, std::mt19937(std::random_device()()));
        std::shuffle(b, b + m, std::mt19937(std::random_device()()));

        EXPECT_TRUE(count_common(a, n, b, m) == common_cnt);
    }
}

TEST(random_tests, rndtest_big_arrays) {
    for (size_t cnt_test = 0; cnt_test < TESTS_CNT; cnt_test++) {
        size_t n = rd() % big_arr_size;
        int a[n];
        size_t m = rd() % big_arr_size;
        int b[m];
        std::unordered_set<int> s;
        size_t common_cnt = rd() % std::min(n, m);

        //generate unique numbers in a
        for (size_t i = 0; i != n - common_cnt; i++) {
            a[i] = rd();
            while (s.find(a[i]) != s.end()) {
                a[i] = rd();
            }
            s.insert(a[i]);
        }

        //generate unique numbers in b
        for (size_t i = 0; i != m - common_cnt; i++) {
            b[i] = rd();
            while (s.find(b[i]) != s.end()) {
                b[i] = rd();
            }
            s.insert(b[i]);
        }

        //generate common numbers in arrays
        for (size_t i = 0; i != common_cnt; i++) {
            int r = rd();
            while (s.find(r) != s.end()) {
                r = rd();
            }
            s.insert(r);

            a[n - common_cnt + i] = r;
            b[m - common_cnt + i] = r;
        }

        std::shuffle(a, a + n, std::mt19937(std::random_device()()));
        std::shuffle(b, b + m, std::mt19937(std::random_device()()));

        EXPECT_TRUE(count_common(a, n, b, m) == common_cnt);
    }
}
