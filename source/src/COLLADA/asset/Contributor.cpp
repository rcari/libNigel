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

#include <COLLADA/asset/Contributor.hpp>
#include <COLLADA/asset/Asset.hpp>
using namespace Nigel::COLLADA::asset;

#include <data/BlockSettings.hpp>

#include <QtCore/QCoreApplication>

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::COLLADA::asset::Contributor
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_METHOD( Nigel::COLLADA::asset::Contributor::BlockProperties )
K_BLOCK_END

Contributor::Contributor()
{
	blockName(tr("Contributor"));
	addFlag(Block::SystemOwned);
}

void Contributor::library(Kore::data::Library* lib)
{
	if(hasParent())
	{
		parent<Asset>()->Nigel::COLLADA::ICollection<Contributor>::unregisterElement(this);
	}
	Element::library(lib);
	if(lib)
	{
		parent<Asset>()->Nigel::COLLADA::ICollection<Contributor>::registerElement(this);
	}
}

void Contributor::author(const QString& author)
{
	_author = author;
	emit authorChanged(author);
}

const QString& Contributor::author() const
{
	return _author;
}

void Contributor::email(const QString& email)
{
	_email = email;
	emit emailChanged(email);
}

const QString& Contributor::email() const
{
	return _email;
}

void Contributor::website(const QUrl& website)
{
	_website = website;
	emit websiteChanged(website);
}

const QUrl& Contributor::website() const
{
	return _website;
}

void Contributor::authoringTool(const QString& authoringTool)
{
	_authoringTool = authoringTool;
}

const QString& Contributor::authoringTool() const
{
	return _authoringTool;
}

void Contributor::comments(const QString& comments)
{
	_comments = comments;
	emit commentsChanged(comments);
}

const QString& Contributor::comments() const
{
	return _comments;
}

void Contributor::copyright(const QString& copyright)
{
	_copyright = copyright;
	emit copyrightChanged(copyright);
}

const QString& Contributor::copyright() const
{
	return _copyright;
}

void Contributor::sourceData(const QString& sourceData)
{
	_sourceData = sourceData;
	emit sourceDataChanged(sourceData);
}

const QString& Contributor::sourceData() const
{
	return _sourceData;
}

void Contributor::initialize()
{
	_author = metaBlock()->blockSetting("author", QString()).toString();
	_email = metaBlock()->blockSetting("email", QString()).toString();
	_website = metaBlock()->blockSetting("website", QString()).toString();
	_authoringTool = QString("%1 %2").arg(qApp->applicationName(), qApp->applicationVersion());
	_copyright = metaBlock()->blockSetting("copyright", QString()).toString();
}

QVariant Contributor::BlockProperties(kint property)
{
	switch(property)
	{
	case Block::BlockTypeName:
		return tr("Contributor");
	case Block::BlockSettings:
		{
			// Author
			QVariantMap author;
			author.insert(K_BLOCK_SETTING_DEFAULT,	QString());
			author.insert(K_BLOCK_SETTING_TEXT,		tr("Author"));

			// email
			QVariantMap email;
			email.insert(K_BLOCK_SETTING_DEFAULT, 	QString());
			email.insert(K_BLOCK_SETTING_TEXT,		tr("email"));

			// Web site
			QVariantMap website;
			website.insert(K_BLOCK_SETTING_DEFAULT,	QString("http://"));
			website.insert(K_BLOCK_SETTING_TEXT,	tr("Website"));

			// Copyright
			QVariantMap copyright;
			copyright.insert(K_BLOCK_SETTING_DEFAULT,	QString());
			copyright.insert(K_BLOCK_SETTING_TEXT,		tr("Copyright"));

			// Global settings structure
			QVariantMap settings;
			settings.insert("author",		author);
			settings.insert("email",		email);
			settings.insert("website",		website);
			settings.insert("copyright",	copyright);

			return settings;
		}
	case Block::BlockPropertiesName:
		{
			QHash<QString,QVariant> propertiesName;
			propertiesName.insert("author",					tr("Author"));
			propertiesName.insert("email",					tr("e-mail"));
			propertiesName.insert("website",				tr("Web site"));
			propertiesName.insert("authoringToolDisplay",	tr("Authoring tool"));
			propertiesName.insert("comments",				tr("Comments"));
			propertiesName.insert("copyright",				tr("Copyright"));
			propertiesName.insert("sourceData",				tr("Source data"));

			return propertiesName;
		}
	default:
		return QVariant();
	}
}
