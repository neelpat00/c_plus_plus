/*
The prime factors of $13195$ are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


bool is_prime(long int num) {
    for(long int i = 1; i <= sqrt(num); i++) {
        if (num % i == 0 && (i != 1 && i != num)) {
            return false;
        }
    }

    return true;
}

long int next_prime(long int num) {
    int i = num + 1;
    while (true)
    {
        if (is_prime(i)) {
            return i;
        }
        else {
            i += 1;
        }
    }
    
}

std::vector<long int> factor_number(long int num) {
    long int number = num;
    std::vector<long int> factors_arr;

    long int prime_number = 2;
    while (!is_prime(number))
    {
        while (true)
        {
            if (number % prime_number == 0) {
                factors_arr.push_back(prime_number);
                number = number / prime_number;

                prime_number = 2;
                break;
            }
            else {
                prime_number = next_prime(prime_number);
            }
        }
    }
    factors_arr.push_back(number);
    return factors_arr;
}



int main() {
    long int number = 600851475143;
    std::vector<long int> factor_arr = factor_number(number);

    int max_value = *std::max_element(factor_arr.begin(), factor_arr.end());

    std::cout << "The biggest prime factor is " << max_value << std::endl;
    return 0;
}
