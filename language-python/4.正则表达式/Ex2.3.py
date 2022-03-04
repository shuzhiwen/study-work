# -*- coding: utf-8 -*-
'''
2.3 学习参考源代码“pics_urllib.py”和“pics_requests_bs4.py”，
    爬取网址：http://www.ivsky.com/tupian/chengshilvyou/  
    第9页至15页中有关”城市旅游”主题相关的图片，并按以下两种方式完成爬取任务, 
    将图片重新命名编号，分别保存到本地磁盘”E:/image1/”和“E:/image2”中。
(1) 仅利用urllib模块完成图片爬取任务，可参考“pics_urllib.py”。
(2) 结合第三方库Beautiful Soup和requests完成图片爬取任务，可参考“pics_requests_bs4.py”
'''

# picture_crawler.py
import urllib.request  # 主要用于打开和阅读url
import os
import re
import urllib.error  # 用于错误处理

import requests
import urllib.request
from bs4 import BeautifulSoup
from os.path import join

dirpath = "E:/"


def target1(url, dirname):
    for i in range(9, 16):
        count = 1
        m = urllib.request.urlopen(url+'index_'+str(i)+'.html').read()
        new_path = os.path.join(dirpath, dirname)
        if not os.path.isdir(new_path):
            os.makedirs(new_path)  # 创建目录保存每个网页上的图片
        page_data = m.decode()
        page_image = re.compile('<img src=\"(.+?)\"')  # 匹配图片的pattern
        for image in page_image.findall(page_data):  # 用正则表达式匹配所有的图片
            pattern = re.compile(r'http://.*.jpg$')  # 匹配jpg格式的文件
            if pattern.match(image):  # 如果匹配，则获取图片信息，若不匹配，进行下一个页面的匹配
                try:
                    image_data = urllib.request.urlopen(image).read()  # 获取图片信息
                    image_path = os.path.join(dirpath, dirname,
                                              'page'+str(i)+'_'+str(count)+".jpg")  # 给图片命名
                    count += 1
                    with open(image_path, "wb") as image_file:
                        image_file.write(image_data)  # 将图片写入文件
                except urllib.error.URLError as e:
                    print("Download failed")


def target2(url, dirname):
    headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.104 Safari/537.36 Core/1.53.3427.400 QQBrowser/9.6.12513.400',
               'Referer': 'http://www.ivsky.com/tupian/qita/index_11.html'}  # 伪装成浏览器
    html = requests.get(url, headers=headers)
    soup = BeautifulSoup(html.text, 'html.parser')
    for i in range(9, 16):
        link = url+'/index_'+str(i)+'.html'
        headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.104 Safari/537.36 Core/1.53.3427.400 QQBrowser/9.6.12513.400',
                   'Referer': 'http://www.ivsky.com/tupian/qita/index_5.html'}
        html = requests.get(link, headers=headers)
        mess = BeautifulSoup(html.text, 'html.parser')
        newpath = dirpath+dirname
        if not os.path.isdir(newpath):
            os.makedirs(newpath)  # 创建目录保存每个网页上的图片
        for page in mess.find_all('ul', class_='ali'):
            x = 1
            for img in page.find_all('img'):
                picf = join(newpath, "page%d_%d.jpg" % (i, x))
                urllib.request.urlretrieve(img['src'], picf)
                x += 1


if __name__ == "__main__":
    url = "http://www.ivsky.com/tupian/chengshilvyou/"

    print("利用urllib模块抓取图片")
    target1(url, "image1")

    print("利用Beautiful Soup和requests抓取图片")
    target2(url, "image2")
