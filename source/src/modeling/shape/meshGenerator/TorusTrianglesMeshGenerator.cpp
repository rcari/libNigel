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


#include <modeling/shape/Torus.hpp>
#include <modeling/shape/meshGenerator/TorusTrianglesMeshGenerator.hpp>
using namespace Nigel::modeling::shape;
using namespace Nigel::modeling::shape::meshGenerator;

#include <geometry/GeometricElement.hpp>
using namespace Nigel::geometry;

#include <geometry/mesh/TrianglesPatch.hpp>
using namespace Nigel::geometry::mesh;

#include <geometry/mesh/buffer/VertexBuffer.hpp>
using namespace Nigel::geometry::mesh::buffer;

#include "../../../../inc/math/Math.hpp"
using namespace Nigel::math;

#define K_BLOCK_TYPE Nigel::modeling::shape::meshGenerator::TorusTrianglesMeshGenerator
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

#include <modeling/ModelingEngine.hpp>
N_GENERATOR_I(
		Nigel::modeling::shape::meshGenerator::TorusTrianglesMeshGenerator,
		Nigel::modeling::shape::Torus
	)

TorusTrianglesMeshGenerator::TorusTrianglesMeshGenerator()
:	_slices(tr("Slices"), QVariant::Int),
 	_stacks(tr("Stacks"), QVariant::Int)
{
	_slices.minimum(QVariant(3));
	_stacks.minimum(QVariant(3));
	_parameters.append(&_slices);
	_parameters.append(&_stacks);
}

GeometricElement* TorusTrianglesMeshGenerator::generatePrimitive(const QVariantMap& parameters) const
{
	//gets parameters
	kint nbSlices = parameters.value(tr("Slices")).toInt();
	kint nbStacks = parameters.value(tr("Stacks")).toInt();
	double radiusExt = parameters.value(tr("External radius")).toDouble();
	double radiusInt = parameters.value(tr("Internal radius")).toDouble();

	//creates the mesh
	Mesh* mesh = Mesh::CreateMesh();
	TrianglesPatch* patch = K_BLOCK_CREATE_INSTANCE ( Nigel::geometry::mesh::TrianglesPatch );
	mesh->addBlock(patch);

	patch->appendVertices(nbSlices*nbStacks);
	patch->appendTriangles(nbStacks*(nbSlices*2));

	Vertex* vertices = patch->vertices();
	TriangleFace* faces = patch->triangles();

	kint offset = 0;

	//appends vertices
	Vertex vertex;
	vertex.w = 1.0f;

	for(int i=0; i<nbSlices; ++i) //vertices in stacks
	{
		for(int j=0; j<nbStacks; ++j)
		{
			vertex.x = (radiusExt * Math::Cos((M_PI*2*i)/nbSlices)) + (radiusInt * Math::Sin((M_PI*2*j)/nbStacks));
			vertex.y = (radiusExt * Math::Sin((M_PI*2*i)/nbSlices)) + (radiusInt * Math::Sin((M_PI*2*j)/nbStacks));
			vertex.z = radiusInt * Math::Cos((M_PI*2*j)/nbStacks);
			vertices[offset] = vertex;
			offset++;
		}
	}

	// Reset offset.
	offset = 0;

	//appends faces
	TriangleFace face;

	for(int i=0; i<nbSlices-1; ++i) //middle faces
	{
		for(int j=0; j<nbStacks-1; ++j)
		{
			face.v0 = (i*nbStacks) + j;
			face.v1 = ((i+1)*nbStacks) + j;
			face.v2 = (i*nbStacks) + j+1;
			faces[offset] = face;
			offset++;

			face.v0 = (i*nbStacks) + j+1;
			face.v1 = ((i+1)*nbStacks) + j;
			face.v2 = ((i+1)*nbStacks) + j+1;
			faces[offset] = face;
			offset++;
		}
		face.v0 = ((i+1)*nbStacks) - 1;
		face.v1 = i*nbStacks;
		face.v2 = (i+1)*nbStacks;
		faces[offset] = face;
		offset++;

		face.v0 = (i+1)*nbStacks;
		face.v1 = ((i+1)*nbStacks) - 1;
		face.v2 = ((i+2)*nbStacks) - 1;
		faces[offset] = face;
		offset++;
	}
	for(int i=0; i<nbStacks-1; ++i) //bottom faces
	{
		face.v0 = ((nbSlices-1)*nbStacks) + i;
		face.v1 = i;
		face.v2 = ((nbSlices-1)*nbStacks) + i+1;
		faces[offset] = face;
		offset++;

		face.v0 = ((nbSlices-1)*nbStacks) + i+1;
		face.v1 = i;
		face.v2 = i+1;
		faces[offset] = face;
		offset++;
	}
	face.v0 = (nbSlices*nbStacks) - 1;
	face.v1 = 0;
	face.v2 = nbStacks-1;
	faces[offset] = face;
	offset++;

	face.v0 = (nbSlices-1)*nbStacks;
	face.v1 = (nbSlices*nbStacks) - 1;
	face.v2 = 0;
	faces[offset] = face;

	patch->doneAppendingVertices(nbSlices*nbStacks);
	patch->doneAppendingTriangles(nbStacks*(nbSlices*2));

	return mesh;
}
