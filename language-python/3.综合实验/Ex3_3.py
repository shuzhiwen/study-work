# -*- coding: utf-8 -*-
'''
Ex3_3. 数据随机存储，掌握os与random模块的用法以及文件读写方法。
  定义一个函数fs(dirname,s)，其中参数dirname表示文件夹路径名，s为字符串，表示需要保存的数据。
  函数fs的功能是随机地将字符串s存储到dirname路径下某个文本文件(“*.txt”文件)中。
  假如dirname路径下已有”a.txt”、 ”b.txt”、 ”c.txt”三个或更多文本文件，
  字符串s可能被保存到”a.txt”，或”b.txt”，或 ”c.txt”，或其他文件，机会是相同的，并且不能覆盖原有的文本文件。
  如果dirname路径下不存在任何文本文件，则新创建“new.txt”文件来保存字符串s。
'''
import os
import random


def fs(dirname, s):
    ans = list()
    for file in os.listdir(dirname):
        ex = os.path.splitext(file)[1]
        if ex == '.txt':
            ans.append(file)
    if len(ans) == 0:
        f = open('new.txt', 'a', encoding='utf-8')
        f.write(s)
        f.close
    else:
        i = int(random.random() * len(ans))
        f = open(ans[i], 'a', encoding='utf-8')
        f.write(s)
        f.closed


ls = input('Please input the path:')
s = input('Please input the string:')
fs(ls, s)
