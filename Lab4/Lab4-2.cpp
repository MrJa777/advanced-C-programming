#include <iostream>
using namespace std;

// ฟังก์ชัน partition
int partition(int arr[], int low, int high) {
    int pivot = arr[high];   // เลือก pivot เป็นตัวสุดท้าย
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ฟังก์ชัน quick sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);   // ฝั่งซ้าย
        quickSort(arr, pi + 1, high);  // ฝั่งขวา
    }
}

int main() {
    int A[10] = {10, 2, 7, 4, 9, 5, 3, 1, 6, 8};

    cout << "Original array: \n";
    for (const auto &x : A) {
        cout << x << " ";
    }
    cout << endl;

    quickSort(A, 0, 9);

    cout << "After sorting (Ascending order): \n";
    for (const auto &x : A) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
