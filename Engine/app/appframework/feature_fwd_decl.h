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
#ifndef __FEATUREFWDDECL_H__
#define __FEATUREFWDDECL_H__

#include "core/ptr.h"

namespace App
{
	// pointer define
	/*
	etc 
	typedef GPtr<InputFeature> TInputFeaturePtr;
	T + ClassName + Feature Ptr

	typedef GPtr<const InputFeature> TInputFeatureConstPtr;
	T + ClassName + Feature ConstPtr
	 */

	// forward declare
	class InputFeature;
	class BaseGameFeature;
	class GraphicsFeature;
	class ParticleFeature;
	class VegetationFeature;
	class ResourceFeature;
    class SoundFeature;
    class ScriptFeature;
    class GUIServer;
#ifndef __OSX__
	class PhysicsFeature;
    class NetworkFeature;
#endif
    class FontFeature;
	class AnimationFeature;
	class GraphicObjectManager;
    class ALSystemFeature;
	
	
	class GameServer;


	// typedefs
	typedef GPtr<InputFeature> TInputFeaturePtr;
	typedef GPtr<BaseGameFeature> TBaseGameFeaturePtr;
	typedef GPtr<GraphicsFeature> TGraphicsFeaturePtr;
	typedef GPtr<ParticleFeature> TParticleFeaturePtr;
	typedef GPtr<VegetationFeature> TVegetationFeaturePtr;
	typedef GPtr<ResourceFeature> TResourceFeaturePtr;
	
	typedef GPtr<AnimationFeature> TAnimationFeaturePtr;
    typedef GPtr<ScriptFeature> TScriptFeaturePtr;
   	typedef GPtr<SoundFeature> TSoundFeaturePtr;
   	typedef GPtr<FontFeature> TFontFeaturePtr;
    typedef GPtr<ALSystemFeature> TALSystemFeaturePtr;
#ifndef __OSX__
    typedef GPtr<PhysicsFeature> TPhysicsFeaturePtr;
	typedef GPtr<NetworkFeature> TNetworkFeaturePtr;
#endif
}

#endif // __FEATUREFWDDECL_H__
