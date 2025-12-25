#include <iostream>
#include <string>
using namespace std;

const int N = 10;   // จำนวนคน
const int DIGITS = 13; // เลขบัตร 13 หลัก

// Counting Sort ตามหลักที่กำหนด
void countingSort(string arr[], int pos) {
    string output[N];
    int count[10] = {0};

    // นับจำนวนตัวเลขในหลัก pos
    for (int i = 0; i < N; i++) {
        int digit = arr[i][pos] - '0';
        count[digit]++;
    }

    // สะสมค่า (prefix sum)
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // จัดเรียง (จากหลังไปหน้าเพื่อให้ stable)
    for (int i = N - 1; i >= 0; i--) {
        int digit = arr[i][pos] - '0';
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // คัดลอกกลับ
    for (int i = 0; i < N; i++)
        arr[i] = output[i];
}

// Radix Sort
void radixSort(string arr[]) {
    // เริ่มจากหลักขวาสุด (12) ไปซ้ายสุด (0)
    for (int pos = DIGITS - 1; pos >= 0; pos--) {
        countingSort(arr, pos);
    }
}

int main() {
    string id[N] = {
        "1101700234567",
        "3100501234561",
        "1101700234501",
        "2100309876543",
        "1101701234560",
        "5100204567891",
        "1101700234599",
        "4100801112223",
        "1101700234560",
        "1101700234000"
    };

    radixSort(id);

    cout << "เรียงเลขบัตรประชาชน (น้อย → มาก):\n";
    for (int i = 0; i < N; i++) {
        cout << id[i] << endl;
    }

    return 0;
}
