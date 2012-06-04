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

#include <NigelExport.hpp>

#include "Element.hpp"

#include <data/Library.hpp>

#include <QtCore/QDir>

namespace Nigel { namespace COLLADA {

class DocumentInstance;
class IUniqueElement;

/*!
 * An InstancesManager holds DocumentsInstances and makes the connections between them.
 * Its purpose is purely runtime !
 */
class NigelExport InstancesManager : public Element
{
	friend class DocumentInstance;

	Q_OBJECT
	Q_PROPERTY( QString rootInstancePath READ rootInstancePath STORED false DESIGNABLE true )

	K_BLOCK

protected:
	InstancesManager();

	virtual void library(Kore::data::Library* lib);

public:
	bool loadRootInstance(QString path);
	bool setRootInstance(Nigel::COLLADA::DocumentInstance* instance, kbool save = false);

	Nigel::COLLADA::DocumentInstance* rootInstance();
	const Nigel::COLLADA::DocumentInstance* rootInstance() const;


	QString url(const Element* element, const IUniqueElement* uniqueElement) const;
	/*!
	 * This method may return K_NULL !
	 * @param element
	 * @param url
	 * @return
	 */
	IUniqueElement* resolveUrl(Element* element, const QString& url, kbool lazy = false);

	// Sub classes might want to handle those operations in special ways...
	virtual Nigel::COLLADA::DocumentInstance* loadInstance(const QFileInfo& file);
	virtual void saveInstance(const Nigel::COLLADA::DocumentInstance* instance) const;

	virtual DocumentInstance* instance();

protected:
	QString rootInstancePath() const;
	virtual void registerDocumentInstance(DocumentInstance*);
	virtual void unregisterDocumentInstance(DocumentInstance*);

private:
	QDir _rootFolder;
	Nigel::COLLADA::DocumentInstance* _rootInstance;
	QHash<QString,Nigel::COLLADA::DocumentInstance*> _instances;

};

}}

#ifdef NIGEL_MSVC
#include <camera/CameraInstance.hpp>
#include <COLLADA/extra/Extra.hpp>
#include <geometry/Geometry.hpp>
#include <lighting/LightInstance.hpp>
#include <scene/Node.hpp>
#include <scene/NodeInstance.hpp>
#include <scene/Scene.hpp>
#include <scene/VisualSceneInstance.hpp>
#include <scene/transformation/Transformation.hpp>
#endif
