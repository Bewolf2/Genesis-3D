/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __FILE_FORMAT_H__
#define __FILE_FORMAT_H__
#include "packageTool/PackDef.h"
namespace Pack
{
	struct FileBlock 
	{
		enum flagType
		{
			FT_Use = 0x01,
		};
		HashCode hashName;
		//u32 packIndex;	//�ļ�������
		u32 beginBlock;		//�ļ�����ʼ���ݿ�
		u32 blockCount;		//�ļ���ռ�õ����ݿ��С
		u32 fileSize;		//�ļ���ʵ�ʴ�С
		u32 flag;			//1�������������ʵ�����ݣ� 0�����������ֻ�Ƿ����˴�С����ʵ������
		u32 checkCode;		//У����
		u32 NoUse;
	};
	const u32 PACKAGE_LS_SIGN = 'GEPL';//genesis package list sign
	const u32 CURRENT_LS_VERSION = 1;

	const u32 PACKAGE_DATA_SIGN = 'GEPD';//genesis package data sign
	const u32 CURRENT_DATA_VERSION = 1;

	struct PackageListHeader//ͷ��СΪ32 * 4 �ֽڣ��������Ը������Ĵ�С
	{
		u32 sign;
		u32 version;		
		u32 headSize;
		u32 fileBlocksBegin;
		u32 fileBlocksCount;
		u32 fileNamesBegin;
		u32 NoUse[26];
	};

	struct PackageDataHeader//ͷ��СΪ32 * 4 �ֽڣ��������Ը������Ĵ�С
	{
		u32 sign;
		u32 version;
		u32 headSize;
		u32 diskBlockSize;
		u32 diskBlockCount;
		u32 filesBegin;
		u32 NoUse[26];
	};

}

#endif //__FILE_FORMAT_H__