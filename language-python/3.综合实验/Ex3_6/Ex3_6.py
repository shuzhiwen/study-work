# -*- coding: utf-8 -*-
'''
Ex3_6. Cython编程入门（请根据PPT课件自行安装C语言编译工具）。
  下列代码中的函数fib旨在计算斐波那契数列：(见图片)

  创建文件”fib1.py”和”fib2.pyx”，内容均为上述代码，不作任何修改。
  创建” fib3.pyx”, 对上述代码做小幅修改，加入一些C语言元素，尽可能优化性能。
  编写“setup.py”，对cython代码文件”fib2.pyx”和 ” fib3.pyx”进行编译。
  接下来创建“Ex3_6.py”文件，内容如下：(见图片)
  
  将运行结果截图，展示在此处。
'''
import fib1
import fib2
import fib3

n = 40
print("Pure python: ")
fib1.fibtime(n)
print("Py in Cython: ")
fib2.fibtime(n)
print("C in Cython: ")
fib3.fibtime(n)
