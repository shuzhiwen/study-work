# -*- coding: utf-8 -*-
'''
Ex3_4. 类的定义以及实例化测试。
  要求定义一个学生类Student。有下面的类属性：
    (a)姓名name
    (b)年龄age
    (c)成绩scores, 类型为列表或元组，形如（语文，数学，英语)
  类方法：
    (a)获取学生的姓名：get_name() 
    (b)获取学生的年龄：get_age() 
    (c)返回3门科目中最高的分数: get_course() 
  写好类以后，给定1个同学进行实例化测试，例如:
    zm = Student('zhangming', 20, [69,88,100])
  返回结果：
    zhangming
    20
    100
'''


class Student:
    '''student's information'''

    def __init__(self, name, age, scores):
        self.name = name
        self.age = age
        self.scores = scores

    def get_name(self):
        return self.name

    def get_age(self):
        return self.age

    def get_course(self):
        self.scores = sorted(self.scores, reverse=True)
        return self.scores[0]


zm = Student('zhangming', 20, [69, 88, 100])
print(zm.get_name())
print(zm.get_age())
print(zm.get_course())
