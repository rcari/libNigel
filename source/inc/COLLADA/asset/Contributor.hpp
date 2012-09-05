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

#include <QtCore/QUrl>

#include <COLLADA/Element.hpp>

namespace Nigel { namespace COLLADA { namespace asset {

class NigelExport Contributor : public Nigel::COLLADA::Element
{
	Q_OBJECT

	Q_PROPERTY( QString author READ author WRITE author NOTIFY authorChanged STORED true DESIGNABLE true )

	Q_PROPERTY( QString email READ email WRITE email NOTIFY emailChanged STORED true DESIGNABLE true )

	Q_PROPERTY( QUrl website READ website WRITE website NOTIFY websiteChanged STORED true DESIGNABLE true )

	Q_PROPERTY( QString authoringToolDisplay READ authoringTool STORED false DESIGNABLE true )
	Q_PROPERTY( QString authoringTool READ authoringTool WRITE authoringTool STORED true DESIGNABLE false )

	Q_PROPERTY( QString comments READ comments WRITE comments NOTIFY commentsChanged STORED true DESIGNABLE true )

	Q_PROPERTY( QString copyright READ copyright WRITE copyright NOTIFY copyrightChanged STORED true DESIGNABLE true )

	Q_PROPERTY( QString sourceData READ sourceData WRITE sourceData NOTIFY sourceDataChanged STORED true DESIGNABLE true )

	K_BLOCK


protected:
	Contributor();

	virtual void library(Kore::data::Library* lib);

public:
	void author(const QString& author);
	const QString& author() const;
signals:
	void authorChanged(const QString& newAuthor);

public:
	void email(const QString& email);
	const QString& email() const;
signals:
	void emailChanged(const QString& newEmail);

public:
	void website(const QUrl& website);
	const QUrl& website() const;
signals:
	void websiteChanged(const QUrl& url);

public:
	void authoringTool(const QString& authoringTool);
	const QString& authoringTool() const;

public:
	void comments(const QString& comments);
	const QString& comments() const;
signals:
	void commentsChanged(const QString& newComments);

public:
	void copyright(const QString& copyright);
	const QString& copyright() const;
signals:
	void copyrightChanged(const QString& newCopyright);

public:
	void sourceData(const QString& sourceData);
	const QString& sourceData() const;
signals:
	void sourceDataChanged(const QString& newSourceData);

public:
	void initialize();

private:
	static QVariant BlockProperties(kint property);

private:
	QString		_author;
	QString		_email;
	QUrl		_website;
	QString		_authoringTool;
	QString		_comments;
	QString		_copyright;
	QString		_sourceData;
};

}}}

#ifdef NIGEL_MSVC
#include <COLLADA/extra/Extra.hpp>
#endif
