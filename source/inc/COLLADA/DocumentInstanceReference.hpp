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

#pragma once

#include "extra/Extra.hpp"

#include <QtCore/QFileInfo>
#include <QtCore/QPointer>

namespace Nigel { namespace COLLADA {

class DocumentInstance;
class IElement;

class NigelExport DocumentInstanceReference : public Nigel::COLLADA::extra::Extra
{
	Q_OBJECT
	Q_PROPERTY( QString referenceText READ blockName STORED false DESIGNABLE false USER true )
	Q_PROPERTY( QString refPath READ refPath WRITE refPath STORED true DESIGNABLE false )
	Q_PROPERTY( bool alwaysLoad READ alwaysLoad WRITE alwaysLoad NOTIFY alwaysLoadChanged STORED true DESIGNABLE true )

	K_BLOCK

private:
	DocumentInstanceReference();

public:
	static DocumentInstanceReference* CreateDocumentInstanceReference(IElement* relativeTo, DocumentInstance* instance);

	kbool isReferenceResolved() const;

	DocumentInstance* reference();

	virtual QString blockName() const;

	virtual kint elementIndex(Nigel::COLLADA::asset::Asset*) const;

	QString refPath() const;

	virtual void instanceChanged(DocumentInstance*);

private:
	void reference(IElement* relativeTo, DocumentInstance* instance);

	void refPath(const QString&);

	QFileInfo referenceFileInfo();

	void alwaysLoad(kbool load);
	kbool alwaysLoad() const;

	static QVariant ElementProperty(kint property);

signals:
	void alwaysLoadChanged(bool);

private:
	QString _refPath;
	QPointer<DocumentInstance> _instance;
	kbool _alwaysLoad;
};

}}
