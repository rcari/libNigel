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

#include <project/Model.hpp>
using namespace Nigel::project;

#include <geometry/GeometriesLibrary.hpp>
using namespace Nigel::geometry;

using namespace Kore::data;

#include <scene/Scene.hpp>
#include <scene/VisualSceneInstance.hpp>
#include <scene/VisualScenesLibrary.hpp>
using namespace Nigel::scene;
using namespace Nigel::COLLADA::instantiation;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::project::Model
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/model.png")
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Model::Model()
:	_geometries(K_NULL)
{
}

void Model::addBlock(Block* block)
{
	// Call the parent implementation !
	DocumentInstance::addBlock(block);

	// Store the Geometries Library !!
	if(block->fastInherits<GeometriesLibrary>())
	{
		K_ASSERT( _geometries == K_NULL )
		_geometries = static_cast<GeometriesLibrary*>(block);
	}
}

GeometriesLibrary* Model::geometries()
{
	return _geometries;
}

Model* Model::CreateNewModel(const QString& absoluteFilePath)
{
	Model* model = DocumentInstance::CreateDocumentInstance<Model>(absoluteFilePath);
	model->blockName(tr("New model"));

	// Geometries library
	GeometriesLibrary* geometries = K_BLOCK_CREATE_INSTANCE( GeometriesLibrary );
	model->addBlock(geometries);

	// Create the default scene
	Scene* scene = K_BLOCK_CREATE_INSTANCE( Scene );
	model->addBlock(scene);

	// VisualScenes library to hold the scenes of the model (one scene per model).
	VisualScenesLibrary* visualScenes = K_BLOCK_CREATE_INSTANCE( VisualScenesLibrary );
	model->addBlock(visualScenes);

	// The default visual scene for the model.
	VisualScene* visualScene = VisualScene::CreateNewVisualScene();
	visualScene->blockName(tr("Default Scene"));
	visualScenes->addBlock(visualScene);

	VisualSceneInstance* visualSceneInstance = ElementInstance::CreateElementInstance<VisualSceneInstance>(visualScene);
	scene->addBlock(visualSceneInstance); // Add the default scene to the model.

	return model;
}
