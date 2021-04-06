# NumPy

* Numpy is a Python package that allows to efficiently store and process large array of numerical data like sound data and image data.

* Numpy library provides a simple yet powerful data structure: the **n-dimensional array**. Many of Python most popular libraries are built on top of Numpy.

* Numpy uses simple Python syntax to perform complex operations on arrays.

* It is a common practice to import numpy as np.

```
import numpy as np
```

| Methods       | Description |
|---------------|-------------|
| `np.zeros(5)`   | array of zeros |
| `np.zeros((3,4))` | 2D array of (3, 4) |
| `np.array`

```python
# create array of zeros
np.zeros(5)

# 2D array of size (3,4)
m = np.zeros((3, 4))

# initialize array from values
a = np.array([1, 2, 3, 4, 5])

# multi-dimensional array
m = np.array([[1, 2], [3, 4], [5, 6]])
```

* Arithmetic operations on numpy arrays, get automatically applied to each individual element of the array. This is called **_vectorisation_**.

* **Vectorization** is the process of performing the same operation in the same way for each element in an array.

* **Broadcasting** is the process of extending two arrays of different shapres and figuring out how to perform a vectorized calculation between them.

```python
x = np.array([1, 2, 3, 5])
y = np.array([6, 7, 8, 9])
z = x + y
print(z)

output:
[ 7  9 11 14]
```

* Numpy has its own version of common math functions like sin, cos, exp etc that are applied to each element of the array.

```python
a = np.array([1, 4, 9, 16])
b = np.sqrt(a)
```

* Numpy arrays can be sliced just like Python lists.

* In addition to array methods Numpy also has a large number of built-in functions.

* All arrays have a property called `.shape` that returns a tuple of the size in each dimension.

* In NumPy arrays, axes are zero-indexed and identify which dimension is which. A 2-D array has a vertical axis (| - axis 0) and a horizontal axis (-- axis 1).

```python
import numpy as np
table = np.array([
    [5, 3, 7, 1],
    [2, 6, 7, 9],
    [1, 1, 1, 1],
    [4, 3, 2, 0],
])

table.max() # 9
table.max(axis=0) # array([5, 6, 7, 9])
table.max(axis=1) # array([7, 9, 1, 4])
```

* Arrays can be broadcasted against each other if their dimensions match or if one of the arrays has a size of 1.

* `A = np.arange(32).reshape(4, 1, 8)` <br>
  A has 4 planes, each with 1 row and 8 columns. <br>
  `B = np.arange(48).reshape(1, 6, 8)` <br>
  B has 1 plane with 6 rows and 8 columns.

* NumPy arrays use commas between axes, so that multiple axes indexed in one set of square brackets.

```python
# Durer magic square
# add up any of the rows, columns, or diagonals, then you’ll get the same number, 34. 
square = np.array([
    [16, 3, 2, 13],
    [5, 10, 11, 8],
    [9, 6, 7, 12],
    [4, 15, 14, 1]
])
```
 