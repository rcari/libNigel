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

#include <scene/transformation/Translation.hpp>
using namespace Nigel::scene::transformation;

using namespace Nigel::math;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE		Nigel::scene::transformation::Translation
#define K_BLOCK_SUPER_TYPE	Nigel::scene::transformation::Transformation
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/transformation.translate.png")
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Translation::Translation()
{
	blockName(tr("Translation"));
}

Vector4f& Translation::direction()
{
	return _direction;
}

const Vector4f& Translation::direction() const
{
	return _direction;
}

kfloat Translation::x() const
{
	return _direction.values().x;
}

void Translation::x(kfloat x)
{
	_direction.values().x = x;
	emit xChanged(x);
	emit elementChanged();
}

kfloat Translation::y() const
{
	return _direction.values().y;
}

void Translation::y(kfloat y)
{
	_direction.values().y = y;
	emit yChanged(y);
	emit elementChanged();
}

kfloat Translation::z() const
{
	return _direction.values().z;
}

void Translation::z(kfloat z)
{
	_direction.values().z = z;
	emit zChanged(z);
	emit elementChanged();
}
