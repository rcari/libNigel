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

#include "../ScopedElement.hpp"

namespace Nigel { namespace COLLADA { namespace instantiation {

class NigelExport ElementInstance : public Nigel::COLLADA::ScopedElement
{
	Q_OBJECT
	Q_PROPERTY( QString instanceName READ instanceName NOTIFY resolved STORED false DESIGNABLE false USER true )
	Q_PROPERTY( QString url READ url WRITE url STORED true DESIGNABLE false )

	K_BLOCK

protected:
	ElementInstance();

	virtual void library(Kore::data::Library* lib) = K_NULL;

public:
	kbool isInstanceResolved() const;
	Nigel::COLLADA::IUniqueElement* instantiatedElement();
	virtual void instanceChanged(Nigel::COLLADA::DocumentInstance* instance);

public:
	virtual QString instanceName() const;

	template<typename T>
	static T* CreateElementInstance(Nigel::COLLADA::IUniqueElement* element);

private:
	void privateInstantiatedElement(Nigel::COLLADA::IUniqueElement* element);

private:
	QString url() const;
	void url(const QString& url);
	void resolve(kbool lazy);

signals:
	void resolved();

private:
	Nigel::COLLADA::IUniqueElement* _instantiatedElement;
	QMetaProperty _instantiatedElementUserMetaProperty;
	QString _url;

};

template<typename T>
class ElementInstanceT : public ElementInstance
{
protected:
	ElementInstanceT();

public:
	T* instantiatedElement();
	const T* instantiatedElement() const;
};

}}}

#include <src/COLLADA/instantiation/ElementInstance.cxx>

#ifdef NIGEL_MSVC
#include <camera/CameraInstance.hpp>
#include <COLLADA/extra/Extra.hpp>
#include <geometry/GeometricElement.hpp>
#include <geometry/Geometry.hpp>
#include <lighting/LightInstance.hpp>
#include <scene/Node.hpp>
#include <scene/NodeInstance.hpp>
#include <scene/Scene.hpp>
#include <scene/VisualSceneInstance.hpp>
#include <scene/transformation/Transformation.hpp>
#endif
