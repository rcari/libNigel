/*
 * 	Copyright (c) 2010-2011, Romuald CARI
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *		* Redistributions of source code must retain the above copyright
 *		  notice, this list of conditions and the following disclaimer.
 *		* Redistributions in binary form must reproduce the above copyright
 *		  notice, this list of conditions and the following disclaimer in the
 *		  documentation and/or other materials provided with the distribution.
 *		* Neither the name of the <organization> nor the
 *		  names of its contributors may be used to endorse or promote products
 *		  derived from this software without specific prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *	DISCLAIMED. IN NO EVENT SHALL Romuald CARI BE LIABLE FOR ANY
 *	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

#include "Transformation.hpp"

#include <math/Vector4f.hpp>

namespace Nigel { namespace scene { namespace transformation {

// TODO: Fix potential problems with SSE alignment as for Matrix.

class Translation : public Transformation
{
	Q_OBJECT

	Q_PROPERTY( float x READ x WRITE x NOTIFY xChanged STORED true DESIGNABLE true )
	Q_PROPERTY( float y READ y WRITE y NOTIFY yChanged STORED true DESIGNABLE true )
	Q_PROPERTY( float z READ z WRITE z NOTIFY zChanged STORED true DESIGNABLE true )

	K_BLOCK

protected:
	Translation();

public:
	Nigel::math::Vector4f& direction();
	const Nigel::math::Vector4f& direction() const;

private:
	kfloat x() const;
	void x(kfloat x);

	kfloat y() const;
	void y(kfloat y);

	kfloat z() const;
	void z(kfloat z);

signals:
	void xChanged(kfloat);
	void yChanged(kfloat);
	void zChanged(kfloat);

private:
	_K_SSE_ALIGNED Nigel::math::Vector4f _direction;
};

}}}
