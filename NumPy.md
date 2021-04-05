# NumPy

* Numpy is a Python package that allows to efficiently store and process large array of numerical data like sound data and image data.

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