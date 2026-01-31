#include <iostream>
using namespace std;
int findSum(int arr[], int size) {
    if ( size <= 0)
        return 0;
    else
        return arr[size - 1] + findSum(arr, size - 1);
}
int main() {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << " Sun of array elements = " << findSum(arr, 10);
}