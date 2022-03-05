#include <iostream>

#define DECIMAL_A_VALUE 65

using namespace std;

int main()
{
  // each testcase
  int n;
  cin >> n;
  while (n > 0)
  {
    // each string
    int l;
    cin >> l;
    int hash = 0;
    for (int i = 0; i < l; ++i)
    {
      // each char
      string str;
      cin >> str;
      for (int j = 0; j < str.length(); ++j)
        hash = hash + (int)str[j] - DECIMAL_A_VALUE + i + j;
    }
    cout << hash << endl;
    --n;
  }
  return 0;
}