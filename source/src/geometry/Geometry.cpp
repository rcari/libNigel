/*
 * 	Copyright (c) 2010-2011, Christophe EVENO
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

#include <geometry/Geometry.hpp>
#include <geometry/GeometricElement.hpp>
#include <geometry/GeometriesLibrary.hpp>
using namespace Nigel::geometry;
using namespace Nigel::COLLADA;
using namespace Nigel::COLLADA::asset;
using namespace Nigel::COLLADA::extra;

using namespace Kore::data;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::geometry::Geometry
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Geometry::Geometry()
{
}

void Geometry::library(Library* library)
{
	if(hasParent())
	{
		parent<GeometriesLibrary>()->ICollection<Geometry>::unregisterElement(this);
	}
	UniqueElement::library(library);
	if(hasParent())
	{
		parent<GeometriesLibrary>()->ICollection<Geometry>::registerElement(this);
	}
}

GeometricElement* Geometry::element()
{
	return IOwner<GeometricElement>::element();
}

kint Geometry::elementIndex(GeometricElement*) const
{
	return IAssetOwner::nextIndex();
}

void Geometry::notifyElementRegistered(GeometricElement* element)
{
	emit elementAdded(element);
}

kint Geometry::elementsOffset(Extra*) const
{
	return IOwner<GeometricElement>::nextIndex();
}
