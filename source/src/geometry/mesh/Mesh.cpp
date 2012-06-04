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

#include <geometry/mesh/Mesh.hpp>
#include <geometry/mesh/Primitive.hpp>
using namespace Nigel::geometry::mesh;

#include <geometry/mesh/buffer/VertexBuffer.hpp>
using namespace Nigel::geometry::mesh::buffer;

using namespace Nigel::COLLADA;

#define K_BLOCK_TYPE Nigel::geometry::mesh::Mesh
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

Mesh::Mesh()
:	_vertices(K_NULL)
{
	blockName(tr("Mesh"));
}

kint Mesh::primitivesNb() const
{
	return Nigel::COLLADA::ICollection<Primitive>::elementsNb();
}

Primitive* Mesh::primitive(kint i)
{
	return Nigel::COLLADA::ICollection<Primitive>::element<Primitive>(i);
}

kint Mesh::elementsOffset(Primitive*) const
{
	return ISourcesCollection::nextIndex();
}

void Mesh::notifyElementRegistered(Primitive* primitive)
{
	emit elementAdded(primitive);
}

kint Mesh::elementsOffset(Nigel::COLLADA::data::Source*) const
{
	return 0;
}

kint Mesh::elementsOffset(Nigel::COLLADA::extra::Extra*) const
{
	return Nigel::COLLADA::ICollection<Primitive>::nextIndex();
}

Mesh* Mesh::CreateMesh()
{
	// Create the Mesh
	Mesh* result = K_BLOCK_CREATE_INSTANCE( Mesh );

	// Create the Vertex buffer for the mesh
	VertexBuffer* buffer = K_BLOCK_CREATE_INSTANCE( VertexBuffer );

	// Add the vertex buffer to the mesh
	result->addBlock(buffer);

	// And voila !
	return result;
}
