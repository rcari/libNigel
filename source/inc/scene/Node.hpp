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

#include "INodesCollection.hpp"
#include "../COLLADA/ICollection.hpp"
#include "../COLLADA/IScopedElement.hpp"
#include "../COLLADA/extra/IExtrasCollection.hpp"
#include "../geometry/IGeometryInstancesCollection.hpp"

namespace Nigel {

namespace camera { class CameraInstance; }
namespace lighting { class LightInstance; }

namespace scene {

class NodeInstance;

namespace transformation { class Transformation; }

class NigelExport Node
:	public INodesCollection,
 	public Nigel::COLLADA::IScopedElement,
 	public Nigel::COLLADA::ICollection<transformation::Transformation>,
 	public Nigel::COLLADA::ICollection<Nigel::camera::CameraInstance>,
 	public Nigel::geometry::IGeometryInstancesCollection,
 	public Nigel::COLLADA::ICollection<Nigel::lighting::LightInstance>,
 	public Nigel::COLLADA::ICollection<NodeInstance>,
 	public Nigel::COLLADA::extra::IExtrasCollection
{
	Q_OBJECT
	Q_PROPERTY( bool nodeEnabled READ enabled WRITE enabled NOTIFY enabledChanged DESIGNABLE true STORED true )
	Q_PROPERTY( QString nodeName READ blockName WRITE blockName NOTIFY nodeNameChanged DESIGNABLE true STORED true )

	K_BLOCK

	friend class NodeInstance;
	friend class Nigel::camera::CameraInstance;
	friend class Nigel::lighting::LightInstance;
	friend class Nigel::scene::transformation::Transformation;

protected:
	Node();

	virtual void library(Library* library);

public:
	kint transformationsNb() const;
	transformation::Transformation* transformation(kint i);

	kint nodeInstancesNb() const;
	NodeInstance* nodeInstance(kint i);

	kint cameraInstancesNb() const;
	Nigel::camera::CameraInstance* cameraInstance(kint i);

	kint lightInstancesNb() const;
	Nigel::lighting::LightInstance* lightInstance(kint i);

	kbool enabled() const;
	void enabled(kbool b);
signals:
	void enabledChanged(kbool k);
	void nodeNameChanged(const QString&);

public:
	virtual Kore::data::Library* toLibrary() { return this; }
	virtual Element* toElement() { return this; }
	virtual IScopedElement* toScopedElement() { return this; }
	virtual IUniqueElement* toUniqueElement() { return this; }
	virtual IGeometryInstancesCollection* toGeometryInstancesCollection() { return this; }
	virtual IExtrasCollection* toExtrasCollection() { return this; }

protected:
	virtual kint elementsOffset(transformation::Transformation*) const;
	virtual void notifyElementRegistered(transformation::Transformation*);

	virtual kint elementsOffset(Nigel::camera::CameraInstance*) const;
	virtual void notifyElementRegistered(Nigel::camera::CameraInstance*);

	virtual kint elementsOffset(Nigel::geometry::GeometryInstance*) const;

	virtual kint elementsOffset(Nigel::lighting::LightInstance*) const;
	virtual void notifyElementRegistered(Nigel::lighting::LightInstance*);

	virtual kint elementsOffset(NodeInstance*) const;
	virtual void notifyElementRegistered(NodeInstance*);

	virtual kint elementsOffset(Node*) const;

	virtual kint elementsOffset(Nigel::COLLADA::extra::Extra*) const;

private:
	static QVariant ElementProperty(kint property);

private:
	kbool _enabled;

};

}}
