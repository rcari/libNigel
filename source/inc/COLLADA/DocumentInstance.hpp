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

#include <data/Library.hpp>
#include <serialization/ProgressCallback.hpp>

#include "asset/IAssetOwner.hpp"
#include "extra/IExtrasCollection.hpp"
#include "Element.hpp"

#include <QtCore/QFileInfo>
#include <QtCore/QHash>
#include <QtCore/QStringList>
#include <QtCore/QUuid>

namespace Nigel {

namespace scene { class Scene; }

namespace COLLADA {

class IUniqueElement;
class InstancesManager;

class NigelExport DocumentInstance
:	public Element,
 	public Nigel::COLLADA::asset::IAssetOwner,
 	public Nigel::COLLADA::IOwner<Nigel::scene::Scene>,
 	public Nigel::COLLADA::extra::IExtrasCollection
{
	Q_OBJECT
	Q_PROPERTY( QString filePath READ infoString STORED false DESIGNABLE true )
	K_BLOCK

	friend class InstancesManager;
	friend class IUniqueElement;
	friend class Nigel::scene::Scene; // For it to properly register.

public:
	enum Version
	{
		COLLADA_Version14,
		COLLADA_Version15,
	};

protected:
	/*!
	 * Create a COLLADA document instance.
	 */
	DocumentInstance();

	virtual void library(Kore::data::Library* library);

public:
	virtual void addBlock(Kore::data::Block* b);
	virtual void removeBlock(Kore::data::Block* b);
	virtual void insertBlock(Kore::data::Block* b, kint index);

public:
	InstancesManager* manager();
	const InstancesManager* manager() const;

	/*!
	 * Update the Asset last modification date.
	 */
	void updateAsset();

	void version(Version v);
	Version version() const;

	Nigel::scene::Scene* scene();
	const Nigel::scene::Scene* scene() const;

	virtual DocumentInstance* instance();

	const QFileInfo& fileInfo() const;

	kbool hasId(const QString& id) const;

	IUniqueElement* elementById(const QUuid& id);
	const IUniqueElement* elementById(const QUuid& id) const;

	QString sid(const IScopedElement* element) const;

	virtual QString infoString() const;

public:
	template<typename T>
	static T* CreateDocumentInstance(const QString& absoluteFilePath);

	static DocumentInstance* LoadDocumentInstance(const QString& absoluteFilePath, Kore::serialization::ProgressCallback* callback = K_NULL);
	static bool SaveDocumentInstance(const DocumentInstance* instance, const QString& filePath = QString(), Kore::serialization::ProgressCallback* callback = K_NULL);

public:
	virtual Nigel::COLLADA::asset::IAssetOwner* toAssetOwner() { return this; }
	virtual Kore::data::Library* toLibrary() { return this; }
	virtual Nigel::COLLADA::Element* toElement() { return this; }
	virtual Nigel::COLLADA::extra::IExtrasCollection* toExtrasCollection() { return this; }

protected:
	virtual kint elementIndex(Nigel::scene::Scene*) const;
	virtual void notifyElementRegistered(Nigel::scene::Scene*);
	virtual kint elementsOffset(Nigel::COLLADA::extra::Extra*) const;

private:
	void registerUniqueElement(IUniqueElement* e);
	void unregisterUniqueElement(IUniqueElement* e);

private:
	// The document instance's mandatory version (attribute).
	Version _version;

	// Libraries
	// ?? No special links [0..*]

	// Internal housekeeping !
	QFileInfo _fileInfo;
	QHash<QUuid,IUniqueElement*> _uniqueElements;
};

}}

#include <src/COLLADA/DocumentInstance.cxx>

#ifdef NIGEL_MSVC
#include <camera/CameraInstance.hpp>
#include <COLLADA/extra/Extra.hpp>
#include <geometry/Geometry.hpp>
#include <lighting/LightInstance.hpp>
#include <scene/NodeInstance.hpp>
#include <scene/Scene.hpp>
#include <scene/VisualSceneInstance.hpp>
#include <scene/transformation/Transformation.hpp>
#endif
