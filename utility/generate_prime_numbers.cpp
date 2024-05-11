#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>
#include <vector>
#include "math_functions.cpp"
using namespace std;

vector<int> generatePrimeNumbers()
{
    /**
     * This function generates two random prime numbers with 5 digits (approximately).
     * It uses the Miller-Rabin primality test to check for primality.
     *
     * Note: This approach might not be suitable for cryptographic applications
     * as the prime numbers need to be very huge. This function takes into consideration the
     * complexity and computation invloved and chooses prime numbers.
     */
    std::cout << std::fixed << std::setprecision(0);

    // Seeding the random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1001, 99999);

    // Ensure an odd number
    int random_number_1 = dis(gen) | 1;
    int random_number_2 = dis(gen) | 1;

    // Find the closest prime numbers for the generated random numbers
    while (!millerRabinPrimalityTest(random_number_1))
    {
        random_number_1 = random_number_1 - 2;
    }

    while (!millerRabinPrimalityTest(random_number_2))
    {
        random_number_2 = random_number_2 + 2;
    }

    vector<int> prime_numbers;

    prime_numbers.push_back(random_number_1);
    prime_numbers.push_back(random_number_2);

    return prime_numbers;
}