
#include "bmpHandler.h"

#include <stdio.h>
#include <math.h>


void readImage( char* filename, byte *imageGray )
{
	FILE *fp=NULL;
	FILE *fp_b=NULL;
	FILE *fp_br=NULL;
	struct BMPFILEHEADER fileHeader;
	struct BMPINF infoHeader;
	long offset, bmpImageSize, width, height, bytesPerPixel, size, bitCount;
	int  i,j;
	long t;
	byte* B, *G, *R, *B_P, *G_P, *R_P;
	byte *Pixel;

	//char *bmpArray;
	//unsigned char **p;
	//WORD c;

	fp=fopen( filename,"rb");
	if(fp == NULL)
	{
		printf("Cann't open the file!\n");
		exit(0);
	}

	fseek(fp, 0, 0);
	fread(&fileHeader, sizeof(fileHeader), 1, fp);
	fread(&infoHeader, sizeof(infoHeader), 1, fp);

	//Calculates and outputs the offset bitmap data, image size, width and height of bytes per pixel
	size = fileHeader.bSize;
	offset = fileHeader.bOffset;
	bmpImageSize = infoHeader.bmpImageSize;
	width = infoHeader.bWidth;
	height = infoHeader.bHeight;
	bitCount = infoHeader.bBitCount;
	bytesPerPixel = infoHeader.bBitCount / 8;


	fseek(fp,offset,SEEK_SET);

	//Assign addresses
	Pixel =(byte *)malloc((size-offset)*sizeof(byte));

	i=0;

	B=(byte *)malloc(height*width*sizeof(float));
	G=(byte *)malloc(height*width*sizeof(float));
	R=(byte *)malloc(height*width*sizeof(float));

	B_P=(byte *)malloc(height*width*sizeof(float));
	G_P=(byte *)malloc(height*width*sizeof(float));
	R_P=(byte *)malloc(height*width*sizeof(float));


	while(1)
	{
		*Pixel=fgetc(fp);
		B[i]= *Pixel;
		*Pixel=fgetc(fp);
		G[i]= *Pixel;
		*Pixel=fgetc(fp);
		R[i]= *Pixel;

		i++;
		if(i==height*width)
		{
			break;
		}
	}

	t=0; 
	for(i=height-1;i>=0;i--)
	{
		for(j=0;j<width;j++)
		{
			B_P[i*width+j]=*(B+t*width+j);
			G_P[i*width+j]=*(G+t*width+j);
			R_P[i*width+j]=*(R+t*width+j);
		}
		t=t+1;
	}

	rgbGray( imageGray, R_P, G_P, B_P, height, width );

	free(Pixel); Pixel = NULL;
	free( B ); free( G ); free( R );
	free( B_P ); free( G_P ); free( R_P );

}

void saveImage( char* filename, byte *imageGray, int height, int width )
{
	struct BMPFILEHEADER fileHeader;
	struct BMPINF infoHeader;
	int i;
	RGBQUAD *ipRGB2 = (RGBQUAD *)malloc(256*sizeof(RGBQUAD));//调色板的大小为1024字节

	FILE* fp=fopen( filename,"wb");
	if(fp == NULL)
	{
		printf("Cann't open the file in save!\n");
		return;
	}

	for ( i = 0; i < 256; i++ )
		ipRGB2[i].rgbRed = ipRGB2[i].rgbGreen = ipRGB2[i].rgbBlue = i;

	{
		fileHeader.bType = 19778;// 0x4D42
		fileHeader.bOffset = sizeof(struct BMPFILEHEADER) + sizeof(struct BMPINF) + 256*sizeof(RGBQUAD);

		fileHeader.bReserved1 = fileHeader.bReserved2 = 0;

		fileHeader.bSize = width * height + fileHeader.bOffset;
	}

	{
		infoHeader.bPlanes		= 1;
		infoHeader.bBitCount	= 8;
		infoHeader.bXPelsPerMeter	= 11811;
		infoHeader.bYPelsPerMeter	= 11811;
		infoHeader.bInfoSize	= sizeof(struct BMPINF);

		infoHeader.bCompression = infoHeader.bClrUsed = infoHeader.bClrImportant = 0;

		infoHeader.bWidth	= width;
		infoHeader.bHeight	= height;
		infoHeader.bmpImageSize = width * height;
	}

	fseek(fp, 0, 0);
	fwrite(&fileHeader, sizeof(struct BMPFILEHEADER), 1, fp);
	fwrite(&infoHeader, sizeof(struct BMPINF), 1, fp);
	fwrite(ipRGB2, sizeof(RGBQUAD), 256, fp);
	fseek(fp,fileHeader.bOffset,SEEK_SET);

	fwrite( imageGray, width*height, 1, fp );

	fclose(fp);
}
//灰度化
void rgbGray( byte *rgb_gray, byte *R_P, byte *G_P, byte *B_P,int height,int width )
{
	int i,j;
	float gray;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			//Converting an RGB image into a grayscale image
			gray = 0.299f * R_P[i*width+j] + 0.587f * G_P[i*width+j] + 0.114f * B_P[i*width+j]; 
			rgb_gray[i*width+j] = (int)( gray + 0.5f );
		}
	}    
}

