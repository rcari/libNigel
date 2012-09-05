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

#include <COLLADA/IUniqueElement.hpp>
#include <COLLADA/IScopedElement.hpp>
#include <COLLADA/DocumentInstance.hpp>
using namespace Nigel::COLLADA;

IUniqueElement::IUniqueElement()
:	_instance(K_NULL)
{
}

IUniqueElement::~IUniqueElement()
{
}

const QUuid& IUniqueElement::id() const
{
	if(_id.isNull())
	{
		// We have a request for our ID, create one !
		_id = QUuid::createUuid();
		// And register now that we have an ID !
		registerWithInstance(_instance);
	}
	return _id;
}

QString IUniqueElement::serializedId() const
{
	if(_id.isNull())
	{
		return QString(); // No need to return a crazy long 0 filled string !
	}
	return _id.toString();
}

void IUniqueElement::serializedId(const QString& id)
{
	if(!id.isEmpty())
	{
		_id = QUuid(id);
	}
}

const DocumentInstance* IUniqueElement::instance() const
{
	return const_cast<IUniqueElement*>(this)->instance();
}

void IUniqueElement::registerScopedElement(const QString& path, IScopedElement* element)
{
	K_ASSERT( !_scopedElements.contains(path) )
	_scopedElements.insert(path, element);
}

void IUniqueElement::unregisterScopedElement(const QString& path, IScopedElement* element)
{
	K_ASSERT( _scopedElements.value(path, K_NULL) == element )
	_scopedElements.remove(path);
}

void IUniqueElement::registerWithInstance(DocumentInstance* instance) const
{
	// Cache the instance !
	_instance = instance;

	if(_id.isNull())
	{
		return; // No need to register a unique element without an ID !
	}

	if(_instance)
	{
		_instance->registerUniqueElement( const_cast<IUniqueElement*>(this) );
	}
}

void IUniqueElement::unregisterWithInstance()
{
	if(_id.isNull())
	{
		// No need to unregister if we don't have an ID !
	}
	else if(_instance)
	{
		_instance->unregisterUniqueElement(this);
	}

	// Uncache the instance !
	_instance = K_NULL;
}
