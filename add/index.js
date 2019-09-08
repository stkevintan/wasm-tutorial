async function init() {
  const { instance } = await WebAssembly.instantiateStreaming(
    fetch("./index.wasm")
  );
  console.log('add result: ',instance.exports.add(4, 1));
}
init();