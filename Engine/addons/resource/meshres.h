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
#ifndef __meshres_H__
#define __meshres_H__
#include "resource/resource.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "util/array.h"
#include "math/float2.h"
#include "math/float3.h"
#include "math/float4.h"
#include "math/color.h"
#include "math/bbox.h"

#include <deque>

namespace Resources
{

	struct SubMesh
	{
		SubMesh()
			: firstVertex(0) , numVertex(0), FirstIndex(0), numIndex(0)
		{
		}
		IndexT firstVertex;
		SizeT numVertex;
		IndexT FirstIndex;
		SizeT numIndex;
		Math::bbox box;
	};

	struct BoneInfo
	{
		BoneInfo()
		{
			boneIndex[0] = 0;   boneIndex[1] = 0; boneIndex[2] = 0; boneIndex[3] = 0;
			boneWeight[0] = 0.0; boneWeight[1] = 0.0; boneWeight[2] = 0.0; boneWeight[3] = 0.0;
		}
		ushort boneIndex[4];
		float boneWeight[4];
	};

	typedef Util::Array<Math::float2>  Vec2fArray;
	typedef Util::Array<Math::float3>  Vec3fArray;
	typedef Util::Array<Math::float4>  Vec4fArray;
	typedef Util::Array<ushort>        UShortArray;
	typedef Util::Array<uint>          UIntArray;
	typedef Util::Array<Math::Color32> ColorArray;
	typedef Util::Array<BoneInfo>      BoneInfoArray;
	typedef Util::Array<SubMesh>       SubMeshArray;
	typedef Util::Array< Util::Array<uchar> > AffectedBonesIndex;

	// ���嶥������� ���������Ԫ���������ߺ�Positon��Ԫ��������ȣ�����Ϊ��
	class VertexIndex
	{
	public:
		enum code
		{
			egPosition = 0,	
			egColor,
			egTexCoord,
			egNormal,
			egTangent,
			egBiNormal,
			egBoneInfo,
		};
	};

	template<class _TContainer, int _TIndex>
	class VertexData: public _TContainer
	{
	public:
		enum 
		{
			_index = _TIndex,
		};
		typedef _TContainer Container;
		typedef typename Container::value_type Elem;
	};

	typedef VertexData<Vec3fArray,  VertexIndex::egPosition>    PositionData;
	typedef VertexData<ColorArray,  VertexIndex::egColor>       ColorData;
	typedef VertexData<Vec2fArray,  VertexIndex::egTexCoord>    TexCoordData;
	typedef VertexData<Vec3fArray,  VertexIndex::egNormal>      NormalData;
	typedef VertexData<Vec4fArray,  VertexIndex::egTangent>     TangentData;
	typedef VertexData<Vec4fArray,  VertexIndex::egBiNormal>    BiNormalData;
	typedef VertexData<BoneInfoArray,  VertexIndex::egBoneInfo> BoneInfoData;

	typedef UShortArray Index16Container;
	typedef UIntArray   Index32Container;

	//���֧��16���������굥Ԫ [0,15]
	const SizeT MaxTexcoordUnitLimit = 15;

	class MeshRes: public Resource 
	{
		__DeclareSubClass(MeshRes,Resource);
		friend class MeshSpliter;
		friend class MeshReviseWorkspace;
	public:
		MeshRes();
		virtual ~MeshRes();

		/// �õ�����״̬
		RenderBase::PrimitiveTopology::Code GetTopologyType() const;

		/// ��������״̬
		void SetTopologyType( RenderBase::PrimitiveTopology::Code t );

		/// �õ���Χ�д�С
		const Math::bbox& GetBoundingBox() const;

		/// ���ð�Χ�д�С
		void SetBoundingBox( const Math::bbox& b );

		/// slow�� ��Ҫ�ڸ��¶�����Ϣ���ֶ����á� includeSubMeshΪtrueʱ�������¼��㵱ǰ������submesh�İ�Χ�д�С
		void RecalculateBounds( bool includeSubMesh = true );

		/// ���¼���indexָ���submesh��Χ�еĴ�С�� slow�� ��Ҫ�ڸ��¶�����Ϣ����submesh���������ݺ��ֶ�����
		void RecalculateSubMeshBounds( IndexT index );

		//// �õ���������������������λ�á���ɫ�����ߵȣ������Ч���������Ԫ�ص�����һ���Ͷ���������ͬ
		SizeT GetVertexCount(void) const;

