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
using System;
using System.Runtime.CompilerServices;
using ScriptRuntime;

namespace ScriptRuntime
{
    /// <summary>
    /// ͶӰ�������
    /// </summary>
    public partial class ProjectorRenderComponent : RenderComponent
    {
        public static readonly System.Type thisType = typeof(ProjectorRenderComponent);

        private ProjectorRenderComponent(DummyClass__ dummy)
        {

        }

        protected ProjectorRenderComponent()
        {

        }

        internal static ViewType converViewType(int viewType)
        {
            return (ViewType)viewType;
        }

        /// <summary>
        /// ��ȡͶӰ������
        /// </summary>
        public ViewType ViewType
        {
            get
            {
                return converViewType(ICall_ProjectorRenderComponent_GetViewType(this));
            }
            set
            {
                ICall_ProjectorRenderComponent_SetViewType( this, (int)value);
            }
        }

        /// <summary>
        /// ��ȡͶӰ���͸��ͶӰ�µ������ӽ�(�Ƕ�)
        /// </summary>
        public float Fov
        {
            get
            {
                return ICall_ProjectorRenderComponent_GetFov(this);
            }
            set
            {
                if (ViewType == ViewType.Orthogonal)
                    return;
                if (value < 1.0f)
                    value = 1.0f;
                if (value > 179.0f)
                    value = 179.0f;
                ICall_ProjectorRenderComponent_SetFov(this, value);
            }
        }

        /// <summary>
        /// ��ȡͶӰ��ĺ��ݱ�
        /// </summary>
        public float Aspect
        {
            get
            {
                return ICall_ProjectorRenderComponent_GetAspect(this);
            }
            set
            {
                if (value < 1.0f)
                    value = 1.0f;
                if (value > 179.0f)
                    value = 179.0f;
                ICall_ProjectorRenderComponent_SetAspect(this, value);
            }
        }

        /// <summary>
        /// ��ȡ�����ý��ü���ľ���
        /// </summary>
        public float NearClipPlane
        {
            get
            {
                return ICall_ProjectorRenderComponent_GetZNear(this);
            }
            set
            {
                if (value < 0.01f)
                {
                    return;
                }

                ICall_ProjectorRenderComponent_SetZNear(this, value);

                if (value >= FarClipPlane)
                {
                    FarClipPlane = value + 0.01f;
                }
            }
        }

        /// <summary>
        /// ��ȡ������Զ�ü���ľ���
        /// </summary>
        public float FarClipPlane
        {
            get
            {
                return ICall_ProjectorRenderComponent_GetZFar(this);
            }
            set
            {
                if (value < 0.02f)
                {
                    return;
                }

                ICall_ProjectorRenderComponent_SetZFar(this, value);

                if (NearClipPlane >= value)
                {
                    NearClipPlane = value - 0.01f;
                }
            }
        }

        /// <summary>
        /// ��ȡ����������ͶӰ�ĸ߶�
        /// </summary>
        public float ViewSize
        {
            get
            {
                return ICall_ProjectorRenderComponent_GetNearHeight(this);
            }
            set
            {
                if (ViewType == ViewType.Perspective)
                    return;
                if (value < 0.01f)
                    value = 0.01f;
                ICall_ProjectorRenderComponent_SetNearHeight(this, value);
            }
        }

        /// <summary>
        /// ��ȡ����������ͶӰ�ĺ��Բ�
        /// </summary>
        public LayerMark IgnoreLayers
        {
            set
            {
                ICall_ProjectorRenderComponent_SetIgnoreLayers(this, value.MarkAsUINT);
            }
            get
            {
                return ICall_ProjectorRenderComponent_GetIgnoreLayers(this);
            }
        }

        /// <summary>
        /// ��ȡ����������ͶӰ�ĺ��Բ�
        /// </summary>
        public uint IgnoreLayersUINT
        {
            set
            {
                ICall_ProjectorRenderComponent_SetIgnoreLayers(this, (uint)LayerMark.ConvertToMark((LayerID)value));
            }
            get
            {
                return ICall_ProjectorRenderComponent_GetIgnoreLayers(this);
            }
        }

        /// <summary>
        /// ����ͶӰ����½ӿ�
        /// </summary>
        public bool EnableProjector
        {
            set{
                ICall_ProjectorRenderComponent_EnableProjector(this, value);
            }
            get{
                return ICall_ProjectorRenderComponent_IsEnabledProjector(this);
            }
        }
    }
}