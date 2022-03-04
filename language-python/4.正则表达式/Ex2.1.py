# -*- coding: utf-8 -*-
'''
2.1 运用re.findall函数查找所有匹配。
(1) 设计一个正则表达式，提取出字符串中的全部单词(数字和标点符号都不是单词部分)。
    这个字符串为s="I like Python programming 123 because it is 456 simple and elegant."
(2) 提取下列文本每行中完整的年月日和时间字段：
    s="see 123, 1987-02-09 07:30:00, 1987-02-15 07:25:00"
(3) 使用正则表达式找出下列文本中全体合法的邮件地址：
    s="xiasd@163.com, sdlfkj@.com sdflkj@180.com solodfdsf@123.com, sdlfjxiaori@139.com saldkfj.com oisdfo@.sodf.com.com"
(4) 令s="see 123, 1987-02-09 07:30:00, 1986-02-15 07:25:00", 执行下面代码：
        fa1=re.findall("\d+-\d+-\d+",s)
        fa2=re.findall("(\d+)-\d+-\d+",s)
        fa3=re.findall("(\d+)-(\d+)-(\d+)",s)
        print(fa1)
        print(fa2)
        print(fa3)
    程序输出结果是什么？通过考察结果，请学习掌握findall在正则式有否分组情形下输出结果的不同格式。
'''

import re

s1 = "I like Python programming 123 because it is 456 simple and elegant."
s2 = "see 123, 1987-02-09 07:30:00, 1987-02-15 07:25:00"
s3 = "xiasd@163.com, sdlfkj@.com sdflkj@180.com solodfdsf@123.com, sdlfjxiaori@139.com saldkfj.com oisdfo@.sodf.com.com"
s4 = "see 123, 1987-02-09 07:30:00, 1986-02-15 07:25:00"

tar = re.compile('[A-Za-z]+')
print(tar.findall(s1))

tar = re.compile('\d+[-:]\d+[-:]\d+')
print(tar.findall(s2))

tar = re.findall('\w+@\w+\.com', s3)
print(tar)

fa1 = re.findall("\d+-\d+-\d+", s4)
fa2 = re.findall("(\d+)-\d+-\d+", s4)
fa3 = re.findall("(\d+)-(\d+)-(\d+)", s4)
print(fa1)
print(fa2)
print(fa3)
