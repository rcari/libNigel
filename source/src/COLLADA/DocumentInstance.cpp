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
#include <COLLADA/InstancesManager.hpp>
#include <COLLADA/IScopedElement.hpp>
#include <COLLADA/IUniqueElement.hpp>
using namespace Nigel::COLLADA;
using namespace Nigel::COLLADA::extra;

#include <serialization/Dumper.hpp>
#include <serialization/Loader.hpp>
using namespace Kore::serialization;

#include <scene/Scene.hpp>
using namespace Nigel::scene;

#include <KoreEngine.hpp>
using namespace Kore::data;
using namespace Kore;

#include <QtCore/QDir>
#include <QtCore/QtDebug>

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::COLLADA::DocumentInstance
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

// TODO: Deal with that... This sucks !
#define NIGEL_CURRENT_SUBPROFILE_VERSION 0x1

DocumentInstance::DocumentInstance()
{
	addFlag(Block::SystemOwned);
}

void DocumentInstance::library(Library* library)
{
	if(hasParent())
	{
		manager()->unregisterDocumentInstance(this);
	}
	Element::library(library);
	if(hasParent())
	{
		manager()->registerDocumentInstance(this);
		// Quick notification of the tree... Maybe some runtime resolutions are possible at this point.
		instanceChanged(this);
	}
}

InstancesManager* DocumentInstance::manager()
{
	return parent<InstancesManager>();
}

const InstancesManager* DocumentInstance::manager() const
{
	return parent<InstancesManager>();
}

void DocumentInstance::updateAsset()
{
	K_ASSERT( asset() )
	asset()->modifiedDate(QDateTime::currentDateTime().toUTC());
}

void DocumentInstance::version(DocumentInstance::Version v)
{
	_version = v;
}

DocumentInstance::Version DocumentInstance::version() const
{
	return _version;
}

Nigel::scene::Scene* DocumentInstance::scene()
{
	return Nigel::COLLADA::IOwner<Nigel::scene::Scene>::element();
}

DocumentInstance* DocumentInstance::instance()
{
	return this;
}

const QFileInfo& DocumentInstance::fileInfo() const
{
	return _fileInfo;
}

kbool DocumentInstance::hasId(const QString& id) const
{
	return _uniqueElements.contains(id);
}

IUniqueElement* DocumentInstance::elementById(const QUuid& id)
{
	return _uniqueElements.value(id, K_NULL);
}

const IUniqueElement* DocumentInstance::elementById(const QUuid& id) const
{
	return _uniqueElements.value(id, K_NULL);
}

QString DocumentInstance::sid(const IScopedElement* element) const
{
	if(element->sid().isEmpty())
	{
		qWarning("Requested SID for ScopedElement without a SID !!");
		return QString();
	}
	else if(element->scopeElement())
	{
		if( element->scopeElement()->instance() == this )
		{
			return QString("%1/%2").arg(element->scopeElement()->id()).arg(element->scopePath());
		}
	}
	return QString(); // WTF ?
}

QString DocumentInstance::infoString() const
{
	return _fileInfo.absoluteFilePath();
}

void DocumentInstance::addBlock(Block* b)
{
	Element::addBlock(b);
	static_cast<Element*>(b)->instanceChanged(this);
}

void DocumentInstance::removeBlock(Block* b)
{
	Element::removeBlock(b);
	static_cast<Element*>(b)->instanceChanged(K_NULL);
}

void DocumentInstance::insertBlock(Block* b, kint index)
{
	Element::insertBlock(b, index);
	static_cast<Element*>(b)->instanceChanged(this);
}

kint DocumentInstance::elementIndex(Scene*) const
{
	return IAssetOwner::nextIndex();
}

void DocumentInstance::notifyElementRegistered(Scene* scene)
{
	emit elementAdded(scene);
}

kint DocumentInstance::elementsOffset(Extra*) const
{
	return Nigel::COLLADA::IOwner<Scene>::nextIndex();
}

