#include <iostream>
#include <vector>

void quick_sort(std::vector<int> &arr, int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = arr[l + r >> 1];
    while (i < j) {
        do i ++; while (arr[i] < x);
        do j --; while (arr[j] > x);
        if (i < j) std::swap(arr[i], arr[j]);
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}

int main() {
    std::vector<int> arr = {1, 5, 3, 2, 6, 7, 9, 8, 4, 0};
    for (auto &a: arr) std::cout << a << '\t';
    std::cout << std::endl;
    quick_sort(arr, 0, arr.size() - 1);
    for (auto &a: arr) std::cout << a << '\t';
    std::cout << std::endl;

    return 0;
}