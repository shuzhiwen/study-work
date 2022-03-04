# -*- coding: utf-8 -*-
import time

def fib(n):
  if n == 0: return 0
  if n == 1: return 1
  return fib(n - 1) + fib(n - 2)
def fibtime(n):
  t = time.time()
  print(fib(n))
  print(time.time() - t)