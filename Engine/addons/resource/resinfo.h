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
#ifndef __resinfo_H__
#define __resinfo_H__

#include "resource.h"
#include "graphicsystem/Material/materialinstance.h"
#include "graphicsystem/GraphicObjectManager.h"

namespace Sprite
{
	class SpritePackage;
}

namespace Resources
{
	const int MAX_RES_LOAD_PRIORITY = 65535;
	const int DEFAULT_RES_LOAD_PRIORITY = 65535;
	//--------------------------------------------------------------------------------
	/** 
	��Դ�����ֱ�����̬�� 
	1�����ⲿ�洢�豸�ϵı�����̬��������һ���ļ����ļ���һ���֣��������ݿ��е�һ����¼�����Ϊ�ļ���̬
	2�����ڴ��е���Դ���ݵı�����̬����Resources::Resource�������ࡣ���Ϊ������̬
	3����ĳ������ģ��������Ļ����еı�����̬��������Ⱦϵͳ�е�һ������� ���Ϊ��������̬
	4��һ����˵��һ���ļ���̬��Ӧһ��������̬
	5����ĳЩ��Դ���ͣ�������̬����������̬��һ���ġ�Ҳ�Ͳ�������������̬
	6����ĳЩ��Դ���ͣ�������̬���ܶ�Ӧ������������̬������MeshRes��������Ⱦ��Ҳ����������

	baseResInfo��Ҫ������������̬������Ӧ����Դ��̬������������̬��ͬʱ��Ӧ�ô��ڲ�ͬ��baseResInfo
	���ֶ�����̬��״̬�仯
	1�������ļ���̬�ɹ����ص�������̬ʱ������Դ��Ϣ���Ѿ�������(Loaded)
	2�����Ӷ�����̬�ɹ����뵽��������̬�󣬸���Դ��Ϣ���Ѿ�������(Compiled)
	3������Դ��Ϣ�Ѿ����ز��ҳɹ������ ����Դ��Ϣ�ǿ��õ�(CanUsable)
	4�������ܵȽǶȿ��ǣ���ͬ����Դ����������״̬�жϺ�����ʵ��Ϊ�麯�����������޸ġ������Щ״̬��ֻ��Ϊ�ڲ�ʹ�ã�����Ϊ�ⲿ�ж���Ч�Ե�����

	*/

	class ResInfoContainer;

	class baseResInfo : public Core::RefCounted
	{
		__DeclareClass(baseResInfo);
	public:
		baseResInfo() : 
		  priority(DEFAULT_RES_LOAD_PRIORITY),
			  isAsynLoading(false),
			  container(0),
			  defaultResUsed(false),
			  needReCompile(false)
		  {};
		  virtual ~baseResInfo()
		  {};

		  // ��ԴID
		  const Resources::ResourceId& GetResID() const {
			  return resID;
		  }
		  void SetResID(const Resources::ResourceId& id){
			  resID = id;
		  }

		  // ��Դ���ص����ȼ��� >0 ��ʾ�ӳټ��ء�����Խ�󣬼������ȼ�Խ��
		  Priority GetPriority(void) const { 
			  return priority;
		  }
		  void SetPriority(Priority p ){
			  priority = p;
		  }

		  // ��Դ���ݶ���
		  const GPtr<Resources::Resource>& GetRes() const{
			  return resData;
		  }

		  void SetRes(const GPtr<Resources::Resource>& res){
			  resData = res;
		  }

		  void SetContainer(ResInfoContainer* m)
		  {
			  container = m;
		  }
		  ResInfoContainer* GetContainer()
		  {
			  return container;
		  }

		  // ��������̬�Ƿ���ڡ�Ĭ������£�������̬����������̬һ�¡������������Ҫ��д
		  virtual bool IsCompiled() const
		  {
			  return IsLoaded()&&!needReCompile;
		  }

		  // �ڲ�ʹ�õĽӿ�

		  // ��Դ��Ϣ�Ƿ�׼����ϣ����Ա�ҵ���߼�ʹ���ˡ�
		  // ��ͬ��������Դ��״̬�жϲ�ͬ��������Ӧ�ø�����Ҫ��д�ĺ���
		  virtual bool CanUsable() const
		  {
			  return IsLoaded() && IsCompiled();
		  }

