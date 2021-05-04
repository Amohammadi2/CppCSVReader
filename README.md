# CppCSVReader
a simple and light-weight csv reader built on top of C++

## build
you should build this source code before you can use it. The source code is developed with VS2017.
### requirements
- `visual studio 2017`
- `visual C++ build tools`

## usage
```C++
#include "CppCSVReader.h"

int main() {

  std::ifstream input_file("path/to/file.csv");
  const char delimiter = ',';
  csv::CSVReader reader(input_file, delimiter);
  
  for (auto const& row : reader.csvRows) {
  
    for (auto const& col : row.csvColumns) {
    
      if (col.is_str) {
        std::cout << col << "|";
      }
      
      else { // is a `double`
        std::cout << col.data.d_data + 45 << "|";
      }
      
    }
  }
}
```
