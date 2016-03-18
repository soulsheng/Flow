#ifndef BMPHANDLER
#define BMPHANDLER

//#include <Windows.h>
//#include "commonDefinition.h"

typedef unsigned char byte;

#pragma pack(2)

/*WORD:two-byte type*/
typedef unsigned short WORD;
/*DWORD:four-byte type*/
typedef unsigned long DWORD;

/*file head of bitmap*/
typedef struct  BMPFILEHEADER
{
	WORD bType;             /*  file identifier          */
	DWORD bSize;            /*  file size                */
	WORD bReserved1;        /*  retention value,must 0   */       
	WORD bReserved2;        /*  retention value,must 0   */
	DWORD bOffset;          /*  The offset from the last file header to the start of image data bits. */
} ;

/*bitmap header*/
struct BMPINF
{
	DWORD bInfoSize;       /*  size of the message header */
	DWORD bWidth;          /*  width of the image         */
	DWORD bHeight;         /*  height of the image        */
	WORD bPlanes;          /*  number of bit-plane image  */
	WORD bBitCount;        /*  number of bits per pixel   */
	DWORD bCompression;    /*  compression Type           */
	DWORD bmpImageSize;    /*  image size, in bytes       */
	DWORD bXPelsPerMeter;  /*  horizontal resolution      */
	DWORD bYPelsPerMeter;  /*  vertical resolution        */
	DWORD bClrUsed;        /*  number of colors used      */
	DWORD bClrImportant;   /*  significant number of colors*/
} ;

typedef struct tagRGBQUAD { 
	byte rgbBlue;    // ��ɫ������(ֵ��ΧΪ0-255) 
	byte rgbGreen;   // ��ɫ������(ֵ��ΧΪ0-255) 
	byte rgbRed;     // ��ɫ������(ֵ��ΧΪ0-255) 
	byte rgbReserved;// ����������Ϊ0 
	} RGBQUAD;

#pragma pack()

	// ��ͼƬ�ļ�
	void readImage(char* filename, byte *imageGray);

	// дͼƬ�ļ�
	void saveImage( char* filename, byte *imageGray, int height, int width );

	//�ҶȻ�
	void rgbGray( byte *rgb_gray, byte *R_P, byte *G_P, byte *B_P,int height,int width );


#endif