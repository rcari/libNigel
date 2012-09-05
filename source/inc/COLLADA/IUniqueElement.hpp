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

#include <Types.hpp>

#include <QtCore/QHash>
#include <QtCore/QUuid>

namespace Nigel { namespace COLLADA {

class DocumentInstance;

class Element;
class IScopedElement;

class NigelExport IUniqueElement
{
	friend class IScopedElement;

protected:
	IUniqueElement();

public:
	virtual ~IUniqueElement();

	const QUuid& id() const;

protected:
	QString serializedId() const;
	void serializedId(const QString& id);

public:
	virtual void instanceChanged(DocumentInstance*) = K_NULL;
	virtual DocumentInstance* instance() = K_NULL; // To force caching of the instance.
	const DocumentInstance* instance() const;

	virtual Element* toElement() = K_NULL;
	virtual IUniqueElement* toUniqueElement() = K_NULL;

private:
	void registerScopedElement(const QString& path, IScopedElement* element);
	void unregisterScopedElement(const QString& path, IScopedElement* element);

protected:
	void registerWithInstance(Nigel::COLLADA::DocumentInstance* instance) const;
	void unregisterWithInstance();

	inline DocumentInstance* cachedInstance() { return _instance; }

private:
	mutable QUuid _id; // Mutable as it can be set on first call to id().
	mutable DocumentInstance* _instance;
	QHash<QString,IScopedElement*> _scopedElements;

};

}}
