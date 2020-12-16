# Lab5: _Memory Access Optimization_

In this laboratory work demonstrates simple memory access optimization.

Initial code:
```
int a[50][50][50];
    
for (int i = 0; i < 50; i++)
{
   for (int j = 0; j < 50; j++)
   {
      for (int k = 0; k < 50; k++)
      {
         a[k][j][i]++;
      }
   }
}
```

Multi dimensional arrays are flat in memory. That means that accessing accessing multidimensional array is the same as accessing simple array.

`array[i][j]`

is converted into

`array[i * WIDTH + j]`

There is two ways to lay multidimensional array into the memory: row- and column-major
Row-major order means that elements in a row reside next to each other, column-major - elements in a column reside next to each other.

C++ has a row-major order therefore for maximum efficiency the code sample should be written as:
```
int a[50][50][50];
    
for (int i = 0; i < 50; i++)
{
   for (int j = 0; j < 50; j++)
   {
      for (int k = 0; k < 50; k++)
      {
         a[i][j][k]++;
      }
   }
}
```

## Benchmarks
Original:\
`Time: 515`

Optimized:\
`Time: 387`
