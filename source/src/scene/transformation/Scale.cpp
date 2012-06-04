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

#include <scene/transformation/Scale.hpp>
using namespace Nigel::scene::transformation;
using namespace Nigel::math;

#define K_BLOCK_TYPE		Nigel::scene::transformation::Scale
#define K_BLOCK_SUPER_TYPE	Nigel::scene::transformation::Transformation
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/transformation.scale.png")
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Scale::Scale()
:	_weights(1.0f, 1.0f, 1.0f)
{
	blockName(tr("Scale"));
}

Vector4f& Scale::weights()
{
	return _weights;
}

const Vector4f& Scale::weights() const
{
	return _weights;
}

kfloat Scale::kx() const
{
	return _weights.values().x;
}

void Scale::kx(kfloat kx)
{
	_weights.values().x = kx;
}

kfloat Scale::ky() const
{
	return _weights.values().y;
}

void Scale::ky(kfloat ky)
{
	_weights.values().y = ky;
}

kfloat Scale::kz() const
{
	return _weights.values().z;
}

void Scale::kz(kfloat kz)
{
	_weights.values().z = kz;
}
