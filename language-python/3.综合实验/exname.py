# -*- coding: utf-8 -*-
import os


def fex(dirpwd):
    ans = list()
    for file in os.listdir(dirpwd):
        flag = 1
        ex = os.path.splitext(file)[1]
        for i in ans:
            if ex == '' or ex == i:
                flag = 0
                break
        if flag:
            ans.append(ex)
    return ans
