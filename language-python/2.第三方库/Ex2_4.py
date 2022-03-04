# -*- coding: utf-8 -*-
'''
Ex2_4.数据探索分析是指对数据进行缺失值、异常值查找以及统计分析，分析出数据的规律以及异常值。
      保存在文件“air_data.csv”中的数据为某航空公司的大量会员档案信息及其乘坐航班记录。
      通过观察可以发现，原始数据中存在票价为空值，票价最小值为0、折扣率最小值为0、总飞行公里数大于0的记录。
      票价为空值的数据可能是客户不存在乘机记录造成，其它的数据可能是客户乘坐0折机票或者积分兑换产生的。      
程序代码” data_explore.py”旨在考察每个属性的观测值中空值个数、最大值和最小值。
请读懂程序的每行代码，学习与领会pandas库中数据框(dataframe)的基本用法。
运行这个程序，并查看运行结果，然后小幅修改代码，完成填写下列表格的空白处。
'''
# 对数据进行基本的探索
# 返回缺失值个数以及最大最小值

import pandas as pd

datafile = 'air_data.csv'
resultfile = 'explore.xls'

data = pd.read_csv(datafile, encoding='utf-8')
explore = data.describe(percentiles=[0.25], include='all').T

explore['null'] = len(data)-explore['count']

explore = explore[['null', 'max', 'min', 'mean', 'std']]

explore.columns = [u'空值数', u'最大值', u'最小值', u'平均值', u'标准差']

explore.to_excel(resultfile)
