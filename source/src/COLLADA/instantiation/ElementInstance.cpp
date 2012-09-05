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

#include <COLLADA/instantiation/ElementInstance.hpp>
using namespace Nigel::COLLADA::instantiation;

#include <COLLADA/Element.hpp>
#include <COLLADA/DocumentInstance.hpp>
#include <COLLADA/InstancesManager.hpp>
using namespace Nigel::COLLADA;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::COLLADA::instantiation::ElementInstance
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/element.instance.png")
	K_BLOCK_VIRTUAL
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

using namespace Kore;

ElementInstance::ElementInstance()
: 	_instantiatedElement(K_NULL)
{
}

QString ElementInstance::instanceName() const
{
	QString instanceName = isInstanceResolved()
			?	_instantiatedElement->toElement()->toLibrary()->blockName()
			:	tr("Unloaded");

	return tr("Reference: %1").arg(instanceName);
}

kbool ElementInstance::isInstanceResolved() const
{
	return _instantiatedElement != K_NULL;
}

IUniqueElement* ElementInstance::instantiatedElement()
{
	if(!_instantiatedElement)
	{
		resolve(false); // This has to be resolved right now !
	}
	return _instantiatedElement;
}

void ElementInstance::instanceChanged(DocumentInstance* instance)
{
	ScopedElement::instanceChanged(instance);
	resolve(true); // Lazy resolve...
}

void ElementInstance::privateInstantiatedElement(IUniqueElement* element)
{
	K_ASSERT( element->toElement() );
	_instantiatedElement = element;
	connect(_instantiatedElement->toElement(), SIGNAL(elementChanged()), SIGNAL(elementChanged()));
}

QString ElementInstance::url() const
{
	if(!_instantiatedElement)
	{
		// The instance was not resolved yet so we provide the url as it was given when serialized.
		return _url;
	}
	K_ASSERT( instance() )
	K_ASSERT( instance()->manager() )
	// Return the URL from the instance manager.
	return instance()->manager()->url(this, _instantiatedElement);
}

void ElementInstance::url(const QString& url)
{
	_url = url;
}

void ElementInstance::resolve(kbool lazy)
{
	// No need to resolve if already resolved !
	if(_instantiatedElement)
	{
		return;
	}

	_instantiatedElement = instance()->manager()->resolveUrl(this, _url, lazy);
	if(_instantiatedElement)
	{
		connect(_instantiatedElement->toElement(), SIGNAL(elementChanged()), SIGNAL(elementChanged()));
		emit resolved();
	}
}
