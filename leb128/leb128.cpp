#include <iostream>
#define LOW7BITS(x) (x & 0x7f)
#define EIGHT_BIT 0x80
#define SEVEN_BIT 0x40
using namespace std;

void encode_unsigned()
{
  unsigned number;
  cin >> dec >> number;
  while (true)
  {
    auto byte = LOW7BITS(number);
    number >>= 7;
    if (number != 0)
    {
      byte |= EIGHT_BIT;
    }
    cout << "0x" << hex << byte << ' ';
    if (number == 0)
    {
      break;
    }
  };
  cout << endl;
}

void decode_unsigned()
{
  unsigned number = 0;
  int shift = 0;
  while (true)
  {
    unsigned x;
    cin >> hex >> x;
    number |= LOW7BITS(x) << shift;
    shift += 7;
    if ((x & EIGHT_BIT) == 0)
      break;
  }
  cout << dec << number << endl;
}

void encode_signed()
{
  int number;
  cin >> dec >> number;
  int sign = number >> (8 * sizeof(number) - 1);
  while (true)
  {
    unsigned byte = LOW7BITS(number);
    number >>= 7;
    bool isMore = number != sign || ((byte ^ sign) & SEVEN_BIT) != 0;
    if (isMore)
    {
      byte |= EIGHT_BIT;
    }
    cout << "0x" << hex << byte << ' ';
    if (!isMore)
      break;
  }
  cout << endl;
}

void decode_signed()
{
  int number = 0;
  int shift = 0;
  int x = 0;
  while (true)
  {
    cin >> hex >> x;
    number |= LOW7BITS(x) << shift;
    shift += 7;
    if ((x & EIGHT_BIT) == 0)
    {
      // add sign
      if (shift < sizeof(number) * 8 && (SEVEN_BIT & x))
      {
        number |= -1 << shift;
      }
      break;
    }
  }
  cout << dec << number << endl;
}

int main()
{
  short x;
  while (true)
  {
    cout << "Enter the operation type: \n0 - exit\n1 - encode unsigned integer \n2 - decode unsigned integer \n3 - encode signed integer\n4 - decode signed integer" << endl;
    cin >> x;
    switch (x)
    {
    case 1:
      encode_unsigned();
      break;
    case 2:
      decode_unsigned();
      break;
    case 3:
      encode_signed();
      break;
    case 4:
      decode_signed();
      break;
    default:
      break;
    }
    if (x == 0)
      break;
  }

  cout << "bye." << endl;
}
