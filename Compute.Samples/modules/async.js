
const console = require('console');
const async = require('async');

async.series([
  function(callback) {
    console.log("one")
    callback();
  },
  function(callback) {
    console.log("two")
    callback();
  },
  function(callback) {
    console.log("three")
    callback();
  }
]);