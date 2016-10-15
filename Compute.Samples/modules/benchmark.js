
const Benchmark = require('benchmark');
const console = require('console');
const suite = new Benchmark.Suite;

suite.add('RegExp#test', () => /o/.test('Hello World!'))
  .add('String#indexOf', () => 'Hello World!'.indexOf('o') > -1)
  .add('String#match', () => !!'Hello World!'.match(/o/));

suite.on('cycle', event => console.log(String(event.target)))
 .on('complete', () => console.log('Fastest is ' + suite.filter('fastest').map('name')))
 .run({ 'async': true });