
const console = require('console');

const isPrime = (num) => {
    let timesReminderEqualsZero = 0;
    for (let i = 1; i <= num; ++i) {
        if (num % i == 0) {
            ++timesReminderEqualsZero;
        }
    }
    return timesReminderEqualsZero == 2;
}

const findPrimes = (start, stop) => {
    let count = 0;
    for (let i = start; i <= stop; ++i) {
        if (isPrime(i)) {
            ++count;
        }
    }

    console.log(count + " primes are in this range");
}

const startTime = (new Date()).getTime();
findPrimes(0, 20000);
console.log(((new Date()).getTime() - startTime) + 'ms time to find primes');
