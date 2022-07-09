# OldVal

Reuse old values with little syntactic boilerplate.

## Examples

### Re-use integer values

```
#include <OldVal.h>
#include <iostream>

using OldInt = Old<int>;

void Update(OldInt a, OldInt b, OldInt c)
{
    a = b + 1;
    b = a + 1;
    c = a + 2;
}

int main()
{
	int a = 2;
	int b = 0;
	int c = 0;
	Update(a, b, c);
	
	// Output: 1 3 4
	std::cout << a << " " << b << " " << c << "\n"; 

	return 0;
}
```