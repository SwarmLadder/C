#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void move_zeros(int *values, size_t n);

static void check(const int *actual, const int *expected, size_t n) {
    for (size_t i = 0; i < n; ++i) assert(actual[i] == expected[i]);
}

int main(void) {
    int a[] = {0, 5, 0, 3, 12, 0, 7};
    int expected_a[] = {5, 3, 12, 7, 0, 0, 0};
    move_zeros(a, 7);
    check(a, expected_a, 7);
    int negatives[] = {-1, 0, -2, 0, -3};
    int expected_negatives[] = {-1, -2, -3, 0, 0};
    move_zeros(negatives, 5);
    check(negatives, expected_negatives, 5);
    int zeros[] = {0, 0, 0};
    move_zeros(zeros, 3);
    assert(zeros[0] == 0 && zeros[1] == 0 && zeros[2] == 0);
    int unchanged[] = {1, 2, 3};
    move_zeros(unchanged, 3);
    assert(unchanged[0] == 1 && unchanged[1] == 2 && unchanged[2] == 3);
    move_zeros(NULL, 0);
    puts("array pointer lab: all reference tests passed");
    return 0;
}
