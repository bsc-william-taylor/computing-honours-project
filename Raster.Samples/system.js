
const console = require('console');
const system = require('system');

console.log(`Logical CPU core ${system.cpuCount()}`);
console.log(`Cache Line Size ${system.cpuCacheLineSize()} kb`);
console.log(`Ram ${system.systemRam()} mb`);
console.log(`3DNow? ${system.has3DNow()}`);
console.log(`AVX? ${system.hasAVX()}`);
console.log(`AVX2? ${system.hasAVX2()}`);
console.log(`AltiVec? ${system.hasAltiVec()}`);
console.log(`MMX? ${system.hasMMX()}`);
console.log(`RDTSC? ${system.hasRDTSC()}`);
console.log(`SSE? ${system.hasSSE()}`);
console.log(`SSE2? ${system.hasSSE2()}`);
console.log(`SSE3? ${system.hasSSE3()}`);
console.log(`SSE41? ${system.hasSSE41()}`);
console.log(`SSE42? ${system.hasSSE42()}`);
