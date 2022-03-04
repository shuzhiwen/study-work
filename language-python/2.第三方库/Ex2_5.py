# -*- coding: utf-8 -*-
'''
Ex2_5.产生10000个随机数，服从均值为-1，标准差为1的正态分布N(-1,1)，
      利用matplotlib画出其直方图(100个bin)，即这10000个数的实际分布图。
      可参考源文件 “ch6_histgram_plot.py”中的代码。
'''
import numpy as np
import matplotlib.pyplot as plt

mu, sigma = -1, 1
x = mu+sigma*np.random.randn(10000)

n, bins, patches = plt.hist(x, 100, normed=1, facecolor='r', alpha=0.75)
plt.xlabel('Row')
plt.ylabel('Col')
plt.title('Homework')
plt.text(3.5, .4, r'$\mu=-1,\ \sigma=1$')
plt.axis([-5, 3, 0, 0.5])
plt.grid(True)
