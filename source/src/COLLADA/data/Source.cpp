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

#include <COLLADA/data/Source.hpp>
#include <COLLADA/data/IArray.hpp>
#include <COLLADA/data/ISourcesCollection.hpp>
using namespace Nigel::COLLADA::data;
using namespace Nigel::COLLADA;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::COLLADA::data::Source
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Source::Source()
{
}

void Source::library(Library* lib)
{
	ISourcesCollection* collection = K_NULL;
	if(hasParent())
	{
		collection = static_cast<Nigel::COLLADA::Element*>(Library::library())->toSourcesCollection();
		K_ASSERT(collection)
		collection->unregisterElement(this);
	}
	UniqueElement::library(lib);
	if(lib)
	{
		collection = static_cast<Nigel::COLLADA::Element*>(lib)->toSourcesCollection();
		K_ASSERT(collection)
		collection->registerElement(this);
	}
}

kint Source::elementIndex(IArray*) const
{
	return IAssetOwner::nextIndex();
}

void Source::notifyElementRegistered(IArray* array)
{
	emit elementAdded(array);
}

kint Source::sourceIndex() const
{
	if(!hasParent())
	{
		return -1;
	}

	return this->index() - parentCollection()->elementsOffset(K_NULL_REF(Source));
}

IArray* Source::array()
{
	return IOwner<IArray>::element();
}

const IArray* Source::array() const
{
	return IOwner<IArray>::element();
}

ISourcesCollection* Source::parentCollection() const
{
	if(!hasParent())
	{
		return K_NULL;
	}

	return const_cast<Nigel::COLLADA::Element*>(
			static_cast<const Nigel::COLLADA::Element*>(Library::library())
		)->toSourcesCollection();
}
