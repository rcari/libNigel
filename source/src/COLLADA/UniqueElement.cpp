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

#include <COLLADA/DocumentInstance.hpp>
#include <COLLADA/IScopedElement.hpp>
#include <COLLADA/UniqueElement.hpp>
using namespace Nigel::COLLADA;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE		Nigel::COLLADA::UniqueElement
#define K_BLOCK_SUPER_TYPE 	Nigel::COLLADA::Element
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_VIRTUAL
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

UniqueElement::UniqueElement()
{
}

void UniqueElement::library(Library* library)
{
	// Unregister from the current instance !
	unregisterWithInstance();
	Element::library(library);
	// Register to the new instance if it is one !
	registerWithInstance(Element::instance());
}

void UniqueElement::instanceChanged(DocumentInstance* instance)
{
	// Unregister with the old instance
	unregisterWithInstance();

	// Debug test !
	K_ASSERT(instance == Element::instance())

	// Register with the new instances
	registerWithInstance(instance);

	// Call the default implementation to further broadcast the change of instance.
	Element::instanceChanged(instance);
}

DocumentInstance* UniqueElement::instance()
{
	return cachedInstance(); // Return the cached version !
}

kuint UniqueElement::type() const
{
	return IElement::UniqueElementType;
}
