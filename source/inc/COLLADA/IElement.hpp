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

#include <data/Library.hpp>

#include <QtCore/QXmlStreamWriter>

namespace Nigel {

namespace geometry {
class IGeometryInstancesCollection;
}

namespace COLLADA {

namespace asset {
class IAssetOwner;
}

namespace data {
class ISourcesCollection;
}

namespace extra {
class IExtrasCollection;
}

class DocumentInstance;
class Element;
class IScopedElement;
class IUniqueElement;

/*!
 *  The goal of this interface is to avoid as much as possible using dynamic casts.
 *  It has direct conversion methods to types that require acess to a wide range of parents types.
 */
class NigelExport IElement
{
public:
	enum Type
	{
		ElementType					= 0x01,
		ScopedElementType			= 0x01 | 0x02,
		UniqueElementType			= 0x01 | 0x04,
		UniqueScopedElementType		= 0x01 | 0x02 | 0x04,
	};

public:
	virtual ~IElement();

	virtual IElement* parentElement() = K_NULL;

	virtual kuint type() const = K_NULL;

	// Kore::data
	virtual Kore::data::Library* toLibrary() { return K_NULL; }

	// Nigel::COLLADA
	virtual Element* toElement() = K_NULL;
	virtual IScopedElement* toScopedElement() { return K_NULL; }
	virtual IUniqueElement* toUniqueElement() { return K_NULL; }

	// Nigel::COLLADA::asset
	virtual asset::IAssetOwner* toAssetOwner() { return K_NULL; }

	// Nigel::COLLADA::data
	virtual data::ISourcesCollection* toSourcesCollection() { return K_NULL; }

	// Nigel::COLLADA::extra
	virtual extra::IExtrasCollection* toExtrasCollection() { return K_NULL; }

	// Nigel::geometry
	virtual Nigel::geometry::IGeometryInstancesCollection* toGeometryInstancesCollection() { return K_NULL; }

	virtual void serializeInStream(QXmlStreamWriter& stream) const = K_NULL;

	virtual void instanceChanged(DocumentInstance*) = K_NULL;
	virtual DocumentInstance* instance();
	const DocumentInstance* instance() const;
};

}}
