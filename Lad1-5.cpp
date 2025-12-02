// Recursive function to check if a string is a palindrome
#include <iostream> // Including the Input/Output Stream Library
#include <string>   // Including the String Library
#include <algorithm> // Including the Algorithm Library

// Recursive function to check if a string is a palindrome
bool isPalindrome(const std::string & text, int start, int end) {
  // Base case: when start >= end, the string is a palindrome
  if (start >= end)
    return true;

  // Recursive case: check if the characters at start and end indices are equal,
  // and recursively check the remaining characters
  if (text[start] != text[end])
    return false;

  return isPalindrome(text, start + 1, end - 1);
}

int main() {
  std::string text; // Declaring a variable to store the input string

  std::cout << "Input a string: ";
  std::getline(std::cin, text); // Taking input for the string

  // Remove any spaces from the input string
  text.erase(std::remove(text.begin(), text.end(), ' '), text.end());

  // Check if the string is a palindrome using recursion
  bool palindrome = isPalindrome(text, 0, text.length() - 1); // Checking if the input string is a palindrome

  // Display the result
  if (palindrome)
    std::cout << "The string is a palindrome." << std::endl;
  else
    std::cout << "The string is not a palindrome." << std::endl;

  return 0; // Returning 0 to indicate successful execution of the program
}