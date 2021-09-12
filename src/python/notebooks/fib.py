#!/usr/bin/env python3

def fib(n):
    """
    Return a list of the first n Fibonacci numbers.
    """

    f0, f1 = 0, 1
    f = [1] * n
    for i in range(1, n):
        f[i] = f0 + f1
        f0, f1 = f1, f[i]

    return f

print(fib(10))
