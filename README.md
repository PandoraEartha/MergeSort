# Merge Sort C++ implementation

## Usage

```
#include "MergeSort.h"

std::vector<double> array(12345678);
MergeSort(array.data(),array.size());
```

## Speed Test (compare with std::sort)

100000000 `unsigned` array, test on 9950x3D with g++ `-O2`

### Random array

`MergeSort`: 4.967 second

`std::sort`: 5.605 second

