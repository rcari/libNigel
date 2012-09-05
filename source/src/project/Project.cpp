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

#include <project/Model.hpp>
#include <project/Project.hpp>
#include <project/ProjectConstants.hpp>
using namespace Nigel::project;

#include <scene/Scene.hpp>
#include <scene/VisualScene.hpp>
using namespace Nigel::scene;

#include <COLLADA/DocumentInstanceReference.hpp>
#include <COLLADA/InstancesManager.hpp>
using namespace Nigel::COLLADA;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::project::Project
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON("nigel/images/icons/project.png")
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END
using namespace Kore;

#include <QtCore/QDir>

Project::Project()
{
}

Model* Project::createModel(const QString& name)
{
	QDir rootDir = fileInfo().dir();
	if(!rootDir.cd(N_PROJECT_MODELS_FOLDER))
	{
		KoreEngine::Error(tr("Invalid project structure"), tr("The project structure is corrupted !"));
		return K_NULL;
	}

	QString dirName = name;
	for(kint counter = 1; rootDir.cd(dirName); counter++)
	{
		// The folder already exists !
		// Go back to the root !
		rootDir.cdUp();
		// Try with a new name !
		dirName = QString("%1-%2").arg(name).arg(counter);
	}

	// Create the root folder for the model
	rootDir.mkdir(dirName);
	rootDir.cd(dirName);

	// TODO: Add test for proper model folder creation.

	Model* model = Model::CreateNewModel(
			rootDir.absoluteFilePath(
					QString("%1.model").arg(name)
				)
		);

	model->blockName(name);

	// Add the model to the current manager.
	manager()->addBlock(model);

	// Save the model right away !
	manager()->saveInstance(model);

	return model;
}

Project* Project::CreateNewProject(const QString& projectFilePath)
{
	QString file = projectFilePath;
	if(!projectFilePath.endsWith(N_PROJECT_FILE_EXTENSION))
	{
		file.append(N_PROJECT_FILE_EXTENSION);
	}

	Project* result = DocumentInstance::CreateDocumentInstance<Project>(file);

	K_ASSERT( result )

	// Project layout is created here.
	QDir projectRoot = result->fileInfo().dir();

	if(!QFileInfo(projectRoot.path()).isWritable())
	{
		Kore::KoreEngine::Error(
				tr("Could not create project !"),
				tr("Project folder %s is not writable !").arg(projectRoot.path())
			);

		result->destroy();
		return K_NULL;
	}

	// Create the resources folder.
	projectRoot.mkdir(N_PROJECT_RESOURCES_FOLDER);

	// Create the scenes folder.
	projectRoot.mkdir(N_PROJECT_SCENES_FOLDER);

	// Create the models folder.
	projectRoot.mkdir(N_PROJECT_MODELS_FOLDER);

	// TODO: Add default Project stuff (default scene, default model, default everything...)

	return result;
}
