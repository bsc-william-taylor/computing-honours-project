
//const console = require('console');
//const async = require('async');

const { setTimeout, pause } = require('datetime');
const console = require('console');

setTimeout(() => {
  let i = 0;
  console.log('helloworld');
}, 2000);
/*
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
]);*/