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
/** \file resourceserver.h
* \brief 

1��������Դ
2��������Դ�ĵ�������
1����Դֻ�������һ�Σ�UnLoaded״̬ʱ�������غ�Ľ���ǳɹ�(Loaded)����ʧ��(Failed)
2����ԴҪ�ٴμ��أ���Ҫ���ֶ�UnLoad��
3����Դ���صķ�ʽ
ͬ����  �ڵ����̴߳Ӵ洢�豸��ȡ�ڴ��������ڴ�������Ϊ��Դ����
�첽��  Step1 �����߳�֪ͨIO�̣߳���IO�߳��첽�Ӵ洢�豸��ȡ�ڴ���
Step2 �����߳�֪ͨ��Դ�̣߳�����Դ�߳��첽���ڴ�����������ʱ��Դ����
Step3 �����̴߳���ʱ��Դ�������ݽ�������������Դ����
4����Դ�洢��ʽ�� ͨ���̣߳����Ǻ͵����߳�ͬ��
Step1  �����߳�֪ͨ��Դ�̣߳��ȴ���Դ�̴߳���Դ�����ڴ���
Step2  �����߳�֪ͨIO�̣߳��ȴ�IO�߳̽��ڴ���д�����洢�豸
*/
#ifndef __resourceserver_H__
#define __resourceserver_H__
#include "core/refcounted.h"
#include "resource/resource.h"
#include "core/singleton.h"
#include "util/delegate.h"
#include "util/queue.h"
#include "util/list.h"
#include "resource/resourceinterface.h"

#include "io/iointerfaceprotocol.h"
#include "timing/timer.h"

namespace Resources
{
	// ������Դ�Ļص�����
	struct LoadedArg
	{	
		LoadedArg(): processOK(false) { };
		bool processOK;	//	�Ƿ���سɹ�
		GPtr<Resource> res;	//	���ص���Դ
	};

	// ĳ����Դ�ڶ�дʱ��ʹ�õı��������ע����. ����ϵͳ�����ͽ���ʱ����ɱ�������ĳ�ʼ�������������
	class ResCodecReg: public Core::RefCounted
	{
		__DeclareClass(ResCodecReg);
	public:
		virtual void Open(void) {  }
		virtual void Close(void) {  }
	};


	class ResourceServer: public Core::RefCounted
	{
		__DeclareClass(ResourceServer);
		__DeclareImageSingleton(ResourceServer);
	public:
		ResourceServer();
		virtual ~ResourceServer();

		/**
		* Open  ��ʼ��ResourceServer
		* @return: void  
		* @see: 
		* @remark:  
		*/
		void Open(void);

		/**
		* IsOpen  �Ƿ��Ѿ���ʼ��
		* @return: bool  
		* @see: 
		* @remark:  
		*/
		bool IsOpen(void) const;

		/**
		* Close  �رսӿڣ��ͷ����е���Դ
		* @return: void  
		* @see: 
		* @remark:  
		*/
		void Close(void);

		/**
		* RegisterResourceType  ע����Դ�Ķ�д������Ҫ��Open֮ǰ����
		* @param: const Core::Rtti * resType	��Դ���͵�Rtti��Ϣ
		* @param: const Util::FourCC & typeFilter  ��ʾ��Դ��filter����֧�ִӶ������ݸ�ʽ�ж�ȡ��Դ��ϵͳĬ����Դ��ʽ��filter��'CYWJ'
		* @param: const Core::Rtti * loaderType  ��Դ���ͺ�filter ��Ӧ�Ķ�ȡ��
		* @param: const Core::Rtti * saverType  ��Դ���ͺ�filter  ��Ӧ��д����
		* @param: GPtr<ResCodecReg>& codecReg  Loader��Saver����ʹ�õ������ı����������Щ�������������Ҫ��ʼ����������ResourceServer Open��Closeʱ��������ö�Ӧ����
		* @return: void  
		* @see: 
		* @remark:  
		*/
		void RegisterResourceType( const Core::Rtti* resType,
			const Util::FourCC& typeFilter,
			const Core::Rtti* loaderType,
			const Core::Rtti* saverType,
			const GPtr<ResCodecReg>& codecReg = GPtr<ResCodecReg>() );

