# -*- coding: utf-8 -*-
'''
2.2 利用re.sub函数进行字符串的替换任务。
    (1) 将下列文本中的电子邮件地址替换为你自己的电子邮件地址(hime@163.com):
        s="hi69@qq.com, werksdf@163.com, sdf@sina.comsfjsdf@139.com, soifsdfj@134.com, pwoeir23@126.com"
    (2) 利用re.sub函数，将上述文本s中的数字加上212，重新输出。
'''

import re

s = "hi69@qq.com, werksdf@163.com, sdf@sina.comsfjsdf@139.com, soifsdfj@134.com, pwoeir23@126.com"


tar = re.sub('\w+@\w+\.com', 'hime@163.com', s)
print(tar)


def _add212(matched):
    intstr = matched.group("num")
    intvalue = int(intstr)
    addedvalue = intvalue + 212
    addedvaluestr = str(addedvalue)
    return addedvaluestr


tar = re.sub("(?P<num>\d+)", _add212, s)
print(tar)
