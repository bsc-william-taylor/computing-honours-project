const v8flags = require('v8flags');

v8flags(function (err, results) {
  results.forEach(arg => {
      if(arg.includes('debug')) {
          console.log(arg);
      }
  })
});