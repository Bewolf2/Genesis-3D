/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
#ifndef __MYGUI_GENESIS_RTTEXTURE_H__
#define __MYGUI_GENESIS_RTTEXTURE_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_IRenderTarget.h"

#include "graphicsystem/base/RenderToTexture.h"

namespace MyGUI
{
	class GenesisRTTexture :
		public IRenderTarget
	{
	public:
		GenesisRTTexture(GPtr<Graphic::RenderToTexture>& rtt);
		virtual ~GenesisRTTexture();

		virtual void begin();
		virtual void end();

		virtual void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);

		virtual const RenderTargetInfo& getInfo()
		{
			return mRenderTargetInfo;
		}

		const GPtr<Graphic::RenderToTexture>& getRenderToTexture() const;

	private:
		RenderTargetInfo mRenderTargetInfo;
		GPtr<Graphic::RenderToTexture> m_rtt;
	};

	inline const GPtr<Graphic::RenderToTexture>& GenesisRTTexture::getRenderToTexture() const
	{
		return m_rtt;
	}

} // namespace MyGUI

#endif // __MYGUI_GENESIS_RTTEXTURE_H__
