var genRandomArray = function(length, minvalue, maxvalue, options){
    var opt = options || {};
    var round = opt.round;
    return Array.apply(null, {length:length}).map(function(){
        var result = Math.random() * (maxvalue - minvalue) + minvalue;
        if(round ===  true){
            return Math.round(result);
        }
        return result;
        });
};


module.exports = function(minvalue, maxvalue){
   return{ 
    oned: function(length, options){
        return genRandomArray(length, minvalue, maxvalue, options);
    },

    twod: function(width,height, options){
            return Array.apply(null, {length: width}).map(function(){ return genRandomArray(height, minvalue, maxvalue, options);}); 
    },

    genWhile: function(func, options) {
        var result = [];
        var opt = options || {};
        var limit = opt.limit || 10000;
        var c = 0;
        while(c !== limit){
            var item = Math.random() * (maxvalue - minvalue) + minvalue;
            result.push(item);
            if(func(item)) {
                return result;
            }
            c += 1;
        }
        return result;
    },
   };
};

