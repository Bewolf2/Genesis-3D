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
#ifndef __resource_H__
#define __resource_H__

#include "core/refcounted.h"
#include "util/stringatom.h"
#include "io/stream.h"
#include "core/weakptr.h"
#include "resource/resourcebase.h"
#include "resourcepriority.h"

namespace Resources
{
	typedef Util::StringAtom ResourceId; 


	struct ReferenceResource
	{
		Resources::ResourceId id;
		Resources::ResourceType type;
		inline ReferenceResource()
			:type(RR_Unknown)
		{

		}

		inline ReferenceResource(const Resources::ResourceId& id, Resources::ResourceType type)
		{
			this->id = id;
			this->type = type;
		}
	};

	class Resource;
	class ResourceNotifier;
	class ResourceServer;

	//-------------------------------��Դ��ȡ����д��������-----------------------------------------
	class ResourceLoaderSaver
	{
	public:
		void SetStream(const GPtr<IO::Stream>& pStream )
		{
			mStream = pStream;
		}
		const GPtr<IO::Stream>& GetStream(void) const
		{
			return mStream;
		}
	protected:
		ResourceLoaderSaver() { };
		GPtr<IO::Stream> mStream;	     //	Ҫ��ȡ/д�����
	};
	// ��Stream�ж�ȡ���л���Դ
	class ResourceLoader: public Core::RefCounted, public ResourceLoaderSaver
	{
		__DeclareClass(ResourceLoader);
	public:
		ResourceLoader(){ };
		virtual ~ResourceLoader(){ };
		virtual bool LoadResource(Resource* res ){ return false; };
	};
	// ����Դ���л���Stream��
	class ResourceSaver:  public Core::RefCounted, public ResourceLoaderSaver
	{
		__DeclareClass(ResourceSaver);
	public:
		ResourceSaver(){ };
		virtual ~ResourceSaver() { };
		virtual bool SaveResource( Resource* res ) { return false; };
	};

	//------------------------------��Դ����------------------------------------------
	class Resource : public Core::RefCounted
	{
		__DeclareClass(Resource);
	public:
		enum State
		{
			UnLoaded,
			Loaded,
			Failed
		};

		/// constructor
		Resource();
		/// destructor
		virtual ~Resource();

		/**
		* GetState  �õ���Դ��״̬
		* @param: void  
		* @return: Resources::Resource::State  
		* @see: 
		* @remark:  
		*/
		State GetState(void) const;

		/**
		* SetManuLoad  �����Ƿ����ֶ�����
		* @param: bool bManu  
		* @return: void  
		* @see: 
		* @remark:  �ֶ����ص���Դ�����Զ�ж�ء� �����ֶ�����Resource::Unload���������ң�ж��֮����Ȼ�����ֶ�����
		*/
		void SetManuLoad(bool bManuLoad );

		/**
		* GetManuLoad  �ж��Ƿ����ֶ�����
		* @param: void  
		* @return: bool  
		* @see: 
		* @remark:  
		*/
		bool IsManuLoad(void) const;

		/**
		* IsAsynProcessing  ��Դ�Ƿ����첽������
		* @return: bool  
		* @see: 
		* @remark:  
		*/
		bool IsAsynProcessing() const;

		/**
		* SetResourceId  set the resource identifier
		* @param: const ResourceId & id  
		* @return: void  
		* @see: 
		* @remark:  !!!!!! nerver change resourceid after resource create!!!!!!!!!!
		*/
		void SetResourceId(const ResourceId& id);

		/**
		* GetResourceId  get the resource identifier
		* @return: const ResourceId&  
		* @see: 
		* @remark:  
		*/
		const ResourceId& GetResourceId() const;

		/**
		* AttachNotifier  ����һ��״̬�仯��֪ͨ�ص�
		* @param: const WeakPtr<ResourceNotifier> & notifier  
		* @return: void  
		* @see: 
		* @remark:  ResourceNotifier�����������ⲿ����
		*/
		void AttachNotifier(const WeakPtr<ResourceNotifier>& notifier );

		/**
		* DeattachNotifier  ɾ��һ��״̬�仯��֪ͨ�ص�
		* @param: const WeakPtr<ResourceNotifier> & notifier  
		* @return: void  
		* @see: 
		* @remark:  ResourceNotifier�����������ⲿ����
		*/
		void DeattachNotifier(const WeakPtr<ResourceNotifier>& notifier);

		/**
		* Load  ����/���¼���һ����Դ�� ���ݴ� ResourceLoader->Resource
		* @param: const GPtr<ResourceLoader> & loader  
		* @return: bool  ����/���¼�����ȫ�����߲������ݣ������ݱ仯��������true�����򣬷���false
		* @see: 
		* @remark:  �����μ��ع��̳ɹ�ʱ�����ResourceLoader::GetEndClipIndex��MaxResClipCount������Դ״̬ΪLoaded��������ԴΪUnloaded/Falied/LoadedParty->LoadedParty
		�����μ��ع���ʧ��ʱ������ΪFailed������Loader����ʧ�ܻ�ʹ���е���Դ����ȫ��ʧЧ��
		*/
		virtual bool Load( const GPtr<ResourceLoader>& loader );