		/**
		* GetMaxTexUnitIndex  �õ���ǰ��Ч��������������Ԫ����
		* @param: void  
		* @return: IndexT  -1��ʾ����Ч��Ԫ
		* @see: 
		* @remark:  ��0�������Ч��Ԫ��֮�����������Ԫ����һ������Ч��
		*/
		IndexT GetMaxTexUnitIndex(void) const;

		/**
		* GetVertexData  �õ��������������ָ��
		* @param: IndexT unit  �Զ�������ж����Ԫ������������������꣩������ָ����Ԫ������
		* @return: const typename T::Elem*  ��������Ч�����ض��������һ��Ԫ�ص�ָ�빩ֱ���޸ģ�ָ��ָ��������С���ڶ������������򣬷���NULL
		* @see: 
		* @remark:  use like: const PositionData::Elem* elem = pMesh->GetVertexData<PositionData>();   // PositionData::Elem* is Math::float3* 

		*/
		template< typename T>
		const typename T::Elem* GetVertexData(IndexT unit = 0 ) const;

		/**
		* GetVertexData  �õ��������������
		* @param: IndexT unit  �Զ�������ж����Ԫ������������������꣩������ָ����Ԫ������
		* @return: typename T::Elem*  ��������Ч�����ض��������һ��Ԫ�ص�ָ�룬ָ��ָ��������С���ڶ������������򣬷���NULL
		* @see: 
		* @remark: !!!!!!!!!!!!����ֱ���޸�ָ��ָ������ݣ��ⲿӦ�ñ�֤�������ݵ���Ч�ԣ���������ָ��Ķ��㲻��Խ��!!!!!!!!!!!!!!!!!
		use like: PositionData::Elem* elem = pMesh->GetVertexData<PositionData>();   // PositionData::Elem* is Math::float3* 
		*/
		template< typename T>
		typename T::Elem* GetVertexData(IndexT unit = 0 );

		/** 
		* SetVertexData  ���ö������������
		* @param: const typename T::Elem * v ָ����������ĵ�ַ��NULL����ɾ���ö������  
		* @param: SizeT elemCount  ��������Ĵ�С��0����ɾ�������
		* @param: IndexT unit  �Զ�������ж����Ԫ������������������꣩��ָ��Ҫ�޸ĵĵ�Ԫ��������С�ڸ���������Ԫ���ƣ���������ʧ��
		* @return: bool  �Ƿ����óɹ�
		* @see: 
		* @remark:  ����������ָ��ǿ�ʱ����positionΪ���������Ӧ��֤��������Ĵ�С�͵�ǰ�Ķ���������ͬ����������ʧ�ܡ�
		������positionʱ�����Զ��޸�������������ݴ�С����Position��������Сʱ����ʹ��������submeshȫ��ʧЧ��
		use like: pMesh->SetVertexData<PositionData>(PositionData::Elem* elem , count );   // PositionData::Elem* is Math::float3* 

		*/
		template< typename T>
		bool SetVertexData( const typename T::Elem* v ,SizeT elemCount, IndexT unit = 0 );

		/// �Ƿ�ʹ��16λ�������� ��16λ������Чʱ������ʹ��16λ����������32λ�����Ƿ���Ч
		bool IsUseIndex16(void) const;

		/// �õ���������
		SizeT GetIndexCount(void) const;

		/// �õ�����������Ч����NULL
		const Index16Container::value_type* GetIndex16(void) const;
		const Index32Container::value_type* GetIndex32(void) const;

		/// �õ�����������Ч����NULL��!!!!!!!!!!!!����ֱ���޸�ָ��ָ������ݣ��ⲿӦ�ñ�֤�������ݵ���Ч�ԣ�������ܻ�Crash!!!!!!!!!!!!!!!!!
		Index16Container::value_type* GetIndex16(void);
		Index32Container::value_type* GetIndex32(void);

		/**
		* SetIndex16  ����16λ����
		* @param: const Index16Container::value_type * v   ΪNULL������ɾ��16λ����
		* @param: SizeT elemCount  
		* @return: bool  
		* @see: 
		* @remark:  		           
		����������ʱ����������Ӧ�ڶ���������Χ�ڣ���������ʧ�ܡ�
		������������16λ����32λ����ʱ��ԭ�е��������ᱻ��������е�submesh����ʧЧ
		���������ݱ�����ʱ�����е�submesh����ʧЧ
		*/
		bool SetIndex16(const Index16Container::value_type* v, SizeT elemCount);

