#include<iostream>
#include<list>

using namespace std;

int main(){
    list<int> mylist;

    mylist.push_back(10);
    mylist.push_back(20);
    mylist.push_back(30);

    cout << " Elements in the list are: ";
    for (int value : mylist){
        cout << value << " ";
    }
    cout << endl;

    mylist.remove(20);

    cout << " Elements in the list after removing 20 are: ";
    for (int value : mylist){
        cout << value << " ";
    }
    cout << endl;
    return 0;
}
