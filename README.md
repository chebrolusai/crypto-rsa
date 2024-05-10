<h1 align="center"> 🔑 Cryptography (RSA)</h1>

This project is the implementation of the RSA Algorithm.

<h5>Built with: </h5>
<img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white">

# About

- ### Prime Numbers

  The algorithm begins with generating a private key and a public key. For this to happen, it requires two <b>Prime Numbers</b>.

  1. It generates two random numbers between 4-5 digits
  2. It looks for the closest prime numbers from the random numbers
  3. A Miller-Rabin primality test is performed on the given number. The test works well for large prime numbers compared to the traditional approach and is not compute intensive.

  <b>Note:</b> _Miller-Rabin primality is a probabilistic test that tells whether a number is likely prime. This test is not deterministic and there couble be a very small probability of error._
