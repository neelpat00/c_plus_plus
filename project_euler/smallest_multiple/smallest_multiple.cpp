/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 
without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers 
from 1 to 20?
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <map>


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

int main()
{   
    int count = 20;

    // Need the initialise the map of prime numbrs 
    std::map<int, int> prime_factor_count;

    // Go through each of the numbers to calculate the highest prime power of each prime factor

    for (int i = 1; i <= count; i++)
    {
        std::vector<long int> factor_array = factor_number(i);

        // Count each of the prime factors power
        std::map<int, int> counts;

        for (int num : factor_array) {
            counts[num]++;  // This works just like defaultdict!
        }

        for (auto [key, value] : counts) {
            if (prime_factor_count[key] < value)
            {
                prime_factor_count[key] = value;
            }
        }
    }

    int prod_value = 1;

    for (auto [key, value] :  prime_factor_count)
    {
        std::cout << "Prime " << key << " with power: " << value << std::endl; 
        prod_value *= pow(key, value);
    }
    
    std::cout << "Smallest Value is " << prod_value << std::endl;
    return 0;
}

