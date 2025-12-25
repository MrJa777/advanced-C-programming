#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int arr[] = {1, 3, 5, 7, 9};

    int* it = lower_bound(arr, arr + 5, 7);

    if (it != arr + 5 && *it == 7) {
        cout << "Found at index " << (it - arr);
    } else {
        cout << "Not found";
    }

    return 0;
}
