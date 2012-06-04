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
 *	DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
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

class Scale : public Transformation
{
	Q_OBJECT

	Q_PROPERTY( float kx READ kx WRITE kx STORED true DESIGNABLE false )
	Q_PROPERTY( float ky READ ky WRITE ky STORED true DESIGNABLE false )
	Q_PROPERTY( float kz READ kz WRITE kz STORED true DESIGNABLE false )

	K_BLOCK

protected:
	Scale();

public:
	Nigel::math::Vector4f& weights();
	const Nigel::math::Vector4f& weights() const;

private:
	kfloat kx() const;
	void kx(kfloat kx);

	kfloat ky() const;
	void ky(kfloat ky);

	kfloat kz() const;
	void kz(kfloat kz);

private:
	_K_SSE_ALIGNED Nigel::math::Vector4f _weights;
};

}}}
