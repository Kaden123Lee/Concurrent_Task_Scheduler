#include <cmath>
#include <vector>
#include <algorithm>

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
void el_prime(std::vector<bool>& vc, int index) {
    int number = index * index;

    while (number < vc.size()) {
        vc[number] = false;
        number += 2 * index;
    }
}

int PPN_medium(int start_num, int end_num) {
    int count_prime = 0;
    std::vector<bool> isPrime((end_num - start_num) + 1, true);  

    // Only process odd candidates : i dont think we change this it seems essential. 
    for (int i = 3; i * i <= end_num; i += 2) {
        if (isPrime[i]) { // I belive this is a problem : we are saying if the first one is true, then you take
            el_prime(isPrime, i);
        }
    }

    // Handle 2 separately
    if (start_num <= 2 && end_num >= 2) {
        count_prime++;
    }

    // Start counting from an odd number >= 3
    int start = std::max(start_num, 3);

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


int PPN_large(int start_num, int end_num){
    // Step # 1 : Find all the primes from 0 -> sqrt(end_num) 
    // Also we are going to be working with 2 vectors in this area so def room for improvement
    int limit = sqrt(end_num); // We dont want to go past this
    std::vector<bool> smallPrime(limit + 1, true);
    smallPrime[0] = false; 

    if(limit > 1){
        smallPrime[1] = false; 
    }

    for(int p = 2; p * p <= limit; ++p){
        if(smallPrime[p]) {
            for(int multiple = p * p; multiple <= limit; multiple += p){
                smallPrime[multiple] = false; 
            }
        }
    }

    // Step # 2 : This vector repersents only from start_num -> end_num
    std::vector<bool> isPrime((end_num - start_num) + 1, true);

    //Step # 3 : Take each small prime and eliminate its multiples inside of our segment
    /*
    Take p
    ↓
    Find first multiple of p in our segment
    ↓
    Jump through the segment by p
    ↓
    Mark each of those multiples false
    */
    for(int p = 2; p <= limit; ++p){
        if(!smallPrime[p]){
            continue;
        }

        // Find the first multiple of p >= start_num, we dont want to check every number in the segment. This caluclates where to start
        // from the small prime to the others even tho they might not be in the bigger vector like 105 is divisable by 7,
        // so we need to know is that the first one we should elminiate? is it even in the vector we are working with?
        // Find where prime p should begin crossing things out in this segment.
        int first = ((start_num + p - 1) / p ) * p;
        // Don't eliminate p itself. 
        first = std::max(first, p * p);
        for(int number = first; number <= end_num; number += p){
            // number is the real number , number - start = its vector index
            isPrime[number - start_num] = false; 
        }
    }
    

    // Step #4: 0 and 1 are not primes.

    for(int number = start_num; number <= std::min(end_num, 1); ++number){ // Stop at whichever is smaller: end_num or 1.
        if(number >= 0){
            isPrime[number - start_num] = false; 
        }
    }

    //Step #5: Count whatever survived.
    int count_prime = 0;

    for(int number = std::max(start_num, 2); number <= end_num; ++number){
        if(isPrime[number - start_num]){
            count_prime++;
        }
    }
    return count_prime;

}