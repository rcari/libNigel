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

#include <data/Library.hpp>

template<typename T>
Nigel::COLLADA::ICollection<T>::ICollection()
:	_elementsNb(0)
{
}

template<typename T>
Nigel::COLLADA::ICollection<T>::~ICollection()
{
}

template<typename T>
const Kore::data::Library* Nigel::COLLADA::ICollection<T>::toLibrary() const
{
	return const_cast<ICollection<T>*>(this)->toLibrary();
}

template<typename T>
kint Nigel::COLLADA::ICollection<T>::nextIndex() const
{
	return elementsOffset(K_NULL_REF(T)) + _elementsNb;
}

template<typename T> template<typename U>
U* Nigel::COLLADA::ICollection<T>::element(kint index)
{
	return static_cast<U*>(
			toLibrary()->at(
				this->elementsOffset(K_NULL_REF(T)) + index
			)
		);
}

template<typename T> template<typename U>
const U* Nigel::COLLADA::ICollection<T>::element(kint index) const
{
	return static_cast<const U*>(
			toLibrary()->at(
				this->elementsOffset(K_NULL_REF(T)) + index
			)
		);
}

template<typename T>
void Nigel::COLLADA::ICollection<T>::registerElement(T* element, kint offset)
{
	offset = elementsOffset(K_NULL_REF(T)) + ( ( offset == -1 ) ? _elementsNb : offset );

	// Move the element to the right position in the library !
	toLibrary()->moveBlock( static_cast<Kore::data::Block*>(element), offset );

	_elementsNb++;

	notifyElementRegistered(element);
}

template<typename T>
void Nigel::COLLADA::ICollection<T>::unregisterElement(T*)
{
	_elementsNb--;
}