		  // ������̬�Ƿ���ڲ�����
		  virtual bool IsLoaded() const
		  {

			  return resData && resData->GetState() == Resources::Resource::Loaded;

		  }



		  // ������������̬
		  bool Compile();

		  // ��Ҫ�����������ظú����������������̬�ı���͸�ֵ
		  virtual void OnCompile(){ }

		  // ��������Ϊ��ʼ״̬
		  virtual void Discard(){
			  resData = 0;
			  resID.Clear();
			  isAsynLoading = false;
			  priority = DEFAULT_RES_LOAD_PRIORITY;
		  }

		  // ����Ĭ�ϵ���Դ����
		  virtual void AssignDefaultResData(const GPtr<baseResInfo>& defaultRes)
		  {
			  if ( defaultRes )
			  {
				  ResourceId tempResID;
				  Priority   tempPriority;
				  bool tempAsynLoading;

				  tempResID = resID;
				  tempPriority = priority;
				  tempAsynLoading = isAsynLoading;

				  Discard();
				  //ResetHandle();


				  resID = tempResID;
				  priority = tempPriority;
				  isAsynLoading = tempAsynLoading;
				  resData = defaultRes->resData;
				  defaultResUsed = true;
			  }
		  }

		  // ��Ҫ��Ϊ��֧��fbx����������������
		  // ���������������ע�⣬���ܻ����bug
		  // ���copy��Ҫres����Ϣ�������ģ�����copy������Ҫɾ��֮ǰ��res������ͻ������
		  // 
		  virtual void CopyFrom(const GPtr<baseResInfo>& res)
		  {
			  if ( res )
			  {
				  ResourceId tempResID;
				  Priority   tempPriority;
				  bool tempAsynLoading;

				  tempResID = resID;
				  tempPriority = priority;
				  tempAsynLoading = isAsynLoading;

				  Discard();

				  resID = tempResID;
				  priority = tempPriority;
				  isAsynLoading = tempAsynLoading;
				  resData = res->resData;

				  AssignDefaultResCompile( res );

				  defaultResUsed = false;
			  }
		  }

		  // ����Ĭ�ϵ���������̬
		  virtual void AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes)
		  {
			  return;
		  }

		  // �Ƿ������첽����
		  bool IsAsynLoading() const
		  {
			  return isAsynLoading;
		  }
		  void SetAsynLoading(bool b)
		  {
			  isAsynLoading = b;
		  }

		  bool IsDefaultResUsed()
		  {
			  return defaultResUsed;
		  }

		  void SetDefaultResUsed(bool isUsed)
		  {
			  defaultResUsed = isUsed;
		  }

		  void SetNeedReCompile(bool isNeedReCompile)
		  {
			  needReCompile = isNeedReCompile;
		  }

		  bool IsNeedReCompile()
		  {
			  return needReCompile;
		  }

		  virtual void ResetHandle()
		  {

		  }

	protected:
		friend class ResourceManager;
		Priority priority;
		Resources::ResourceId resID;
		GPtr<Resources::Resource> resData;
		bool isAsynLoading;
		ResInfoContainer* container;
		bool defaultResUsed;
		bool needReCompile;
	};
	//------------------------------------------------------------------------

	class TextureResInfo : public baseResInfo
	{
		__DeclareSubClass(TextureResInfo,baseResInfo);
	public:
		TextureResInfo()
		{
			texHandle = RenderBase::TextureHandle();
		}
		virtual ~TextureResInfo()
		{
		}
		void SetData(const Resources::ResourceId& tex_id, const RenderBase::TextureHandle& handle)
		{
			resID = tex_id;
			texHandle = handle;
		}
		void SetHandle(const RenderBase::TextureHandle& handle)
		{
			texHandle = handle;
		}
		const RenderBase::TextureHandle& GetHandle() const
		{
			return texHandle;
		}

		// ��������̬�Ƿ����
		virtual bool IsCompiled() const
		{
#ifdef __GENESIS_EDITOR__
			return GetHandle().IsValid() && Super::IsCompiled();
#else
			return GetHandle().IsValid();
#endif
		}

		virtual void ResetHandle() 
		{
			texHandle = RenderBase::TextureHandle();
		}

		virtual void Discard();

		// ������������̬
		virtual void OnCompile();

		virtual void AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes);

