# -*- coding: utf-8 -*-
'''
Ex3_1. 了解时间模块time和datetime。
(1) 利用time.time()获取当前的时间戳。
(2) 用datetime.date.today()获取当前的日期。
(3) 自行查询使用方法，用datetime模块返回一个月前的日期。
'''
import time
import datetime

print(time.time())
print(datetime.date.today())
print(datetime.date.today() + datetime.timedelta(days=-30))
