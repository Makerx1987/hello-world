import requests
from lxml import etree
import re
from selenium import webdriver
import time


targeturl = 'http://music.163.com/m/at/5a746296671614a5283e3be5'


def picspider():
    response = requests.get(
        targeturl, headers={
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) '
                          'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36'})
    ht = response.text
    xh = etree.HTML(ht)
    rspxh = xh.xpath("//body/script//text()")[0]
    tryurl = re.findall(r'http://[^\s]+?jpg', rspxh)
    # savepic(tryurl)
    print(tryurl)


def mp3spider():
    driverchrome = webdriver.Chrome(
        executable_path='...\chromedriver_win32\chromedriver.exe')
    driverchrome.get('http://music.163.com/m/at/5a746296671614a5283e3be5')
    time.sleep(3)
    div_list = driverchrome.find_elements_by_xpath("//div[@class='m-song']")
    mp3url = []
    for p in div_list:
        p.click()
        div = driverchrome.find_element_by_xpath("//audio")
        url = div.get_attribute('src')
        mp3url.append(url)
    # savemp3(mp3url)
    print(mp3url)


def savepic(picurl):    # 保存
    for p in range(len(picurl)):
        picurl_data = requests.get(picurl[p]).content
        with open('{}.jpg'.format(p), 'wb') as fp:
            fp.write(picurl_data)  # str强制转化为文本
            fp.close()


def savemp3(mp3url):    # 保存
    for p in range(len(mp3url)):
        url_data = requests.get(mp3url[p]).content
        with open('{}.mp3'.format(p), 'wb') as fp:
            fp.write(url_data)
            fp.close()


if __name__ == '__main__':   # 在测试时运行py
    picspider()
    mp3spider()
