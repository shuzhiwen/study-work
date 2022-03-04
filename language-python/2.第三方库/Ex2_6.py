# -*- coding: utf-8 -*-
'''
Ex2_6.画一张图，包含5幅子图，布局为：第一行2幅，左边为柱状图（bar plot），
      右边为散点图(scatter plot)；第二行2幅，左边为饼图（pie plot），
      右边为折线图（plot），第三行1幅子图，为直方图（histogram plot）。
      相关数据请自行随机创建或从网上采集。每幅子图要有相应的标题，表示什么类型的图。
      可参考的源文件有：“ch6_histgram_plot.py”、“ch6_pie_plot1.py”和“ch6_multiple_subplots.py”。
'''
import matplotlib.pyplot as plt
import numpy as np

t1 = np.random.randn(100)
t2 = np.random.randn(100)

# No.1
plt.figure(1)
# left
plt.subplot(221)
labels = ['Apple', 'Banana', 'Pear', 'Peach']
colors = ['yellowgreen', 'gold', 'lightskyblue', 'lightcoral']
num = [40, 100, 20, 70]
plt.bar(range(len(num)), num, color=colors, tick_label=labels)
plt.title('Bar Plot')
# right
plt.subplot(222)
plt.scatter(t1, t2)
plt.title('Scatter Plot')

# No,2
plt.figure(2)
# left
plt.subplot(221)
labels = ['Apple', 'Banana', 'Pear', 'Peach']
sizes = [22, 38, 11, 29]
colors = ['yellowgreen', 'gold', 'lightskyblue', 'lightcoral']
explode = (0, 0.1, 0, 0)
plt.pie(sizes, explode=explode, labels=labels, colors=colors,
        autopct='%.1f%%', shadow=True, startangle=90)
plt.axis('equal')
plt.title('Pie Plot')
# right
plt.subplot(222)
x = range(0, 10)
y = [10, 20, 5, 40, 30, 60, 70, 12, 55, 25]
plt.plot(x, y, linewidth=3, color='b')
plt.title('Plot')

# No.3
plt.figure(3)
plt.subplot(211)
mu, sigma = -1, 1
x = mu+sigma*np.random.randn(10000)
n, bins, patches = plt.hist(x, 100, normed=1, facecolor='r', alpha=0.75)
plt.title('Histogram Plot')
plt.text(3.5, .4, r'$\mu=-1,\ \sigma=1$')
plt.axis([-5, 3, 0, 0.5])

plt.show()
