/*
A palindromic number reads the same both ways. The largest palindrome made from 
the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

#include <string>
#include <iostream>

bool is_palindrome(std::string string) {
    int i = 0;
    int length = string.length();

    int middle_index;

    if (length % 2 == 0) {
        middle_index = length / 2;
    }
    else {
        middle_index = (length - 1) / 2;
    }

    while (i < middle_index) {
        if (string[i] != string[length - 1 - i]) { 
            return false;
        }
        else {
            i += 1;
        }
    }

    return true;
}

int main() {

    int largest_palindrome = 0;

    for (int i = 1; i < 1000; i++)
    {
        for (int j = 1; j < 1000; j++)
        {
            int prod = i * j;

            std::string prod_string = std::to_string(prod);

            if (is_palindrome(prod_string) && (largest_palindrome < prod))
            {
                largest_palindrome = prod;
            }

        }
        
    }

    std::cout << largest_palindrome << " is the largest palindrome" << std::endl;

    return 0;
}