		/**
		* Save  �洢��Դ�� ���ݴ�Resource->ResourceSaver
		* @param: const GPtr<ResourceSaver> & saver  
		* @return: bool  �Ƿ�д��ɹ���
		* @see: 
		* @remark:  ��д�뵽�ڴ��������ļ�����ȡ����ResouceSaver
		*/
		virtual bool Save( const GPtr<ResourceSaver>& saver );

		/**
		* UnLoad  ж�����м��ص���Դ���ݡ���Դ״̬���ΪUnLoad
		* @return: void  
		* @see: 
		* @remark:  
		*/
		virtual void UnLoad(void);

		/**
		* SwapLoad  ��һ����ʱ��Դ��ͨ�����ݽ��������ٵĻ�ȡ��Դ����
		* @param: const GPtr<Resource> & tempResData   tempResDataΪ��,UnLoaded����Falied״̬������Ҫ������������Դ��RTTI����ȣ�����ʧ��; 
		* @return: bool �Ƿ񽻻��ɹ�  
		* @see: ResourceServer ʹ�øú����ڵ�ǰ��Դ���߳��м��ص���ʱ��Դ֮����ٵĽ������ݡ��������ݿ���
		* @remark:  
		*/
		virtual bool SwapLoad(const GPtr<Resource>& tempResData );

		/**
		* CalculateRuntimeSize  ������Դ����ʱռ�õ����ݴ�С. ����Ӧ�����ú��������ʵ�ʵļ������
		* @param: void  
		* @return: SizeT  
		* @see: 
		* @remark:  this is not fast
		*/
		virtual SizeT CalculateRuntimeSize(void) const;

		/**
		* SetState  �޸�״̬����֪ͨNotifier
		* @param: State newState  
		* @return: void  
		* @see: 
		* @remark:  !!!!!!!!!!Ӧ��ͨ��Load,UnLoad,SwapLoad����ȥ�޸ġ���������
		*/
		void SetState( State newState);

		static ResourceId EmptyResID;
	protected:

		// �����첽������Դ�ı�־
		void AddAsynProcessingIndex(void);
		void DecAsynProcessingIndex(void);

		// ����Ӧ�����ú�����������������ݽ���
		virtual bool SwapLoadImpl( const GPtr<Resource>& tempRes );

		// �����������������������ж�ز���
		virtual void UnLoadImpl(void);

		// ����һ��resource�õ�һЩ������Ҫ�ĳ�ʼ���Ĳ�����resourceserver�����ڸ���ʱ��Դ����ʼֵ
		virtual void InitLoadParam( const GPtr<Resource>& res );
	protected:
		State mState;
		ResourceId mResourceID;
		IndexT mAsynProcessingIndex;
		bool mManuLoad;
		Util::Array< WeakPtr<ResourceNotifier> > mNotifierList;

		friend class ResourceServer;
	};
	//------------------------------��Դ״̬�仯���֪ͨ�ص�------------------------------------------
	class ResourceNotifier: public Core::RefCounted
	{
		__DeclareClass(ResourceNotifier);
	public:
		ResourceNotifier()
			:mAttachCount(0) {
		};

		virtual ~ResourceNotifier() { };
		// is notifier attach to a resource
		bool IsAttached(void) const{
			n_assert(mAttachCount >= 0 );
			return mAttachCount != 0;
		}

	protected:
		virtual void Notify(Resource* res, Resource::State preState) { };

		void Attach(Resource* res){
			++mAttachCount;
		}
		void Deattach(Resource* res){
			--mAttachCount;
		}
		IndexT mAttachCount;
		friend class Resource;
	};

	//------------------------------------------------------------------------
	inline
		Resource::State 
		Resource::GetState(void) const
	{
		return mState;
	}
	//------------------------------------------------------------------------
	inline 
		void
		Resource::SetResourceId(const ResourceId& id)
	{
		this->mResourceID = id;
	}
	//------------------------------------------------------------------------------
	inline 
		const ResourceId&
		Resource::GetResourceId() const
	{
		return this->mResourceID;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		Resource::IsAsynProcessing() const
	{
		return mAsynProcessingIndex > 0;
	}
	//------------------------------------------------------------------------
	inline
		void 
		Resource::AddAsynProcessingIndex(void)
	{
		++mAsynProcessingIndex;
	}
	//------------------------------------------------------------------------
	inline
		void 
		Resource::DecAsynProcessingIndex(void)
	{
		--mAsynProcessingIndex;
	}
	//------------------------------------------------------------------------
	inline
		void 
		Resource::SetManuLoad(bool bManuLoad )
	{
		mManuLoad = bManuLoad;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		Resource::IsManuLoad(void) const
	{
		return mManuLoad;
	}

}	//	namespace Resources



#endif // __resource_H__
