import time

def isPrime(num):
    count = 0;
    for i in range(1, num+1):
        if num % i == 0:
            count += 1
    return count == 2;

def findPrimes(startSearch, stopSearch):
    count = 0;
    for x in range(startSearch, stopSearch+1):
        if isPrime(x):
            count += 1
    print(':', count, " primes are in this range")     

start = int(round(time.time() * 1000))
findPrimes(0, 20000)
time = int(round(time.time() * 1000)) - start
print(':', time, 'time to find primes')
