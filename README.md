# `prolib`: PRO1 and PRO2 library

This is a C++ library to support teaching [PRO1](https://pro1.cs.upc.edu) and [PRO2](https://pro2.cs.upc.edu) courses, at [FIB](https://fib.upc.edu).

Right now, we have:
-   `pro2::BinTree<T>`: a binary tree holding values of any type `T`.
-   `pro2::Tree<T>`: a tree with any number of children holding values of type `T`.

Both have `operator<<` for writing.

## `BinTree` Example

The following code:

```c++
#include <iostream>
using namespace std;

#include "bintree.hh"
#include "bintree-io.hh"
using namespace pro2;

int main() {
    BinTree<int> t0(0), t1(1);
    BinTree<int> t2(2, t0, t1);

    cout << t2;
}
```

produces:

```text
2
|-- 0
'-- 1
```
