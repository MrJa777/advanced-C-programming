#include <iostream> // Including the Input/Output Stream Library
#include <string>   // Including the String Library
using namespace std;

int main() {
    char a[6] = {'a', 'b', 'c', 'd', 'e', 'f'}; // Declare and initialize another character array
    char b[6] = {'A', 'B', 'C', 'D', 'E', 'F'}; // Declare and initialize a character array
    char temp;
    string mess = "AbbeF"; // Declare and initialize a string variable
    for (int i = 0; i < mess.length(); i++) {
        temp =  mess[i] ;
        if ((int)temp > 90) { // Lowercase letter check}
            cout << b [(int)temp - (int)'a'];
        } else { // Uppercase letter case   
            cout << a [ (int)temp - (int)'A' ];
        }
    }
    
    return 0; // Return 0 to indicate successful execution
}