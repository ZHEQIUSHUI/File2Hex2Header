# File2Hex2Header

## example

### create header file
```
#include "File2Hex2Header.h"
int main()
{
  File2Header("filename for input", "header filename for output");
  return 0;
}
```

### export file
```
#include "generated header filename"
int main()
{
  std::string ctx(buf, buf + _countof(buf));
  writefile(ctx, "filename for output");
  return 0;
}
```
	
