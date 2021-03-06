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

#include <scene/transformation/Rotation.hpp>
using namespace Nigel::scene::transformation;
using namespace Nigel::math;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE		Nigel::scene::transformation::Rotation
#define K_BLOCK_SUPER_TYPE	Nigel::scene::transformation::Transformation
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/transformation.rotate.png")
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Rotation::Rotation()
{
	blockName(tr("Rotation"));
	// Load identity rotation as a default !
	_orientation.identity();
}

Quaternionf& Rotation::orientation()
{
	return _orientation;
}

const Quaternionf& Rotation::orientation() const
{
	return _orientation;
}

void Rotation::x(kfloat x)
{
	_orientation.data().x = x;
}

kfloat Rotation::x() const
{
	return _orientation.data().x;
}

void Rotation::y(kfloat y)
{
	_orientation.data().y = y;
}

kfloat Rotation::y() const
{
	return _orientation.data().y;
}

void Rotation::z(kfloat z)
{
	_orientation.data().z = z;
}

kfloat Rotation::z() const
{
	return _orientation.data().z;
}

void Rotation::s(kfloat s)
{
	_orientation.data().s = s;
}

kfloat Rotation::s() const
{
	return _orientation.data().s;
}
