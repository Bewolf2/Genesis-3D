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
    /// ���߼������㷨�ļ���
    /// </summary>
    public static class IntersectWorld// : Base
    {
        /// <summary>
        /// ����һ���ӵ�ǰĬ���������������
        /// </summary>
        /// <param name="screenPos">��������λ�ã�ȡֵ��Χ��[0,1]</param>
        /// <param name="outRay">����ֵ������������ߣ�</param>
        static public void IntersectWorld_ComputeRay(ref Vector2 screenPos, out Ray outRay)
        {
            ICall_IntersectWorld_ComputeRay(ref screenPos,out outRay);
        }

        /// <summary>
        /// ���߼��ָ����Actor
        /// </summary>
        /// <param name="act">Ҫ����Actor</param>
        /// <param name="ray">����</param>
        /// <param name="layerid">������Ĳ�</param>
        /// <param name="pos">���ߴ�Actor�ϵĵ������</param>
        /// <returns>�Ƿ��⵽Actor</returns>
        static public bool IntersectActor(Actor act, ref Ray ray, LayerID layerid, out Vector3 pos)
        {
            if (LayerID.Min <= layerid && layerid < LayerID.Max)
            {
                return ICall_IntersectWorld_IntersectActor(act, ref ray, LayerMark.ConvertToMark(layerid), out pos);
            }
            pos = Vector3.Zero;
            return false;
        }

        /// <summary>
        /// ���߼��Actor
        /// </summary>
        /// <param name="ray">ָ��������</param>
        /// <param name="layerid">������Ĳ�</param>
        /// <returns>���߼�⵽Actor�����ߴ���㷢������һ����⵽��Actor������û�м�⵽�κ�Actor������NULL</returns>
        static public Actor IntersectWorld_Actor(ref Ray ray, LayerID layerid)
        {
            if (LayerID.Min <= layerid && layerid < LayerID.Max)
            {
                return ICall_IntersectWorld_Actor(ref ray, LayerMark.ConvertToMark(layerid));
            }
            return null;
        }

        /// <summary>
        /// ��ȡ���߼�⵽������(����)Actor�ĵ�һ���������
        /// </summary>
        /// <param name="ray">ָ��������</param>
        /// <param name="layerid">������Ĳ�</param>
        /// <param name="outPoint">����ֵ����⵽�ĵ�һ��������꣩</param>
        static public void IntersectWorld_Point(ref Ray ray, LayerID layerid, out Vector3 outPoint)
        {
            if (LayerID.Min <= layerid && layerid < LayerID.Max)
            {
                ICall_IntersectWorld_Point(ref ray, LayerMark.ConvertToMark(layerid), out outPoint);
            }
            else
            {
                outPoint = Vector3.Zero;
            }
        }

        /// <summary>
        /// ��ȡ������ָ��(����)Actor�Ľ���
        /// </summary>
        /// <param name="act">Ҫ����Actor</param>
        /// <param name="ray">Ҫ��������</param>
        /// <param name="mark">Actor�Ĺ��˲�(ֻ��������Actor�������߼��)</param>
        /// <param name="pos">������Actor�Ľ���</param>
        /// <returns>������Actor�Ƿ��н���</returns>
        static public bool IntersectActor(Actor act, ref Ray ray, LayerMark mark, out Vector3 pos)
        {
            return ICall_IntersectWorld_IntersectActor(act, ref ray, mark.MarkAsUINT, out pos);
        }

        /// <summary>
        /// ��ȡ���ߴ��еĵ�һ��(����)Actor
        /// </summary>
        /// <param name="ray">ָ��������</param>
        /// <param name="mark">Actor�Ĺ��˲�(ֻ��������Actor�������߼��)</param>
        /// <returns></returns>
        static public Actor IntersectWorld_Actor(ref Ray ray, LayerMark mark)
        {
            return ICall_IntersectWorld_Actor(ref ray, mark.MarkAsUINT);
        }

        /// <summary>
        /// ��ȡ���ߴ��еĵ�һ��(����)Actor�Ľ���
        /// </summary>
        /// <param name="ray">ָ��������</param>
        /// <param name="mark">Actor�Ĺ��˲�(ֻ��������Actor�������߼��)</param>
        /// <param name="outPoint">�������һ��Actor�Ľ���</param>
        static public void IntersectWorld_Point(ref Ray ray, LayerMark mark, out Vector3 outPoint)
        {
            ICall_IntersectWorld_Point(ref ray, mark.MarkAsUINT, out outPoint);
        }

        /// <summary>
        /// ��ȡ���ߴ��еĵ�һ�������ϵ������ε�������
        /// </summary>
        /// <param name="ray">ָ��������</param>
        /// <param name="mark">Actor�Ĺ��˲�(ֻ��������Actor�������߼��)</param>
        /// <param name="outPoint1">�����εĵ�һ����</param>
        /// <param name="outPoint2">�����εĵڶ�����</param>
        /// <param name="outPoint3">�����εĵ�������</param>
        static public void IntersectWorld_Triangle(ref Ray ray, LayerMark mark, out Vector3 outPoint1, out Vector3 outPoint2, out Vector3 outPoint3)
        {
            ICall_IntersectWorld_Triangle(ref ray, mark.MarkAsUINT, out outPoint1, out outPoint2, out outPoint3);
        }

        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_IntersectWorld_ComputeRay(ref Vector2 screenPos, out Ray outRay);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_IntersectWorld_IntersectActor(Actor act, ref Ray ray, uint selectMark, out Vector3 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_IntersectWorld_Actor(ref Ray ray, uint selectMark);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_IntersectWorld_Point(ref Ray ray, uint selectMark, out Vector3 outFloat3);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_IntersectWorld_Triangle(ref Ray ray, uint selectMark, out Vector3 outPoint1, out Vector3 outPoint2, out Vector3 outPoint3);
    }
}
