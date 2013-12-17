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
#ifndef __ThreadRuntimeInfo_H__
#define __ThreadRuntimeInfo_H__

#include "core/refcounted.h"


namespace Threading
{
	// ����ÿһ���߳��а�������󵥼�ʵ������
	const SizeT MaxThreadInstanceNum = 256;

	class ThreadRunTimeInfo
	{
	public:
		ThreadRunTimeInfo(void);
		~ThreadRunTimeInfo(void);
		
		char* GetInstance( IndexT i );

		void SetInstance( IndexT i , char* pIns );

		bool HasInstance( IndexT i );

	public:
		// ��ǰ�߳��е���ʵ������
		char* mInstanceArray[MaxThreadInstanceNum];
		// �߳�����
		const char* mThreadName;
	public:

		/// *******��ֹ�ⲿ����*******     ����Ψһ��һ��ID���̶߳����ĵ�����
		static IndexT GetThreadInstanceID(void);

		/// �����̶߳���������ʱ����,ÿ���߳�ֻ�������һ�Ρ����̱߳����ڹ����̺߳ʹ�������֮ǰ���á������̱߳����ڸո������ʹ�������֮ǰ���á�
		static void SetupMyThreadRunTime( const char* threadName );

		/// �������߳�����ʱ����.���̱߳��������� 
		static void DestoryThreadRunTime( bool isMainThread = false );

		/// �õ���ǰ�̵߳�����ʱ
		static Threading::ThreadRunTimeInfo* GetMyThreadRuntime( void );

	private:
		static IndexT ThreadInstanceCounter;
		static IndexT mTlsSlot;	//	����Tls���洢�߳�����ʱ��Ϣ
	};

	//------------------------------------------------------------------------
	inline char* ThreadRunTimeInfo::GetInstance( IndexT i )
	{
		n_assert( i >=0 && i < MaxThreadInstanceNum );
		n_assert( mInstanceArray[i] );
		return mInstanceArray[i];
	}
	//------------------------------------------------------------------------
	inline void ThreadRunTimeInfo::SetInstance( IndexT i , char*  pIns )
	{
		n_assert( i >=0 && i < MaxThreadInstanceNum );
		mInstanceArray[i] = pIns;
	}
	//------------------------------------------------------------------------
	inline bool ThreadRunTimeInfo::HasInstance( IndexT i )
	{
		n_assert( i >=0 && i < MaxThreadInstanceNum );
		return mInstanceArray[i] != NULL;
	}

}







#endif // __ThreadRuntimeInfo_H__
