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

#include <scene/Scene.hpp>
#include <scene/VisualSceneInstance.hpp>
using namespace Nigel::scene;

#include <COLLADA/DocumentInstance.hpp>
using namespace Nigel::COLLADA;
using namespace Nigel::COLLADA::instantiation;

using namespace Kore::data;

#define K_BLOCK_TYPE		Nigel::scene::Scene
#define K_BLOCK_SUPER_TYPE 	Nigel::COLLADA::Element
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Scene::Scene()
{
	blockName(tr("Instance Scene"));
}

void Scene::library(Library* lib)
{
	if(hasParent())
	{
		parent<DocumentInstance>()->Nigel::COLLADA::IOwner<Scene>::element(K_NULL);
	}
	Element::library(lib);
	if(hasParent())
	{
		parent<DocumentInstance>()->Nigel::COLLADA::IOwner<Scene>::element(this);
	}
}

VisualSceneInstance* Scene::visualSceneInstance()
{
	return IOwner<VisualSceneInstance>::element();
}

const VisualSceneInstance* Scene::visualSceneInstance() const
{
	return IOwner<VisualSceneInstance>::element();
}

kint Scene::elementIndex(VisualSceneInstance*) const
{
	return 0;
}

void Scene::notifyElementRegistered(VisualSceneInstance* instance)
{
	emit elementAdded(instance);
}

kint Scene::elementsOffset(Nigel::COLLADA::extra::Extra*) const
{
	return IOwner<VisualSceneInstance>::nextIndex();
}
