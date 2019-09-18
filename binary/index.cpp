#define WASM_EXPORT __attribute__((visibility("default")))

int WASM_EXPORT add(int a, int b)
{
  return a + b;
}

double WASM_EXPORT add(double a, double b)
{
  return a + b;
}

int WASM_EXPORT minus(int a, int b)
{
  return a - b;
}

int main()
{
  return 0;
}