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

#include <data/Library.hpp>

template<typename T>
Nigel::COLLADA::IOwner<T>::IOwner()
:	_element(K_NULL)
{
	// Nothing.
}

template<typename T>
Nigel::COLLADA::IOwner<T>::~IOwner()
{
	// Nothing.
}

template<typename T>
kint Nigel::COLLADA::IOwner<T>::nextIndex() const
{
	return elementIndex(K_NULL_REF(T)) + ( _element ? 1 : 0 );
}

template<typename T>
T* Nigel::COLLADA::IOwner<T>::element()
{
	return _element;
}

template<typename T>
const T* Nigel::COLLADA::IOwner<T>::element() const
{
	return _element;
}

template<typename T>
kbool Nigel::COLLADA::IOwner<T>::hasElement() const
{
	return _element != K_NULL_REF(T);
}

template<typename T>
void Nigel::COLLADA::IOwner<T>::element(T* element)
{
	_element = element;
	if(_element)
	{
		toLibrary()->moveBlock(
				static_cast<Kore::data::Block*>(_element),
				elementIndex(K_NULL_REF(T))
			);
		notifyElementRegistered(_element);
	}
}
