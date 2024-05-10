#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

bool millerRabinPrimalityTest(long long n, int k = 5)
{
    /**
     * This function performs a Miller-Rabin primality test on a given number `n`.
     * It is a probabilistic test that determines whether a number is likely prime
     * with a high degree of certainty. The `k` parameter specifies the number of iterations
     * of the test, with higher values increasing the accuracy.
     *
     * Note: This test is not deterministic and there is a small probability of error.
     */

    // Handle base cases (n <= 1 or n is even)
    if (n <= 1 || n % 2 == 0)
    {
        return false;
    }

    long long d = n - 1;

    // Extract the exponent (d) where n - 1 = 2^s * d (d is odd)
    while (d % 2 == 0)
    {
        d /= 2;
    }

    // Perform k iterations of the Miller-Rabin test
    for (int i = 0; i < k; ++i)
    {
        // Generate a random witness (a) between 2 and n-2 (inclusive)
        long long a = 2 + rand() % (n - 3);
        long long x = 1;
        long long power = d;

        // Perform exponentiation with modular reduction
        while (power > 0)
        {
            if (power & 1)
            {
                x = (x * a) % n;
            }
            a = (a * a) % n;
            power >>= 1;
        }
        // If x is not 1 or n-1 after the exponentiation, n is likely composite
        if (x != 1 && x != n - 1)
            return false;
    }

    // If all k iterations pass, n is probably prime
    return true;
}

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