		/**
		* RegisterDefaultResouceTypes  ע��ϵͳ��Ĭ�ϵ���Դ���͡�filter�Ͷ�д���ȡ���Ҫ��Open֮ǰ����
		* @return: void  
		* @see: 
		* @remark:  Ĭ��ע��MeshRes��ImageRes��SkeletonRes��AnimationRes
		*/
		void RegisterDefaultResouceTypes();

		/**
		* CreateOrGetResource  ����һ����Դ���ߵõ�һ���Ѿ����ڵ���Դ��
		* @param: const ResourceId & resID  ��ԴID
		* @param: const Core::Rtti * ResType   ��Դ����
		* @return: GPtr<Resource>  ������Դָ��. ����ʧ��,���ؿ�ָ�룬
		* @see: 
		* @remark:  
		*/
		GPtr<Resource> CreateOrGetResource( const ResourceId& resID, const Core::Rtti* ResType );

		/**
		* HasResource  �ж�resIDָ�����Դ�Ƿ����
		* @param: const ResourceId & resID  
		* @return: bool  
		* @see: 
		* @remark:  
		*/
		bool HasResource(const ResourceId& resID);

		/**
		* GetResource  ������ԴID��ȡһ���Ѿ����ڵ���Դ
		* @param: const ResourceId & resID  
		* @return: GPtr<Resource>  ��Դ�����ڣ����ؿ�ָ��
		* @see: 
		* @remark:  
		*/
		GPtr<Resource> GetResource( const ResourceId& resID );

		/**
		* LoadResource  ͬ��/�첽 ����/���¼�����Դ����  
		* @param: const GPtr<Resource> & res  Ҫ���ص���Դָ��
		* @param: bool bAsyn  �Ƿ����첽����
		* @param: const Util::FourCC & typeFilter  ��Դ��filter��Ĭ����'CYWJ'  
		* @param: const Core::Rtti * manuLoaderType  �ֶ����õ���Դ��ȡ�����͡�
		1��Ϊ��ʱ��ʹ��typeFilterע��ġ�����Ҳ������������Դʧ�ܣ����ؿ�ָ��; 
		2����Ϊ��ʱ��ʹ���û��Զ���Ķ�ȡ�� 
		* @return: bool                              ͬ�����أ�bool ��ʾ�Ƿ���سɹ���
		�첽���أ�bool ��ʾ�ɹ����뵽���ض��У�false��ʾ�Ѿ��ڼ��ض�����
		* @see: 
		* @remark:  ��Դֻ�ܼ���һ��,���۳ɹ�����ʧ�ܡ���Ҫ��μ��أ���ж�ء�Ȼ���ټ���
		*/
		bool LoadResource( const GPtr<Resource>& res,
			bool bAsyn = true,
			const Util::FourCC& typeFilter = 'CYWJ',
			const Core::Rtti* manuLoaderType = NULL );

		/**
		* SaveResource  ͬ���洢һ����Դ
		* @param: const GPtr<Resource> & res  Ҫ�洢����Դָ��
		* @param: const IO::URI & uri  ��Դ�Ĵ洢·����Ϊ��ʱ��ʹ��res��ID��ǵ���Դ·��
		* @param: const Util::FourCC & typeFilter  �洢��filter��Ĭ����'CYWJ'		                                              
		* @param: const Core::Rtti * manuSaverType  �ֶ����õ���Դд��������
		1��Ϊ��ʱ��ʹ��typeFilterע��ġ�����Ҳ�������洢ʧ��  
		2������ʹ���û������д����
		* @return: bool  ���ش洢�Ƿ�ɹ�
		* @see: 
		* @remark:  
		*/
		bool SaveResource( const GPtr<Resource>& res,
			const IO::URI& uri = IO::URI(), 
			const Util::FourCC& typeFilter = 'CYWJ',
			const Core::Rtti* manuSaverType = NULL );
		/**
		* Flush  ˢ����Դ���ݡ����̼߳��ص���Դ���ݽ��������̡߳��ú������ᷢ����Դ���صĻص�֪ͨ
		* @param: void  
		* @return: void  
		* @see: 
		* @remark:  �ú���Ӧ��ÿ֡���á�
		*/
		void Flush(void);