#ifndef __GENESIS_EDITOR__	
		virtual bool CanUsable() const
		{
			return IsCompiled();
		}
#endif

	protected:
		RenderBase::TextureHandle texHandle;
	};

	//--------------------------------------------------------------------------------
	class PrimitiveResInfo : public baseResInfo
	{
		__DeclareSubClass(PrimitiveResInfo,baseResInfo);
	public:
		PrimitiveResInfo()
		{
			primHandle = RenderBase::PrimitiveHandle();
		}
		virtual ~PrimitiveResInfo()
		{

		}
		const RenderBase::PrimitiveHandle& GetHandle() const
		{
			return primHandle;
		}
		void SetHandle( const RenderBase::PrimitiveHandle& h)
		{
			primHandle = h;
		}

		// ��������̬�Ƿ����
		virtual bool IsCompiled() const
		{
#ifdef __GENESIS_EDITOR__
			return GetHandle().IsValid() && Super::IsCompiled();
#else
			return GetHandle().IsValid();
#endif
		}

		virtual void ResetHandle()
		{
			primHandle = RenderBase::PrimitiveHandle();
		}

		virtual void Discard();

		// ������������̬
		virtual void OnCompile();

		virtual void AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes);

#ifndef __GENESIS_EDITOR__
		virtual bool CanUsable() const
		{
			return IsCompiled();
		}
#endif

	protected:
		RenderBase::PrimitiveHandle primHandle;
	};
	//------------------------------------------------------------------------

	class MaterialResInfo : public baseResInfo
	{
		__DeclareSubClass(MaterialResInfo,baseResInfo);
	public:
		MaterialResInfo()
		{
			matIns = NULL;
			mbSave = true;
			mbImport = false;
		}
		virtual ~MaterialResInfo()
		{

		}

		const Resources::ResourceId& GetMatID() const
		{
			return GetResID();
		}

		void  SetMatID(const Resources::ResourceId& matID)
		{
			SetResID(matID);
		}

		const GPtr<Graphic::MaterialInstance>& GetHandle() const
		{
			return matIns;
		}

		GPtr<Graphic::MaterialInstance>& GetHandle()
		{
			return matIns;
		}

		void SetHandle(const GPtr<Graphic::MaterialInstance>& m )
		{
			matIns = m;
		}
		void SetSave(const bool bFlag )
		{
			mbSave = bFlag;
		}
		bool GetSave()
		{
			return mbSave;
		}
		void SetImport(const bool bImport)
		{
			mbImport = bImport;
		}
		bool GetImport()
		{
			return mbImport;
		}
		virtual void AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes);

		virtual void ResetHandle()
		{
			matIns = NULL;
		}
		virtual void CopyFrom(const GPtr<baseResInfo>& res)
		{			
			baseResInfo::CopyFrom(res);
			GPtr<MaterialResInfo> matInfo = res.downcast<MaterialResInfo>();
			mbSave = matInfo->mbSave;
			mbImport = matInfo->mbImport;
		}

	protected:

		// ��������̬�Ƿ����
		virtual bool IsCompiled() const
		{
			return GetHandle().isvalid()&&Super::IsCompiled();
		}
		// ������������̬
		virtual void OnCompile();

	protected:
		GPtr<Graphic::MaterialInstance> matIns;
		bool							mbSave;
		bool							mbImport;
		friend class ResourceManager;
	};

	class SpritePackageResInfo : public baseResInfo
	{
		__DeclareSubClass(SpritePackageResInfo,baseResInfo);
	public:
		GPtr<Sprite::SpritePackage> GetPackage() const;
	};

	//------------------------------------------------------------------------
	// �����Ǽ򵥵���Դ������Ҫ�����ض��Ķ���

	typedef baseResInfo TemplateResInfo;

	typedef baseResInfo AudioResInfo;

	typedef baseResInfo AudioResInfo;

	typedef baseResInfo RawResInfo;

	typedef baseResInfo AnimationResInfo;

	typedef baseResInfo SkeletonResInfo;

	typedef baseResInfo PhysXMaterialResInfo;

	//------------------------------------------------------------------------
}






#endif // __resinfo_H__
