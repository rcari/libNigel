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

#include <COLLADA/DocumentInstance.hpp>
#include <COLLADA/DocumentInstanceReference.hpp>
#include <COLLADA/InstancesManager.hpp>
using namespace Nigel::COLLADA;
using namespace Nigel::COLLADA::asset;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::COLLADA::DocumentInstanceReference
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_METHOD( DocumentInstanceReference::ElementProperty )
K_BLOCK_END

DocumentInstanceReference::DocumentInstanceReference()
:	_instance(K_NULL),
 	_alwaysLoad(false)
{
	addFlag(Block::SystemOwned);
}

DocumentInstanceReference* DocumentInstanceReference::CreateDocumentInstanceReference(IElement* relativeTo, DocumentInstance* instance)
{
	DocumentInstanceReference* ref = K_BLOCK_CREATE_INSTANCE( DocumentInstanceReference );
	// Set the reference
	ref->reference(relativeTo, instance);
	// Return the result.
	return ref;
}

kbool DocumentInstanceReference::isReferenceResolved() const
{
	return !_instance.isNull();
}

DocumentInstance* DocumentInstanceReference::reference()
{
	if(_instance.isNull())
	{
		K_ASSERT( instance() )
		K_ASSERT( instance()->manager() )
		_instance = instance()->manager()->loadInstance(referenceFileInfo());
	}

	return _instance;
}

QString DocumentInstanceReference::blockName() const
{
	return tr("Reference: %1").arg(_refPath);
}

void DocumentInstanceReference::reference(IElement* relativeTo, DocumentInstance* instance)
{
	K_ASSERT( _instance.isNull() )

	_instance = instance;

	// Compute the relative path.
	QDir dir = relativeTo->instance()->fileInfo().dir();
	_refPath = dir.relativeFilePath(_instance->fileInfo().absoluteFilePath());
}

kint DocumentInstanceReference::elementIndex(Asset*) const
{
	return 0;
}

QString DocumentInstanceReference::refPath() const
{
	return _refPath;
}

void DocumentInstanceReference::instanceChanged(DocumentInstance* instance)
{
	Extra::instanceChanged(instance);
	if(_instance.isNull() && _alwaysLoad && instance->manager())
	{
		// Resolve !
		reference();
	}
}

void DocumentInstanceReference::refPath(const QString& path)
{
	_refPath = path;
}

QFileInfo DocumentInstanceReference::referenceFileInfo()
{
	QDir directory = instance()->fileInfo().dir();
	return QFileInfo(directory.absoluteFilePath(_refPath));
}

void DocumentInstanceReference::alwaysLoad(kbool load)
{
	if(_alwaysLoad != load)
	{
		_alwaysLoad = load;
		if(instance() != K_NULL && _alwaysLoad)
		{
			reference();
		}
		emit alwaysLoadChanged(_alwaysLoad);
	}
}

kbool DocumentInstanceReference::alwaysLoad() const
{
	return _alwaysLoad;
}

QVariant DocumentInstanceReference::ElementProperty(kint property)
{
	switch(property)
	{
	case Block::BlockTypeName:
		return QString(tr("Document Instance reference"));
	case Block::BlockPropertiesName:
		{
			QHash<QString,QVariant> propertiesName;
			propertiesName.insert("alwaysLoad", tr("Always load"));
			return propertiesName;
		}
	default:
		return QVariant();
	}
}
