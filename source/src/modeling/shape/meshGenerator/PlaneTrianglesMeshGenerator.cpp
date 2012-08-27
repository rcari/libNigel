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


#include <modeling/shape/Plane.hpp>
#include <modeling/shape/meshGenerator/PlaneTrianglesMeshGenerator.hpp>
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

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::modeling::shape::meshGenerator::PlaneTrianglesMeshGenerator
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

#include <modeling/ModelingEngine.hpp>
N_GENERATOR_I(
		Nigel::modeling::shape::meshGenerator::PlaneTrianglesMeshGenerator,
		Nigel::modeling::shape::Plane
	)

PlaneTrianglesMeshGenerator::PlaneTrianglesMeshGenerator()
:	_divx(tr("Width Subdivision"), QVariant::Int),
 	_divy(tr("Height Subdivision"), QVariant::Int)
{
	_divx.minimum(QVariant(0));
	_divy.minimum(QVariant(0));
	_parameters.append(&_divx);
	_parameters.append(&_divy);
}

GeometricElement* PlaneTrianglesMeshGenerator::generatePrimitive(const QVariantMap& parameters) const
{
	//gets parameters
	kint divx = parameters.value(tr("Width Subdivision")).toInt();
	kint divy = parameters.value(tr("Height Subdivision")).toInt();
	double width = parameters.value(tr("Width")).toDouble();
	double height = parameters.value(tr("Height")).toDouble();

	//creates the mesh
	Mesh* mesh = Mesh::CreateMesh();
	TrianglesPatch* patch = K_BLOCK_CREATE_INSTANCE ( Nigel::geometry::mesh::TrianglesPatch );
	mesh->addBlock(patch);

	patch->appendVertices((divx+2)*(divy+2));
	patch->appendTriangles((divx+1)*(divy+1)*2);

	Vertex* vertices = patch->vertices();
	TriangleFace* faces = patch->triangles();

	kint offset = 0;
	kint offsetFaces = 0;

	Vertex vertex;
	vertex.w = 1.0f;

	TriangleFace face;

	for(int i=0; i<divy+1; ++i)
	{
		for(int j=0; j<divx+1; ++j)
		{
			face.v0 = (i*(divx+2)) + j;
			face.v1 = (i*(divx+2)) + j+1;
			face.v2 = (i*(divx+2)) + divx+2 + j;
			faces[offsetFaces] = face;
			offsetFaces++;
			face.v0 = (i*(divx+2)) + j+1;
			face.v1 = (i*(divx+2)) + divx+2 + j+1;
			face.v2 = (i*(divx+2)) + divx+2 + j;
			faces[offsetFaces] = face;
			offsetFaces++;
		}
	}
	for(int i=0; i<divy+2; ++i)
	{
		for(int j=0; j<divx+2; ++j)
		{
			vertex.x = j*(width/(divx+1));
			vertex.y = i*(height/(divy+1));
			vertex.z = 0.0f;
			vertices[offset] = vertex;
			offset++;
		}
	}

	patch->doneAppendingVertices((divx+2)*(divy+2));
	patch->doneAppendingTriangles((divx+1)*(divy+1)*2);

	return mesh;
}
