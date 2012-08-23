/*
 * 	Copyright (c) 2010-2011, Christophe EVENO
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

#include <COLLADA/asset/Asset.hpp>
#include <COLLADA/asset/Contributor.hpp>
#include <COLLADA/asset/IAssetOwner.hpp>
using namespace Nigel::COLLADA::asset;

#include <COLLADA/extra/Extra.hpp>
using namespace Nigel::COLLADA::extra;

#include <COLLADA/Element.hpp>
using namespace Nigel::COLLADA;

using namespace Kore::data;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::COLLADA::asset::Asset
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/asset.png")
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_METHOD( Asset::ElementProperty )
K_BLOCK_END

#include <QtCore/QtDebug>

Asset::Asset()
:	_unitName("Meter"),
 	_unitValue(1.0f),
 	_upAxis(Y_UP),
 	_longitude(0.0f),
 	_latitude(0.0f),
 	_altitudeValue(0.0f),
 	_altitudeMode(Absolute)
{
	blockName(tr("Asset"));
	addFlag(Block::SystemOwned);
	// TODO: Prefill the asset information with the current user data !
}

void Asset::initialize()
{
	Block::initialize();

	// Set the current datetime to now (UTC) by default.
	createdDate(QDateTime::currentDateTimeUtc());

	Contributor* contributor = K_BLOCK_CREATE_INSTANCE( Contributor );
	contributor->initialize();
	addBlock(contributor);
}

void Asset::library(Kore::data::Library* lib)
{
	IAssetOwner* owner = K_NULL;
	if(Library::library())
	{
		owner = static_cast<Element*>(Library::library())->toAssetOwner();
		K_ASSERT( owner )
		owner->asset(K_NULL);
	}
	Library::library(lib);
	if(lib)
	{
		owner = static_cast<Element*>(lib)->toAssetOwner();
		K_ASSERT( owner )
		owner->asset(this);
	}
}

void Asset::createdDate(const QDateTime& date)
{
	_createdDate = date;
	emit createdDateChanged(date);
}

const QDateTime& Asset::createdDate() const
{
	return _createdDate;
}

QDateTime Asset::createdDateDisplay() const
{
	return _createdDate.toLocalTime();
}

void Asset::modifiedDate(const QDateTime& date)
{
	_modifiedDate = date;
	emit modifiedDateChanged(date);
}

const QDateTime& Asset::modifiedDate() const
{
	return _modifiedDate;
}

QDateTime Asset::modifiedDateDisplay() const
{
	return _modifiedDate.toLocalTime();
}

void Asset::keywords(const QStringList& keywords)
{
	_keywords = keywords;
	emit keywordsChanged(_keywords);
}

const QStringList& Asset::keywords() const
{
	return _keywords;
}

void Asset::revision(const QString& revision)
{
	_revision = revision;
	emit revisionChanged(revision);
}

const QString& Asset::revision() const
{
	return _revision;
}

void Asset::subject(const QString& subject)
{
	_subject = subject;
	emit subjectChanged(subject);
}

const QString& Asset::subject() const
{
	return _subject;
}

void Asset::title(const QString& title)
{
	_title = title;
	emit titleChanged(title);
}

const QString& Asset::title() const
{
	return _title;
}

void Asset::unitName(const QString& name)
{
	_unitName = name;
	emit unitNameChanged(name);
}

const QString& Asset::unitName() const
{
	return _unitName;
}

void Asset::unitValue(kfloat value)
{
	_unitValue = value;
	emit unitValueChanged(value);
}

kfloat Asset::unitValue() const
{
	return _unitValue;
}

void Asset::upAxis(UpAxis upAxis)
{
	_upAxis = upAxis;
	emit upAxisChanged(upAxis);
}

Asset::UpAxis Asset::upAxis() const
{
	return _upAxis;
}

void Asset::longitude(kfloat longitude)
{
	_longitude = longitude;
	emit longitudeChanged(longitude);
}

kfloat Asset::longitude() const
{
	return _longitude;
}

void Asset::latitude(kfloat latitude)
{
	_latitude = latitude;
	emit latitudeChanged(latitude);
}

kfloat Asset::latitude() const
{
	return _latitude;
}

void Asset::altitudeValue(kfloat altitude)
{
	_altitudeValue = altitude;
	emit altitudeValueChanged(altitude);
}

kfloat Asset::altitudeValue() const
{
	return _altitudeValue;
}

void Asset::altitudeMode(AltitudeMode mode)
{
	_altitudeMode = mode;
	emit altitudeModeChanged(mode);
}

Asset::AltitudeMode Asset::altitudeMode() const
{
	return _altitudeMode;
}

kint Asset::elementsOffset(Contributor*) const
{
	return 0;
}

void Asset::notifyElementRegistered(Contributor* contributor)
{
	emit elementAdded(contributor);
}

kint Asset::elementsOffset(Nigel::COLLADA::extra::Extra*) const
{
	return Nigel::COLLADA::ICollection<Contributor>::nextIndex();
}

QVariant Asset::ElementProperty(kint property)
{
	switch(property)
	{
	case Block::BlockTypeName:
		return tr("Asset");
	case Block::BlockPropertiesName:
		{
			QHash<QString,QVariant> propertiesName;
			propertiesName.insert("createdDateDisplay", tr("Created"));
			propertiesName.insert("modifiedDateDisplay", tr("Last modified"));
			propertiesName.insert("keywords", tr("Keywords"));
			propertiesName.insert("revision", tr("Revision"));
			propertiesName.insert("subject", tr("Subject"));
			propertiesName.insert("title", tr("Title"));
			propertiesName.insert("unitName", tr("Distance unit"));
			propertiesName.insert("unitValue", tr("Unit value (m)"));
			return propertiesName;
		}
	default:
		return QVariant();
	}
}
