# -*- coding: utf-8 -*-
import time

cdef long long fib(int n):
  if n == 0: return 0
  if n == 1: return 1
  return fib(n - 1) + fib(n - 2)
def fibtime(int n):
  t = time.time()
  print(fib(n))
  print(time.time() - t)
