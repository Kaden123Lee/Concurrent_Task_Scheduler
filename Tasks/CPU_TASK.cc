#include <cmath>
/*
Notes: After thinking out the fast way to calculate prime numbers i went back to what i knew, there is not a fits right all solution
as such iv desided to implment 5 kinds.

Format Code: ctr + shift + i 



*/

/*

Trial Division / Brute Force

For every number, test whether it's prime individually.
Great baseline.
Also interesting for scheduler load balancing because individual numbers are independent tasks.

Basic Sieve of Eratosthenes
Baseline implementation.
O(n log log n), O(n) memory.
Best for smaller ranges.

Optimized Sieve
Skip evens.
Start marking at p².
More cache/memory efficient.
Gives you something to compare against the naive implementation.

Segmented Sieve
Break a huge range into chunks.
Most important one for your threading project.
Segments naturally become scheduler tasks.
Experiment with segment size and worker count.

Lehmer Prime Counting
For extremely large n.
Only returns number of primes, not the primes themselves.
Sublinear approach.
Gives your scheduler a fundamentally different computational strategy.

*/

int PPN_Brute(int start_num, int end_num)
{
    int count_prime = 0;
    // Go through every number in the range
    for (int i = start_num; i <= end_num; ++i) {
        // 0 and 1 are not prime
        if (i < 2) {
            continue;
        }
        // Assume prime until we find a divisor
        bool is_prime = true;
        // Try every possible divisor
        for (int j = 2; j < i; ++j) {

            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        // Nothing divided i
        if (is_prime) {
            count_prime++;
        }
    }
    return count_prime;
}
/*
Sieve : If 2 is prime, then every multiple of 2 is definitely not prime. // Basic Sieve of Eratosthene

*/
void el_prime(vector<bool>& vc, int index) {
    int number = index * index;

    while (number < vc.size()) {
        vc[number] = false;
        number += 2 * index;
    }
}

int PPN_medium_small(int start_num, int end_num) {
    int count_prime = 0;
    vector<bool> isPrime(end_num + 1, true);

    // Only process odd candidates
    for (int i = 3; i * i <= end_num; i += 2) {
        if (isPrime[i]) {
            el_prime(isPrime, i);
        }
    }

    // Handle 2 separately
    if (start_num <= 2 && end_num >= 2) {
        count_prime++;
    }

    // Start counting from an odd number >= 3
    int start = max(start_num, 3);

    if (start % 2 == 0) {
        start++;
    }

    // Only check odd numbers
    for (int i = start; i <= end_num; i += 2) {
        if (isPrime[i]) {
            count_prime++;
        }
    }

    return count_prime;
}


int PPN_large(int start_num, int end_num)
{
    // Segmented Sieve should be the one you push to the brink.
}

int PPN_largest(int start_num, int end_num)
{
    //Lehmer Prime Counting
}
