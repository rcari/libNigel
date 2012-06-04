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

#include <COLLADA/Element.hpp>
using namespace Nigel::COLLADA;
using namespace Kore::data;

#define K_BLOCK_TYPE Nigel::COLLADA::Element
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/element.png")
	K_BLOCK_VIRTUAL
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Element::Element()
{
	// All elements are serializable.
	addFlag(Block::Serializable);
	// When the block changes, the element changes...
	connect(this, SIGNAL(blockChanged()), SIGNAL(elementChanged()));
}

void Element::library(Library* lib)
{
	if(hasParent())
	{
		disconnect(this, SIGNAL(elementChanged()), parent<Element>(), SIGNAL(elementChanged()));
		parent<Element>()->notifyElementRemoved(this);
	}
	Library::library(lib);
	if(hasParent())
	{
		parent<Element>()->notifyElementAdded(this);
		connect(this, SIGNAL(elementChanged()), lib, SIGNAL(elementChanged()));
	}
}

IElement* Element::parentElement()
{
	return parent<Element>();
}

kuint Element::type() const
{
	return IElement::ElementType;
}

void Element::instanceChanged(DocumentInstance* instance)
{
	for(kint i = 0; i < this->size(); i++)
	{
		static_cast<Element*>(this->at(i))->instanceChanged(instance);
	}
}

void Element::serializeInStream(QXmlStreamWriter& stream) const
{
	stream.writeStartElement(objectClassName());

	for(kint i = 0; i < size(); i++)
	{
		at<Element>(i)->serializeInStream(stream);
	}

	stream.writeEndElement();
}

void Element::notifyElementAdded(Element* element)
{
	emit elementAdded(element);
	emit elementChanged();
}

void Element::notifyElementRemoved(Element* element)
{
	emit elementRemoved(element);
	emit elementChanged();
}
