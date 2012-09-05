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

#include <lighting/LightInstance.hpp>
using namespace Nigel::lighting;

#include <scene/Node.hpp>
using namespace Nigel::scene;

using namespace Nigel::COLLADA;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE 		Nigel::lighting::LightInstance
#define K_BLOCK_SUPER_TYPE 	Nigel::COLLADA::instantiation::ElementInstance
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

LightInstance::LightInstance()
{
}

void LightInstance::library(Library* lib)
{
	if(hasParent())
	{
		parent<Node>()->ICollection<LightInstance>::unregisterElement(this);
	}
	ScopedElement::library(lib);
	if(hasParent())
	{
		parent<Node>()->ICollection<LightInstance>::registerElement(this);
	}
}