DocumentInstance* DocumentInstance::LoadDocumentInstance(const QString& absoluteFilePath, ProgressCallback* callback)
{
	const QFileInfo file(absoluteFilePath);

	qDebug() << "Nigel / Loading instance @" << file.absoluteFilePath();

	QFile device(file.absoluteFilePath());
	if(!device.open(QIODevice::ReadOnly))
	{
		qWarning() << "Nigel / Could not open file";
		KoreEngine::Error(
				tr("Could not load instance"),
				tr("The file %1 could not be opened.").arg(file.absoluteFilePath())
			);
		return K_NULL;
	}

	Loader loader(&device);
	if(!loader.isValid())
	{
		qWarning() << "Nigel / The file is not a valid Kore archive";
		KoreEngine::Error(
				tr("Invalid format"),
				tr("The file %1 is not a valid Kore archive.").arg(file.absoluteFilePath())
			);
		return K_NULL;
	}

	if(loader.header().subProfileSignature != K_FOURCC('N','G','E','L'))
	{
		qWarning() << "Nigel / The file is not a valid Nigel archive";
		KoreEngine::Error(
				tr("Invalid format"),
				tr("The file %1 is not a valid Nigel archive.").arg(file.absoluteFilePath())
			);
		return K_NULL;
	}

	if(loader.header().subProfileVersion > NIGEL_CURRENT_SUBPROFILE_VERSION)
	{
		qWarning() << "Nigel / The file was generated by a more recent version of Nigel.";
		KoreEngine::Error(
				tr("Unsupported format"),
				tr("The file %1 was a generated by a more recent version of Nigel.").arg(file.absoluteFilePath())
			);
		return K_NULL;
	}

	// Skip metadata.
	device.seek( device.pos() + loader.header().metaDataSize );

	Block* block = K_NULL;
	if(loader.inflater()->inflate(&device, &block, callback) == BlockInflater::Failed)
	{
		qWarning() << "Nigel / An error occurred while loading";
		KoreEngine::Error(
				tr("Stream error"),
				tr("An error occurred while loading %1, please see the logs for further information.").arg(file.absoluteFilePath())
			);

		if(block)
		{
			// Cleanup the allocated tree for the instance...
			block->destroy();
		}

		return K_NULL;
	}

	K_ASSERT( block->fastInherits<Nigel::COLLADA::DocumentInstance>() ) // Check we loaded an instance !

	qDebug() << "Nigel / Successfully loaded instance";

	DocumentInstance* instance = static_cast<DocumentInstance*>(block);

	// Set the instance's file info !
	instance->_fileInfo = file;

	// Return the loaded instance !
	return instance;
}

bool DocumentInstance::SaveDocumentInstance(const DocumentInstance* instance, const QString& filePath, ProgressCallback* callback)
{
	QFile device(
			filePath.isNull()
				?	instance->fileInfo().absoluteFilePath()
				:	filePath
		);

	if(!device.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		KoreEngine::Error(
				tr("Could not save instance"),
				tr("The file %1 could not be opened for writing.").arg(instance->fileInfo().absoluteFilePath())
			);
		return false;
	}

	FileHeader header;
	header.subProfileSignature = K_FOURCC('N','G','E','L');
	header.subProfileVersion = NIGEL_CURRENT_SUBPROFILE_VERSION;

	Dumper dumper(&device, header); // Dump the header !

	return dumper.deflater()->deflate(&device, instance, callback) == BlockDeflater::Success;
}

void DocumentInstance::registerUniqueElement(IUniqueElement* e)
{
	K_ASSERT( !e->id().isNull() )
	K_ASSERT( !hasId(e->id()) )
	_uniqueElements.insert(e->id(), e);
}

void DocumentInstance::unregisterUniqueElement(IUniqueElement* e)
{
	_uniqueElements.remove(e->id());
}