		/// see SetIndex16
		bool SetIndex32(const Index32Container::value_type* v, SizeT elemCount);

		/// ������Ч��submesh������
		SizeT GetSubMeshCount(void) const;

		//// �õ�submesh
		const SubMesh* GetSubMesh(IndexT index ) const;

		/// �õ�submesh���������޸ġ�!!!!!!!!!!!!����ֱ���޸�ָ��ָ������ݣ��ⲿӦ�ñ�֤�������ݵ���Ч�ԣ�������ܻ�Crash!!!!!!!!!!!!!!!!!
		SubMesh* GetSubMesh(IndexT index);

		/// �õ�ÿ��submesh�ܵ�����Ӱ�����������
		const Util::Array<uchar>& GetAffectedBonesIndex(IndexT index) const;
		Util::Array<uchar>& GetAffectedBonesIndex(IndexT index);

		/**
		* SetSubMesh  ����submesh
		* @param: const SubMesh * submesh  Ϊ��ʱ��ɾ����Ӧ������SubMesh
		* @param: IndexT index  ���������ڵ�ǰSubMesh����������submesh��������Чʱ�����ᴴ�����ֱ���ﵽindexָ����������
		* @return: bool �Ƿ����óɹ� 
		* @see: 
		* @remark:  ��submeshָ������ݺ͵�ǰ�Ķ�����Ϣ��������Index����ƥ��ʱ������ʧ��
		�����Զ�����SubMesh�İ�Χ�У���Ҫ�ֶ�������غ�����
		��ɾ��SubMeshʱ����������е�����ʧЧ��ѭ������ʱע��!!!!!
		*/
		bool SetSubMesh(const SubMesh* submesh, IndexT index);

		void SetMeshID(const Util::String meshId);

		const Util::String GetMeshID();

		Util::Array<uint>& GetSubmeshUsedMaterial();

		/// ��鵱ǰmesh�е������Ƿ���Ч�� slow
		bool Validate(void) const;

		// @Resource::CalculateRuntimeSize
		virtual SizeT CalculateRuntimeSize(void) const;

		static GPtr<MeshRes> EmptyMeshRes;
		static Util::Array<uchar> EmptyBonesIndex;
	protected:
		// @Resource::SwapLoadImpl
		virtual bool SwapLoadImpl( const GPtr<Resource>& tempRes);
		// @Resource::UnLoadImpl
		virtual void UnLoadImpl(void);

		const void* GetDataImpl( VertexIndex::code t, IndexT unit ) const;
		bool SetDataImpl( VertexIndex::code t, const void* v, SizeT elemCount, IndexT unit );

		bool ValidateSubMesh(const SubMesh* submesh ) const;
	protected:

		RenderBase::PrimitiveTopology::Code mTopologyType;
		Math::bbox mBox;

		Util::String meshId;

		PositionData mPosition;
		ColorData    mColor;
		Util::Array<TexCoordData> mTexCoords;
		NormalData    mNormal;
		TangentData   mTangent;
		BiNormalData  mBiNormal;
		BoneInfoData  mBoneInfo;

		Index16Container  mIndex16;
		Index32Container  mIndex32;

		SubMeshArray mSubMeshs;

		AffectedBonesIndex mAffectedBonesIndex;
		Util::Array<uint> mSummeshUsedMaterial;

