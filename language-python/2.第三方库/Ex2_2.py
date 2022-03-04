# -*- coding: utf-8 -*-
'''
Ex2_2.假设已有下列代码：
      import numpy as np
      import math
      def myfun(x):
	      return math.cos(x)
显而易见，函数myfun()还不是一个ufunc函数，请定义一个新函数nmyfun()，
使得 myfun成为一个ufunc函数。进一步，分别记录nmyfun和np.cos() 
在计算1~100000之间共计10万个正整数的余弦值时所需的时间（要求利用ufunc运算），
比较两者的计算速度。
'''
import numpy as np
import time


def nmyfun(x):
    return np.cos(x)


A = [i for i in range(100000)]

start = time.clock()
nmyfun(A)
times = time.clock() - start
print('nmyfun   needs %f times!' % times)

start = time.clock()
for i in A:
    np.cos(i)
times = time.clock() - start
print('np.cos() needs %f times!' % times)
