#include "BmpLoader.h"
#include<stdio.h>
#include <iostream>

BmpLoader::BmpLoader(const char* fname)
{
    FILE *fl=0;
    fl=fopen(fname, "rb");
    if(!fl)
        std::cout<<"File not found"<<std::endl;
    fread(&bfh, sizeof(BITMAPFILEHEADER),1,fl);
    if(bfh.bfType != 0x4D42)
        std::cout<<"Not a valid bitmap"<<std::endl;
    fread(&bih, sizeof(BITMAPINFOHEADER),1,fl);
    if(bih.biSizeImage==0)
        bih.biSizeImage=bih.biHeight*bih.biWidth*3;
    datatexture = new unsigned char[bih.biSizeImage];
    fseek(fl, bfh.bfOffBits, SEEK_SET);
    fread(datatexture, 1, bih.biSizeImage, fl);
    unsigned char temp;
    for(int i=0; i<bih.biSizeImage; i+=3)
    {
        temp = datatexture[i];
        datatexture[i] = datatexture[i+2];
        datatexture[i+2] = temp;

    }

    iWidth = bih.biWidth;
    iHeight = bih.biHeight;
    fclose(fl);
}

BmpLoader::~BmpLoader()
{
    delete [] datatexture;
}
