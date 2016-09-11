import time

def isPrime(num):
    count = 0;
    for i in range(1, num+1):
        if num % i == 0:
            count += 1
    return count == 2;

def findPrimes(start, stop):
    count = 0;
    for x in range(start, stop+1):
        if isPrime(x):
            count += 1
    print("%d primes are in this range" % count)

start = int(round(time.time() * 1000))

findPrimes(0, 20000)

time = int(round(time.time() * 1000)) - start

print('%dms time to find primes' % time)