		friend class MeshResLoader;
		friend class MeshResSaver;
	};
	//------------------------------------------------------------------------
	inline 
		RenderBase::PrimitiveTopology::Code 
		MeshRes::GetTopologyType() const
	{
		return mTopologyType;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		MeshRes::SetTopologyType( RenderBase::PrimitiveTopology::Code t )
	{
		mTopologyType = t;
	}
	//------------------------------------------------------------------------
	inline 
		const Math::bbox& 
		MeshRes::GetBoundingBox() const
	{
		return mBox;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		MeshRes::SetBoundingBox( const Math::bbox& b )
	{
		mBox = b;
	}
	//------------------------------------------------------------------------
	inline
		void 
		MeshRes::SetMeshID(const Util::String id)
	{
		meshId = id;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		MeshRes::GetVertexCount(void) const
	{
		return mPosition.Size();
	}
	//------------------------------------------------------------------------
	inline
		IndexT 
		MeshRes::GetMaxTexUnitIndex(void) const
	{
		return mTexCoords.IsEmpty() ? InvalidIndex: ( mTexCoords.Size()-1 );

	}
	//------------------------------------------------------------------------
	template< typename T>
	inline
		const typename T::Elem* 
		MeshRes::GetVertexData(IndexT unit ) const
	{
		return (const typename T::Elem* )( GetDataImpl( (VertexIndex::code)(T::_index), unit ) );
	}
	//------------------------------------------------------------------------
	template< typename T>
	inline
		typename T::Elem* 
		MeshRes::GetVertexData(IndexT unit ) 
	{
		return (typename T::Elem* )( GetDataImpl( (VertexIndex::code)(T::_index), unit ) );
	}
	//------------------------------------------------------------------------
	template< typename T>
	inline
		bool 
		MeshRes::SetVertexData( const typename T::Elem* v ,SizeT elemCount, IndexT unit )
	{
		return SetDataImpl( (VertexIndex::code)(T::_index), v, elemCount, unit );
	}
	//------------------------------------------------------------------------
	/*  �ػ�����postion��ʵ��
	*/
	template<>
	bool 
		MeshRes::SetVertexData<PositionData>( const PositionData::Elem* v ,SizeT elemCount, IndexT unit );
	//------------------------------------------------------------------------
	inline
		bool 
		MeshRes::IsUseIndex16(void) const
	{
		return ( !mIndex16.IsEmpty() ) ? true: ( mIndex32.IsEmpty() );
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		MeshRes::GetIndexCount(void) const
	{
		if ( !mIndex16.IsEmpty() )
		{
			return mIndex16.Size();
		}
		else
		{
			return mIndex32.Size();
		}
	}
	//------------------------------------------------------------------------
	inline 
		const Index16Container::value_type* 
		MeshRes::GetIndex16(void) const
	{
		return ( mIndex16.IsEmpty() ) ? NULL: ( &mIndex16[0] );
	}
	//------------------------------------------------------------------------
	inline
		const Index32Container::value_type* 
		MeshRes::GetIndex32(void) const
	{
		return ( mIndex32.IsEmpty() ) ? NULL: ( &mIndex32[0] );
	}
	//------------------------------------------------------------------------
	inline 
		Index16Container::value_type* 
		MeshRes::GetIndex16(void)
	{
		return ( mIndex16.IsEmpty() ) ? NULL: ( &mIndex16[0] );
	}
	//------------------------------------------------------------------------
	inline
		Index32Container::value_type* 
		MeshRes::GetIndex32(void)
	{
		return ( mIndex32.IsEmpty() ) ? NULL: ( &mIndex32[0] );
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		MeshRes::GetSubMeshCount(void) const
	{
		return mSubMeshs.Size();
	}
	//------------------------------------------------------------------------
	inline
		const SubMesh* 
		MeshRes::GetSubMesh(IndexT index ) const
	{
		if ( index >= 0 && index < mSubMeshs.Size() )
		{
			return &(mSubMeshs[index]);
		}
		else
		{
			return NULL;
		}
	}
	//------------------------------------------------------------------------
	inline
		SubMesh* 
		MeshRes::GetSubMesh(IndexT index)
	{
		if ( index >= 0 && index < mSubMeshs.Size() )
		{
			return &(mSubMeshs[index]);
		}
		else
		{
			return NULL;
		}
	}

	inline
		Util::Array<uchar>&
		MeshRes::GetAffectedBonesIndex(IndexT index) 
	{
		if (index >=0 && index < mAffectedBonesIndex.Size())
		{
			return mAffectedBonesIndex[index];
		}
		else
		{
			n_assert("AffectedBonesIndex: Out of bound");
			return EmptyBonesIndex;
		}

	}
	//------------------------------------------------------------------------
	inline
		const Util::Array<uchar>&
		MeshRes::GetAffectedBonesIndex(IndexT index) const
	{
		const Util::Array<uchar>& tmp = GetAffectedBonesIndex(index);
		return tmp;		
	}


	//--------------------------------------------------------------------------
	inline
		const Util::String 
		MeshRes::GetMeshID()
	{
		return meshId;
	}
	//-------------------------------------------------------------------------
	inline
		Util::Array<uint>& MeshRes::GetSubmeshUsedMaterial()
	{
		return mSummeshUsedMaterial;
	}

}






#endif // __meshres_H__
