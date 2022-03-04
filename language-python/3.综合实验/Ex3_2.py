# -*- coding: utf-8 -*-
'''
Ex3_2. 自定义一个模块，并调用模块中的函数。
(1) 首先, 定义一个函数fex (dirpwd)，用os模块的相关方法，返回一个列表，
    列表包括：dirpwd路径下所有文件不重复的扩展名，如果有2个".py"的扩展名，则返回一个".py"。
    提示：可用os.path.splitext()分离文件名和扩展名。
(2) 然后，将定义上述函数的代码保存在”exname.py”中，作为模块文件。
    另创建一个测试文件” Ex3_2.py”，编写相关代码：调用exname模块中的fex方法，
    返回某个路径下的所有文件的扩展名（要求不重复）。
'''
import exname

ls = input("Please input the path:")
print(exname.fex(ls))
