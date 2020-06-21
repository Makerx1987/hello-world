Info=imfinfo('IMG_2018.cr2');
TiffHandle=Tiff('IMG_2018.cr2','r');
CFA=double(read(TiffHandle));