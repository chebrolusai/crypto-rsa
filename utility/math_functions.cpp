#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

long long modExp(long long base, long long exp, long long mod)
{
    /**
     * This function calculates the modular exponentiation of a base raised to an exponent, modulo a modulus.
     *
     * In simpler terms, it calculates (base ^ exp) % mod, which is the remainder when base raised to the power of exp is divided by mod.
     *
     * @param base: The base value to be exponentiated.
     * @param exp: The exponent to which the base is raised.
     * @param mod: The modulus value used for modular arithmetic.
     * @return The result of the modular exponentiation (base ^ exp) % mod.
     */

    long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp & 1)
        {
            result = (result * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

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