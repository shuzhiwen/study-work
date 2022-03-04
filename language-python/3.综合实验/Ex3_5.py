# -*- coding: utf-8 -*-
'''
Ex3_5. 类的定义以及实例化测试。
  定义一个列表的操作类Listinfo，包括的方法:
    (a)列表元素添加: add_elem (elename)  [elename:字符串或者整数类型]
    (b)列表元素取值： get_elem(num)   [num:整数类型]
    (c)列表合并： merge_list(ls)	  [ls:列表类型]
    (d)删除最后一个元素，并返回这个元素：del_lastone()
  写好这个类之后，进行实例化测试，某个实例对象创建可以如下：
    list_info = Listinfo([44,222,111,333,454,'sss','333'])
'''


class Listinfo:
    # List operation
    def __init__(self, l):
        self.l = l

    def add_elem(self, elename):
        self.l.append(elename)

    def get_elem(self, num):
        return self.l[num]

    def merge_list(self, ls):
        self.l = self.l + ls

    def del_lastone(self):
        data = self.l[len(self.l) - 1]
        del self.l[len(self.l) - 1]
        return data


list_info = Listinfo([44, 222, 111, 333, 454, 'sss', '333'])
list_info.add_elem(234)
print('Add data:', list_info.l)
print('Get third data:', list_info.get_elem(2))
list_info.merge_list([999, 'ppp'])
print('Merge list:', list_info.l)
print('Delete data:', list_info.del_lastone(), '\n', list_info.l)
