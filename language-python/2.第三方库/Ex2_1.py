# -*- coding: UTF-8 -*-
'''
Ex2_1.利用numpy中相关模块，产生10000个在[-1,1]区间之中的随机数，
      以及随机产生10000个服从标准正态分布的数，由此我们得到两个一维数组， 
      分别记为A和B。利用numpy中的普通函数或ufunc函数计算下列式子的值：
(a) A+B
(b) A和B的乘积
(c) A/B
(d) exp(A)+exp(B)
(e) A和B的内积
(f) 数组B中所有元素的平均值，最大值，最小值。
'''
import numpy as np

A = np.random.uniform(-1, 1, 10000)
B = np.random.randn(10000)

print(A)
print()

print(B)
print()

print(np.add(A, B))
print()

print(np.multiply(A, B))
print()

print(np.divide(A, B))
print()

print(np.add(np.exp(A), np.exp(B)))
print()

print(np.dot(A, B))
print()

print(np.mean(B))
print(np.max(B))
print(np.min(B))
