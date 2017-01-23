var random = require('./index.js');
var assert = require("assert");

describe('Test generation 1d array', function(){
    it('should return 2', function(){
        assert.deepEqual(random(2,2).oned(1, {round:true}), [2]);
    }),

    it('should return random array of numbers between [0,10] of length 100', function(){
        var result = random(0,10).oned(100);
        assert.equal(result.length,100);
        assert.equal(result.filter(function(x){ if (x < 0 || x > 10) return x;}).length,0);

    })
    
});

describe('Test generation 2d array', function(){
   it('should return random 2d array of dimension 3x2', function(){
       var result = random(0,10).twod(3,2);
       assert.equal(result.length,3);
       assert.equal(result[0].length,2);
   })
});


describe('Test generation while not found target value', function(){
    it('should return 10000 values', function(){
        var result = random(0,10).genWhile(function(i){ return i === 11;});
        assert.equal(result.length,10000);
    });

    it('should return 25 values', function(){
         var result = random(0,10).genWhile(function(i){ return i === 11;}, {limit: 25});
         assert.equal(result.length, 25);
    });

    it('should return value greater then 0', function(){
        var result = random(0,10).genWhile(function(i){ return Math.round(i) === 5;});
        assert.notEqual(result.length,0);
    });

});
