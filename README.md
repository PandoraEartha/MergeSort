# Merge Sort C++ implementation

## Usage

```c++
#include "MergeSort.h"

std::vector<double> array(12345678);
MergeSort(array.data(),array.size());
```

## Speed Test (compare with std::sort)

100000000 `unsigned` array, test on 9950x3D with g++ `-O2`

### Random array

`MergeSort`: 4.967 second

`std::sort`: 5.605 second

### 80% sorted array

`MergeSort`: 2.755 second

`std::sort`: 3.713 second

### Sorted array

`MergeSort`: 0.020 second

`std::sort`: 0.756 second

### Reversed array

`MergeSort`: 0.036 second

`std::sort`: 0.502 second
