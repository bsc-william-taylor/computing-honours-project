
import computer from 'computer';
import console from 'console';

// Basic CPU properties
console.log(`Logical CPU core ${computer.cpuCount()}`);
console.log(`Cache Line Size ${computer.cpuCacheLineSize()} kb`);
console.log(`Ram ${computer.systemRam()} mb`);

// Instruction sets
console.log(`3DNow? ${computer.has3DNow()}`);
console.log(`AVX? ${computer.hasAVX()}`);
console.log(`AVX2? ${computer.hasAVX2()}`);
console.log(`AltiVec? ${computer.hasAltiVec()}`);
console.log(`MMX? ${computer.hasMMX()}`);
console.log(`RDTSC? ${computer.hasRDTSC()}`);
console.log(`SSE? ${computer.hasSSE()}`);
console.log(`SSE2? ${computer.hasSSE2()}`);
console.log(`SSE3? ${computer.hasSSE3()}`);
console.log(`SSE41? ${computer.hasSSE41()}`);
console.log(`SSE42? ${computer.hasSSE42()}`);
