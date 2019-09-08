#define WASM_EXPORT __attribute__((visibility("default")))

int WASM_EXPORT add(int a, int b)
{
  return a + b;
}