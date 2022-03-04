# -*- coding: utf-8 -*-
'''
Ex2_3.利用scipy.integrate模块计算函数x^2+sin⁡(x)+√x+x^(1/3)+1在区间[1,2]上的定积分。
'''
from scipy import integrate
from scipy import sin

print(integrate.quad(lambda x: x**2 + sin(x) + x**0.5 + x**(1/3) + 1, 1, 2))
