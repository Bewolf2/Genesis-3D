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
#ifndef _GENESISLOADER_H_
#define _GENESISLOADER_H_
#include <windows.h>
#include <assert.h>
#include <string>
#include "appframework/gameapplication.h"

#include "GenesisLoaderData.h"

namespace Genesis
{


class GenesisLoader
{
public:
	//Public Interfaces
	static GenesisLoader* Instance()
	{
		if (m_pInst)
		{
			return m_pInst;
		}
		else
		{
			m_pInst = new GenesisLoader();
			assert(m_pInst);
			return m_pInst;
		}
		
	}

	static void Destroy()
	{
		if (m_pInst)
		{
			delete m_pInst;
			m_pInst = NULL;
		}
	}

	~GenesisLoader();
	
	//��ʼ��
	//1.��ȡ�����в��� ��������  2.
	bool Init(int argc, char *argv[]);
	void Run();
	bool End();
	bool IsLocalVersion(){return m_bLocalVersion;}
	
	
public:
	//Public Attributes
private:
	//private method
	//ctor
	GenesisLoader()
	{
		m_pInst = NULL;
		mh_PluginWnd = NULL;
		//m_bLocalRes = false;
		m_bLocalVersion = false;
		//m_pGameInst = NULL;
	}

	//Create Loader Render Window which is the children window of the plugin window
	HWND CreateLoaderWindow(HWND parentWnd,unsigned int nWidth,unsigned int nHeight);
	
private:
	//private attributes

	//single instnce
	static GenesisLoader* m_pInst;
	//plugin wnd
	HWND mh_PluginWnd;
	////�Ƿ�ֻʹ�ñ�����Դ
	//bool m_bLocalRes;
	//�Ƿ��Ǳ��ذ汾���У���������ҳ�汾
	bool m_bLocalVersion;

};




/************************************************************************/
/* ��ҳͨ�Žṹ                                                                     */
/************************************************************************/
struct IpcEvent
{
	IpcEvent(const std::string &e, const std::string &m) : ipc_event(e), ipc_msg(m) { }
	std::string ipc_event;
	std::string ipc_msg;
};


}

//---------------------------------------------------------------------------
//�ڲ�ͬ��Demo�еĳ�ʼ������������������ֻ�ṩ�����������ھ����Demo�и���ʵ��
//---------------------------------------------------------------------------
#define HANDLE_API(r,n,p) r n p;
#include "GenesisLoaderInterface.h"

#endif