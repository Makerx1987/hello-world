from urllib import request
neihan = request.urlopen('http://neihanshequ.com/bar/1/')
print(neihan.read())
request.urlretrieve('http://neihanshequ.com/bar/1/','neihan1.html')

















