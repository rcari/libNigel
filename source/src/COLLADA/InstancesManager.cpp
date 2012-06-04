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

#include <COLLADA/InstancesManager.hpp>
#include <COLLADA/DocumentInstance.hpp>
#include <COLLADA/Element.hpp>
#include <COLLADA/IUniqueElement.hpp>
using namespace Nigel::COLLADA;
using namespace Kore::data;

#define K_BLOCK_TYPE Nigel::COLLADA::InstancesManager
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END
using namespace Kore;

InstancesManager::InstancesManager()
:	_rootInstance(K_NULL)
{
	addFlag(SystemOwned);
}

void InstancesManager::library(Library* lib)
{
	Library::library(lib); // Can't use the Element implementation which expects an Element as a parent !
}

bool InstancesManager::loadRootInstance(QString path)
{
	if(_rootInstance)
	{
		qWarning("%s / The manager already has a root instance !", qPrintable(objectClassName()));
		return false;
	}

	QFileInfo rootFile(path);

	// Load the root document instance.
	_rootInstance = loadInstance(rootFile);
	if(!_rootInstance)
	{
		return false;
	}

	// Store the root folder. (FS Caching, no need to instantiate a QDir !)
	_rootFolder = rootFile.dir();

	return true;
}

bool InstancesManager::setRootInstance(DocumentInstance* instance, kbool save)
{
	if(_rootInstance)
	{
		qWarning("%s / The manager already has a root instance !", qPrintable(objectClassName()));
		return false;
	}

	_rootInstance = instance;

	addBlock(_rootInstance);

	_rootFolder = _rootInstance->fileInfo().dir();

	if(save)
	{
		saveInstance(_rootInstance);
	}

	return true;
}

Nigel::COLLADA::DocumentInstance* InstancesManager::rootInstance()
{
	return _rootInstance;
}

const Nigel::COLLADA::DocumentInstance* InstancesManager::rootInstance() const
{
	return _rootInstance;
}

QString InstancesManager::url(const Element* element, const IUniqueElement* uniqueElement) const
{
	if(uniqueElement->id().isNull())
	{
		qWarning("Requested URL for UniqueElement without an ID !!");
		return QString(); // No VALID ID !
	}

	QString result;

	const DocumentInstance* elementInstance = element->instance();
	const DocumentInstance* uniqueElementInstance = uniqueElement->instance();

	if(elementInstance != uniqueElementInstance)
	{
		// Retrieve the relative path.
		result = elementInstance->fileInfo().dir().relativeFilePath(
				uniqueElementInstance->fileInfo().absoluteFilePath()
			);
	}

	result.append("#"); // The separator.
	result.append(uniqueElement->id().toString());

	return result;
}

IUniqueElement* InstancesManager::resolveUrl(Element* element, const QString& url, kbool lazy)
{
	int splitIndex = url.indexOf('#');
	QString id = url.mid( splitIndex + 1 );

	if(splitIndex == 0)
	{
		// Same instance, get outta here early !
		return element->instance()->elementById(QUuid(id));
	}

	QString localPath = _rootFolder.relativeFilePath(
			element->instance()->fileInfo().dir().absoluteFilePath( url.left(splitIndex) )
		);

	// Return the Instance for the localPath
	DocumentInstance* instance = _instances.value(localPath, K_NULL);
	if(instance == K_NULL) // Could not find this specific instance, it was not loaded.
	{
		if(lazy) // This was a lazy resolve request, no need to process this further !
		{
			return K_NULL;
		}

		// Try to load the DocumentInstance for the url.
		instance = loadInstance(QFileInfo(_rootFolder, localPath));
		if(instance == K_NULL) // Could not find/load this instance file, this is serious !
		{
			KoreEngine::Error(
					tr("URL Resolution error"),
					tr("The following URL could not be resolved: %1#%2").arg(localPath).arg(id)
				);
			return K_NULL;
		}
	}

	return instance->elementById(QUuid(id));
}

QString InstancesManager::rootInstancePath() const
{
	return _rootInstance->fileInfo().absoluteFilePath();
}

void InstancesManager::registerDocumentInstance(DocumentInstance* instance)
{
	_instances.insert(_rootFolder.relativeFilePath(instance->fileInfo().absoluteFilePath()), instance);
}

void InstancesManager::unregisterDocumentInstance(DocumentInstance* instance)
{
	_instances.remove(_rootFolder.relativeFilePath(instance->fileInfo().absoluteFilePath()));
}

DocumentInstance* InstancesManager::loadInstance(const QFileInfo& file)
{
	DocumentInstance* instance = DocumentInstance::LoadDocumentInstance(file.absoluteFilePath());

	if(instance)
	{
		// Add the block to this manager -> Default action.
		addBlock(instance);
	}

	return instance;
}

void InstancesManager::saveInstance(const DocumentInstance* instance) const
{
	DocumentInstance::SaveDocumentInstance(instance);
}

DocumentInstance* InstancesManager::instance()
{
	return _rootInstance;
}
