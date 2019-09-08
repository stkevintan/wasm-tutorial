#include "lib.h"

#define N 10000
#define swap(a, b) int tmp = a; a = b; b = tmp;

extern "C"
{
  int arr[N];
  extern int getSize();

  void quickSort(const int *array, int start, int end)
  {
    if (end - start <= 0)
      return;
    int left = start;
    int right = end - 1;
    while (left < right)
    {
      if (arr[left] > arr[left + 1])
      {
        swap(arr[left], arr[left + 1]);
        left++;
      }
      else
      {
        swap(arr[right], arr[left + 1]);
        right--;
      }
    }
    quickSort(arr, start, left);
    quickSort(arr, left + 1, end);
  }

  void WASM_EXPORT sort() { quickSort(arr, 0, getSize()); }
  int WASM_EXPORT *getArrayOffset() { return arr; }
}
