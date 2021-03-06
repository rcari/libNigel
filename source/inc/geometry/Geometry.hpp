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

#include <NigelExport.hpp>

#include "../COLLADA/UniqueElement.hpp"
#include "../COLLADA/asset/IAssetOwner.hpp"
#include "../COLLADA/extra/IExtrasCollection.hpp"

namespace Nigel { namespace geometry {

class GeometricElement;

class NigelExport Geometry
:	public Nigel::COLLADA::UniqueElement,
 	public Nigel::COLLADA::asset::IAssetOwner,
 	public Nigel::COLLADA::IOwner<GeometricElement>,
 	public Nigel::COLLADA::extra::IExtrasCollection
{
	Q_OBJECT
	Q_PROPERTY(QString geometryName READ blockName WRITE blockName STORED true DESIGNABLE false)

	K_BLOCK

	friend class GeometricElement;

protected:
	Geometry();

	virtual void library(Kore::data::Library* library);

public:
	GeometricElement* element();

protected:
	virtual Kore::data::Library* toLibrary() { return this; }
	virtual Nigel::COLLADA::Element* toElement() { return this; }

	virtual Nigel::COLLADA::asset::IAssetOwner* toAssetOwner() { return this; }

	virtual kint elementIndex(GeometricElement*) const;
	virtual void notifyElementRegistered(GeometricElement*);

	virtual kint elementsOffset(Nigel::COLLADA::extra::Extra*) const;
	virtual Nigel::COLLADA::extra::IExtrasCollection* toExtrasCollection() { return this; }
};

}}

#ifdef NIGEL_MSVC
#include <geometry/GeometricElement.hpp>
#endif