		/**
		* UnLoadUnreferencedResources  
		* @param: void  
		* @return: void  
		* @see: 
		* @remark:  this method is not fast
		*/
		void UnLoadUnreferencedResources(void);

		/**
		* DicardUnreferencedResources  ɾ��δʹ�õ���Դ
		* @param: void  
		* @return: void  
		* @see: 
		* @remark:  this method is slow
		*/
		void DicardUnreferencedResources(void);

	protected:
		IO::URI _ConstructURI( const IO::URI& defaultUri, 
			const ResourceId& resID );

		const Core::Rtti* _ConstructLoaderOrSaverType( const Core::Rtti* defaultType, 
			const Core::Rtti* resType,
			const Util::FourCC& typeFilter,
			bool bloader );

		//	ͬ��������Դ
		bool _SynLoad(const GPtr<Resource>& res, const ResourceId& uri, const GPtr<ResourceLoader>& resLoader);	

		//	�첽������Դ
		bool _AsynPrepare(const GPtr<Resource>& res, const ResourceId& uri, const GPtr<ResourceLoader>& resLoader);	

		void _FlushReadList(const Timing::Timer& t ,Timing::Tick max_tick);
		void _FlushPrepareList(const Timing::Timer& t, Timing::Tick max_tick);

	protected:
		// ��Դ�Ķ�ȡ����д������ע�� ���ݽṹ
		struct LoadSaveRegistry 
		{
			const Core::Rtti* Loader;
			const Core::Rtti* Saver;
			GPtr<ResCodecReg> codecReg;
		};
		typedef Util::Dictionary<Util::FourCC, LoadSaveRegistry> ResFilterRegistry;
		typedef Util::Dictionary<const Core::Rtti*, ResFilterRegistry> ResRegistry;
		typedef Util::Dictionary< ResourceId, GPtr<Resource> > ResMap;

		bool mIsOpen;
		ResRegistry mResReg;	//	ע�����Դ��д��
		ResMap mResources;	//	��Դ�б�

		// �����첽���ص����ݽṹ�ͱ���

		struct PrepareStub	//	IO��������ı��ش��
		{
			GPtr<Resource> res;	//	���ص���Դ
			GPtr<ResourceLoader> loader;
			GPtr<IO::ReadStream> msg_stream;	//	��IO�߳�ͨ�ŵ���Ϣ
		};

		struct ReadStub		// ���л���������ı��ش��
		{
			GPtr<Resource> res;	//	���ص���Դ
			GPtr<ResMsg> msg_loader;	//	�����л��߳�ͨ�ŵ���Ϣ
		};

		typedef Util::List<PrepareStub> PrepareStubbList;
		typedef Util::List<ReadStub>    ReadStubList;

		GPtr<ResourceInterface> mThreadInterface;//	���л��̡߳����ڴ���з����л���Դ
		PrepareStubbList mAsynPrepareQueue;	//	��¼����IO�߳��У����ⲿ�豸����IO����Դ
		ReadStubList mAsynReadQueue;	//	��¼�������л��߳��У����з����л�����Դ
	};
	//------------------------------------------------------------------------
	inline
		bool
		ResourceServer::IsOpen() const
	{
		return mIsOpen;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		ResourceServer::HasResource(const ResourceId& resID)
	{
		return mResources.FindIndex( resID ) != InvalidIndex;
	}
	//------------------------------------------------------------------------
	inline
		GPtr<Resource> 
		ResourceServer::GetResource( const ResourceId& resID )
	{
		IndexT findIndex = mResources.FindIndex( resID );
		if ( InvalidIndex != findIndex )
		{
			return mResources.ValueAtIndex(findIndex);
		}
		else
		{
			return GPtr<Resource>(0); 
		}
	}
}












#endif // __resourceserver_H__
