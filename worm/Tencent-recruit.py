# 导入request和etree库
import requests
from lxml import etree
# 定义常量
domaiN='https://hr.tencent.com/'
headerS={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) '
                       'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36'}
pagE = "https://hr.tencent.com/position.php?keywords=&tid=0&lid=2175&start={}#a"


# 定义主函数
def spider():
    # datapool是将来数据汇总
    datapool = []
    for x in range(0,50,10):   # 通过分析发现网址变化规律
        page = pagE.format(x)   # format将取代%语句
        ht = requests.get(page, headers=headerS).text   # 偷懒(￣▽￣)／返回的response对象使用自动化的etree.text函数
        xh = etree.HTML(ht)   # 转化为xpath可用的编码形式
        detailurlist = xh.xpath('//tr[@class="even" or @class="odd"]//a/@href')   # 通过分析用xpath爬取详情页
        for durl in detailurlist:
            durl = domaiN + durl   # 加上大域名
            print(durl)
            datapool.append(durlparser(durl))
    savetxt(datapool)
    return ' finish'


   # 详情页爬取函数
def durlparser(durl):
    ht = requests.get(durl, headers=headerS).text
    xh = etree.HTML(ht)
    detaildict={}                    # 创建字典,爬取数据
    detaildict['职位名称'] = xh.xpath("//tr[@class='h']/td/text()")[0]   # 返回的是list
    detaildict['工作地点'] = xh.xpath("//tr[@class='c bottomline']//td/text()")[0]
    detaildict['职位类别'] = xh.xpath("//tr[@class='c bottomline']//td/text()")[1]
    detaildict['招聘人数'] = xh.xpath("//tr[@class='c bottomline']//td/text()")[2]
    detaildict['工作职责'] = xh.xpath("//tr[@class='c'][1]//ul/li/text()")
    detaildict['工作要求'] = xh.xpath("//tr[@class='c'][2]//ul/li/text()")
    return detaildict


def savetxt(datapool):   # 保存为txt
    with open('腾讯招聘.txt', 'w', encoding='utf-8') as fp:
        fp.write(str(datapool))   # str强制转化为文本
        fp.close()


if __name__ == '__main__':   # 在测试时运行py
    try:   # 这里try语句纯属画蛇添足
        spider()
    except:
        print('unexpected error occurs')
