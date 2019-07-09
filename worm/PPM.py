# 导入request和etree库
import requests
from lxml import etree
# 定义常量
page="https://ppmforums.com/index.php?f=110&ppage=100050&sort=lastpost&order=DESC"
headerS={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) '
                       'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36'}

def work():
    