import quicksort from './quicksort.js'

let instance = null;
const N = 1000;


function array2Buffer(memory, offset, array) {
  const shared = new Uint32Array(memory.buffer, offset, array.length);
  array.forEach((c, i) => shared[i] = c);
}

function buffer2Array(memory, offset, len) {
  const shared = new Uint32Array(memory.buffer, offset, len);
  return Array.from(shared);
}

function getRandomArray(n) {
  const arr = [];
  while(n--) arr.push(Math.round(Math.random() * n));
  return arr;
}

fetch('./index.wasm').then(response =>
  response.arrayBuffer()
).then(bytes => WebAssembly.instantiate(bytes, {
   env: {
     getSize: () => N
  }
})).then(wasm => {
  instance = wasm.instance;
  const arr = getRandomArray(N);
  console.log(`[Before Sort]: ${arr}`);
  sortByWasm(arr);
  sortByJs(arr);
}).catch(console.error);


function sortByWasm(arr) {
  const { memory, sort, getArrayOffset } = instance.exports;
  const offset = getArrayOffset();
  array2Buffer(memory, offset, arr);
  const startTime = performance.now();
  sort();
  const endTime = performance.now();
  const array = buffer2Array(memory, offset, arr.length);
  console.log(`[After Sort By Wasm]: ${array.slice(0, 10)}...${array.slice(N - 10)} cost ${endTime - startTime}ms.`);
}

function sortByJs(arr) {
  const array = arr.slice();
  const startTime = performance.now();
  quicksort(array, 0, array.length);
  const endTime = performance.now();
  console.log(`[After Sort By js]: ${array.slice(0, 10)}...${array.slice(N - 10)} cost ${endTime - startTime}ms.`);
}

