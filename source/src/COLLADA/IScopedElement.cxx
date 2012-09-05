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

#include "../../inc/COLLADA/IElement.hpp"
#include "../../inc/COLLADA/IScopedElement.hpp"
#include "../../inc/COLLADA/IUniqueElement.hpp"

template<typename T>
void Nigel::COLLADA::IScopedElement::registerWithScope()
{
	if(_sid.isEmpty())
	{
		return; // No need to register an element with an empty SID !
	}

	IElement* element = static_cast<T*>(this)->parentElement();
	QString path = _sid;

	for( ; element != K_NULL; element = element->parentElement())
	{
		if(element->type() & IElement::UniqueElementType)
		{
			IUniqueElement* uElement = element->toUniqueElement();
			if(!uElement->_id.isNull())
			{
				// We are finished we have found the UniqueElement with an ID, it's our ancestor.
				_uniqueElement = uElement;
				_pathFromUniqueElement = path;
				uElement->registerScopedElement(_pathFromUniqueElement, this);
				return;
			}
		}
		if(element->type() & IElement::ScopedElementType)
		{
			IScopedElement* sElement = element->toScopedElement();
			if(!sElement->_sid.isEmpty())
			{
				// There is a scoped element on our path with an SID set, add it to the path !
				path.prepend('/');
				path.prepend(sElement->_sid);
			}
		}
	}

	qDebug("WEIRD: Could not find a valid scope ancestor to register to @ %s : %d", __FILE__, __LINE__);
}

template<typename T>
void Nigel::COLLADA::IScopedElement::unregisterWithScope()
{
	if(_sid.isEmpty())
	{
		return; // No need to unregister an element with an empty SID !
	}

	IElement* element = static_cast<T*>(this)->parentElement();
	QString path = _sid;

	for( ; element != K_NULL; element = element->parentElement())
	{
		if(element->type() & IElement::UniqueElementType)
		{
			IUniqueElement* uElement = element->toUniqueElement();
			K_ASSERT(uElement)
			if(!uElement->_id.isNull())
			{
				// We are finished we have found the UniqueElement with an ID, it's our ancestor.
				uElement->unregisterScopedElement(path, this);
				return;
			}
		}
		if(element->type() & IElement::ScopedElementType)
		{
			IScopedElement* sElement = element->toScopedElement();
			K_ASSERT(sElement)
			if(!sElement->_sid.isEmpty())
			{
				// There is a scoped element on our path with an SID set, add it to the path !
				path.prepend('/');
				path.prepend(sElement->_sid);
			}
		}
	}

	qWarning("WEIRD: Could not find a valid scope ancestor to unregister from @ %s : %d", __FILE__, __LINE__);
}
