# random-array [![Build Status](https://travis-ci.org/saromanov/random-array.svg?branch=master)](https://travis-ci.org/saromanov/random-array)
Generating  array of random numbers

## Install
``` npm install random-array ```

## Usage
```javascript
var random = require('random-array');
//Generate array of size 10 between 1 and 10
random(1,10).oned(10);
//Generate array of width 3 and height 2 between 1 and 10
random(1,10).twod(3,2);
//Generate array of size 10 and round numbers between 1 and 10
random(1,10).oned(10, {round: true});
```

Generate array of random numbers, while function is false.
```javascript
var random = require('random-array');
random(1,10).genWhile(function(x){ return Math.round(x) > 8;});
```

and output:
```
[ 4.424256478203461,
  4.920260030310601,
  4.706073637586087,
  5.157449695048854,
  9.543757784646004 ]
```
Because was found value 9.5437, function returns true and generation was stopped.

You can limit number of generation values:
```javascript
random(1,10).genWhile(function(x){ return x === 11;}, {limit: 10});
```

# License
MIT
