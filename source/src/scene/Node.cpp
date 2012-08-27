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

#include <scene/Node.hpp>
#include <scene/NodeInstance.hpp>
using namespace Nigel::scene;

#include <camera/CameraInstance.hpp>
using namespace Nigel::camera;
using namespace Nigel::COLLADA;
using namespace Nigel::COLLADA::extra;

#include <geometry/GeometryInstance.hpp>
using namespace Nigel::geometry;

#include <lighting/LightInstance.hpp>
using namespace Nigel::lighting;

#include <scene/transformation/Transformation.hpp>
using namespace Nigel::scene::transformation;

using namespace Kore::data;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::scene::Node
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/scene.node.png")
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_METHOD( Node::ElementProperty )
K_BLOCK_END

Node::Node()
:	_enabled(true)
{
	blockName(tr("Scene Node"));
	connect(this, SIGNAL(blockNameChanged(const QString&)), SIGNAL(nodeNameChanged(const QString&)));
}

void Node::library(Library* library)
{
	if(hasParent())
	{
		parent<INodesCollection>()->unregisterElement(this);
	}
	unregisterWithScope<Node>();
	UniqueElement::library(library);
	registerWithScope<Node>();
	if(hasParent())
	{
		parent<INodesCollection>()->registerElement(this);
	}
}

kint Node::transformationsNb() const
{
	return Nigel::COLLADA::ICollection<Transformation>::elementsNb();
}

Transformation* Node::transformation(kint i)
{
	return Nigel::COLLADA::ICollection<Transformation>::element<Transformation>(i);
}

kint Node::nodeInstancesNb() const
{
	return Nigel::COLLADA::ICollection<NodeInstance>::elementsNb();
}

NodeInstance* Node::nodeInstance(kint i)
{
	return Nigel::COLLADA::ICollection<NodeInstance>::element<NodeInstance>(i);
}

kint Node::cameraInstancesNb() const
{
	return Nigel::COLLADA::ICollection<CameraInstance>::elementsNb();
}

CameraInstance* Node::cameraInstance(kint i)
{
	return Nigel::COLLADA::ICollection<CameraInstance>::element<CameraInstance>(i);
}

kint Node::lightInstancesNb() const
{
	return Nigel::COLLADA::ICollection<LightInstance>::elementsNb();
}

LightInstance* Node::lightInstance(kint i)
{
	return Nigel::COLLADA::ICollection<LightInstance>::element<LightInstance>(i);
}

kbool Node::enabled() const
{
	return _enabled;
}

void Node::enabled(kbool b)
{
	_enabled = b;
	emit enabledChanged(b);
	emit elementChanged();
}

kint Node::elementsOffset(Transformation*) const
{
	return IAssetOwner::nextIndex();
}

void Node::notifyElementRegistered(Transformation* transformation)
{
	emit elementAdded(transformation);
}

kint Node::elementsOffset(CameraInstance*) const
{
	return Nigel::COLLADA::ICollection<Transformation>::nextIndex();
}

void Node::notifyElementRegistered(CameraInstance* camera)
{
	emit elementAdded(camera);
}

kint Node::elementsOffset(Nigel::geometry::GeometryInstance*) const
{
	return Nigel::COLLADA::ICollection<CameraInstance>::nextIndex();
}

kint Node::elementsOffset(LightInstance*) const
{
	return IGeometryInstancesCollection::nextIndex();
}

void Node::notifyElementRegistered(Nigel::lighting::LightInstance* light)
{
	emit elementAdded(light);
}

kint Node::elementsOffset(NodeInstance*) const
{
	return Nigel::COLLADA::ICollection<LightInstance>::nextIndex();
}

void Node::notifyElementRegistered(NodeInstance* node)
{
	emit elementAdded(node);
}

kint Node::elementsOffset(Node*) const
{
	return Nigel::COLLADA::ICollection<NodeInstance>::nextIndex();
}

kint Node::elementsOffset(Extra*) const
{
	return Nigel::COLLADA::ICollection<Node>::nextIndex();
}

QVariant Node::ElementProperty(kint property)
{
	switch(property)
	{
	case Block::BlockTypeName:
		return QString(tr("Scene Node"));
	case Block::BlockPropertiesName:
		{
			QHash<QString,QVariant> propertiesName;
			propertiesName.insert("nodeEnabled", tr("Active"));
			propertiesName.insert("nodeName", tr("Name"));
			return propertiesName;
		}
	default:
		return QVariant();
	}
}
