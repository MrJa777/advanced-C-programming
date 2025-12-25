#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int arr[] = {1, 3, 3, 3, 5, 7};

    int* lb = lower_bound(arr, arr + 6, 3);
    int* ub = upper_bound(arr, arr + 6, 3);

    cout << "First 3 at index " << (lb - arr) << endl;
    cout << "Count of 3 = " << (ub - lb);

    return 0;
}
