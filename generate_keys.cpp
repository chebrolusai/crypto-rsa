#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <cmath>
#include <gmp.h>
#include "utility/generate_prime_numbers.cpp"

long long int gcd(long long a, long long b)
{
    /**
     * Euclidean Algorithm.
     * An efficient algorithm to find the greatest common divisor (GCD) of two
     * non-negative integers a and b using recursion.
     */
    if (!a)
        return b;
    return gcd(b % a, a);
}

long long modInverse(long long a, long long m)
{
    /**
     * Extended Euclidean Algorithm.
     * Allows finding both the GCD and the modular inverse in one go
     */
    long long m0 = m;
    long long y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    // Ensure x is positive
    x = x % m0;
    if (x < 0)
    {
        x = (x + m0) % m0;
    }

    return x;
}

int main()
{
    /**
     * This is a main function which generates the public and the private keys.
     * It calls a utility file to get the prime numbers
     */
    vector<int> prime_numbers = generatePrimeNumbers();

    // Store the prime numbers generated in the variables
    const long long int P = prime_numbers[0];
    const long long int Q = prime_numbers[1];

    const long long N = P * Q;
    const long long EULER_TOTIENT = (P - 1) * (Q - 1);

    // Define the Public Encryption key E
    long long int E = 2;

    while (gcd(E, EULER_TOTIENT) != 1 || gcd(E, N) != 1)
    {
        E++;
    }
    // The loop exits with the public encryption E

    // Get the private Decryption key using the extended euclidean algorithm
    long long int D = modInverse(E, EULER_TOTIENT);

    // Verify the equation E * D MOD EULER_TOTIENT = 1
    if ((E * D) % EULER_TOTIENT != 1)
    {
        std::cerr << "Could not generate keys. Please retry again" << std::endl;
    }

    // Open the file "public_key.rsa" in write ("w") and truncate mode ("t")
    FILE *public_file = fopen("public_key.rsa", "wt");

    if (public_file != nullptr)
    {
        // Write e and N to the file, separated by a comma
        fprintf(public_file, "%lld,%lld", E, N);
        fclose(public_file);
    }
    else
    {
        std::cerr << "Error opening file for writing." << std::endl;
    }

    FILE *private_file = fopen("private_key.rsa", "wt");

    if (private_file != nullptr)
    {
        // Write e and N to the file, separated by a comma
        fprintf(private_file, "%lld,%lld", D, N);
        fclose(private_file);
    }
    else
    {
        std::cerr << "Error opening file for writing." << std::endl;
    }

    return 0;
}