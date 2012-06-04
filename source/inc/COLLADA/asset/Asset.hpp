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

#pragma once

#include <NigelExport.hpp>

#include <QtCore/QDateTime>
#include <QtCore/QStringList>

#include <data/Library.hpp>

#include <COLLADA/Element.hpp>
#include <COLLADA/ICollection.hpp>
#include <COLLADA/extra/IExtrasCollection.hpp>

namespace Nigel { namespace COLLADA {

class Instance;
class InstancesManager;

namespace asset {

class Contributor;

/*!
 * @class Asset
 *
 * This class is equal to an asset from COLLADA documentation
 */
class NigelExport Asset
:	public Nigel::COLLADA::Element,
 	public Nigel::COLLADA::ICollection<Contributor>,
 	public Nigel::COLLADA::extra::IExtrasCollection
{
	Q_OBJECT

	Q_PROPERTY(QDateTime createdDateDisplay READ createdDateDisplay STORED false DESIGNABLE true)
	Q_PROPERTY(QDateTime createdDate READ createdDate WRITE createdDate STORED true DESIGNABLE false)

	Q_PROPERTY(QDateTime modifiedDateDisplay READ modifiedDateDisplay NOTIFY modifiedDateChanged STORED false DESIGNABLE true)
	Q_PROPERTY(QDateTime modifiedDate READ modifiedDate WRITE modifiedDate STORED true DESIGNABLE false)

	Q_PROPERTY(QString revision READ revision WRITE revision NOTIFY revisionChanged STORED true DESIGNABLE true)

	Q_PROPERTY(QStringList keywords READ keywords WRITE keywords NOTIFY keywordsChanged STORED true DESIGNABLE true)

	Q_PROPERTY(QString subject READ subject WRITE subject NOTIFY subjectChanged STORED true DESIGNABLE true)

	Q_PROPERTY(QString title READ title WRITE title NOTIFY titleChanged STORED true DESIGNABLE true)

	Q_PROPERTY(QString unitName READ unitName WRITE unitName NOTIFY unitNameChanged STORED true DESIGNABLE true)

	Q_PROPERTY(float unitValue READ unitValue WRITE unitValue NOTIFY unitValueChanged STORED true DESIGNABLE true)

	Q_PROPERTY(int upAxis READ upAxis WRITE upAxisInt STORED true DESIGNABLE false)

	K_BLOCK

	friend class Contributor;

public:
	/*!
	 * @enum	UpAxis.
	 *
	 * The different axis that can be used as reference.
	 */
	enum UpAxis
	{
		X_UP = 0,	//!< The X axis is the reference.
		Y_UP,		//!< The Y axis is the reference.
		Z_UP,		//!< The Z axis is the reference.
	};

	/*!
	 * @enum	AltitudeMode.
	 *
	 * The different altitude modes used to calculate coordinates.
	 */
	enum AltitudeMode
	{
		RelativeToGround,	//!< All coordinates are relative to the ground.
		Absolute,			//!< All coordinates are absolute.
	};

private:
	/*!
	 * @brief	Default constructor.
	 *
	 * This default constructor is protected as a Asset should not be instantiated as-is but rather sub-classed.
	 */
	Asset();

protected:
	/*!
	 * @property	Asset::library
	 *
	 * The library is the parent node of this Block.
	 */
	virtual void library(Kore::data::Library* lib);

private:
	/*!
	 * @property	Asset::createdDate
	 *
	 * The created date is the date of this Asset creation.
	 */
	void createdDate(const QDateTime& date);
	const QDateTime& createdDate() const;
	QDateTime createdDateDisplay() const;

public:
	/*!
	 * @property	Asset::modifiedDate
	 *
	 * The modified date is the date of the modification on this Asset.
	 */
	void modifiedDate(const QDateTime& date);
private:
	const QDateTime& modifiedDate() const;
	QDateTime modifiedDateDisplay() const;

	/*!
	 * @property	Asset::keywords
	 *
	 * Some keyboards associated to the Asset.
	 */
	void keywords(const QStringList& keywords);
	const QStringList& keywords() const;

	/*!
	 * @property	Asset::revision
	 *
	 * Revision of the Asset.
	 */
	void revision(const QString& revison);
	const QString& revision() const;

	/*!
	 * @property	Asset::subject
	 *
	 * Subject of the Asset.
	 */
	void subject(const QString& subject);
	const QString& subject() const;

	/*!
	 * @property	Asset::title
	 *
	 * Title of the Asset.
	 */
	void title(const QString& title);
	const QString& title() const;

	/*!
	 * @property	Asset::unitName
	 *
	 * Type of the unit used by the Asset for the coordinates.
	 */
	void unitName(const QString& name);
	const QString& unitName() const;

	/*!
	 * @property	Asset::unitValue
	 *
	 * Value of the unit used by the Asset for the coordinates.
	 */
	void unitValue(kfloat value);
	kfloat unitValue() const;

	/*!
	 * @property	Asset::upAxis
	 *
	 * Axis used by the Asset for the coordinates.
	 */
	void upAxis(UpAxis upAxis);
	UpAxis upAxis() const;

	/*!
	 * @property	Asset::longitude
	 *
	 * Longitude where the Asset was set.
	 */
	void longitude(kfloat longitude);
	kfloat longitude() const;

	/*!
	 * @property	Asset::latitude
	 *
	 * Latitude where the Asset was set.
	 */
	void latitude(kfloat latitude);
	kfloat latitude() const;

	/*!
	 * @property	Asset::altitudeValue
	 *
	 * Altitude where the Asset was set.
	 */
	void altitudeValue(kfloat altitude);
	kfloat altitudeValue() const;

	/*!
	 * @property	Asset::altitudeMode
	 *
	 * Altitude mode used the Asset.
	 */
	void altitudeMode(AltitudeMode mode);
	AltitudeMode altitudeMode() const;

signals:
	void modifiedDateChanged(const QDateTime& date);
	void keywordsChanged(const QStringList&);
	void revisionChanged(const QString&);
	void subjectChanged(const QString&);
	void titleChanged(const QString&);
	void unitNameChanged(const QString&);
	void unitValueChanged(kfloat);

public:
	void initialize();
	virtual Kore::data::Library* toLibrary() { return this; }
	virtual Nigel::COLLADA::Element* toElement() { return this; }
	virtual Nigel::COLLADA::extra::IExtrasCollection* toExtrasCollection() { return this; }

protected:
	virtual kint elementsOffset(Contributor*) const;
	virtual void notifyElementRegistered(Contributor*);
	virtual kint elementsOffset(Nigel::COLLADA::extra::Extra*) const;

private:
	void upAxisInt(int);
	static QVariant ElementProperty(kint property);

private:
	QDateTime	_createdDate;
	QDateTime	_modifiedDate;
	QStringList	_keywords;
	QString		_revision;
	QString		_subject;
	QString		_title;
	QString		_unitName;
	kfloat		_unitValue;
	UpAxis		_upAxis;
	kfloat		_longitude;
	kfloat		_latitude;
	kfloat		_altitudeValue;
	AltitudeMode	_altitudeMode;
};

}}}

#ifdef NIGEL_MSVC
#include <COLLADA/asset/Contributor.hpp>
#include <COLLADA/extra/Extra.hpp>
#endif
