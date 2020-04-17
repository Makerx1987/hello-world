from urllib.request import urlretrieve

for i in range(1,9):
    url = "https://s3.ananas.chaoxing.com/doc/ff/47/4a/fe9030f564eb3433fe8981d7b53d1a7a/thumb/{}.png".format(i)
    filename = "pdf/{}.png".format(i)
    urlretrieve(url, filename)
    print(filename)
