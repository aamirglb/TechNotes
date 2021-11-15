#!/usr/bin/env python3

def add(self, a: int, b: int) -> int:
    return a+b

class IntClass:
    def __init__(self, a: int, b: int):
        self._a = a
        self._b = b

class StrClass:
    def __init__(self, x: str, y: str):
        self._x = x
        self._y = y

a = IntClass(10, 20)
print(a.add())

b = StrClass("ten", "twenty")
print(b.add())