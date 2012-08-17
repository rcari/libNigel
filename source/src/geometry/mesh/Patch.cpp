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

#include <geometry/mesh/Patch.hpp>
using namespace Nigel::geometry::mesh;

#include <geometry/mesh/buffer/VertexBuffer.hpp>
using namespace Nigel::geometry::mesh;

#define K_BLOCK_TYPE Nigel::geometry::mesh::Patch
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_VIRTUAL
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

using namespace Kore::data;

Patch::Patch()
:	_verticesOffset(0),
 	_changingLocalVertices(false)
{
}

void Patch::library(Library* lib)
{
	if(hasParent())
	{
		mesh()->disconnect(this);
	}
	Primitive::library(lib);
	if(hasParent())
	{
		K_ASSERT(  mesh()->verticesBuffer() )

		connect(mesh()->verticesBuffer(), SIGNAL(insertingElements(kint,kint)), SLOT(insertingVerticesInBuffer(kint,kint)));
		connect(mesh()->verticesBuffer(), SIGNAL(removingElements(kint,kint)), SLOT(removingVerticesFromBuffer(kint,kint)));
	}

}

QList<kint> Patch::faceEdges(kint faceIndex) const
{
	QList<kint> result;
	kint index = _facesData.at(faceIndex).firstEdge;
	do
	{
		result.append(index);
		index = nextEdgeIndex(index);
	}
	while(index != _facesData.at(faceIndex).firstEdge);
	return result;
}

QList<kint> Patch::vertexEdges(kint localVertexIndex) const
{
	QList<kint> result;

	kint firstEdgeIndex = _verticesData.at(localVertexIndex).edge;
	kint index = firstEdgeIndex;

	do {
		kint nextIndex = nextEdgeIndex(index);

		// Add the edge and its next edge (the next edge share the vertex !).
		result.append(index);
		result.append(nextIndex);

		// Move to the next edge.
		index = _edges.at(nextIndex).pairEdge;

	} while( index != -1 && index != firstEdgeIndex );

	firstEdgeIndex = _edges.at(firstEdgeIndex).pairEdge;
	index = firstEdgeIndex;

	if(index == -1) // The pair edge from the original edge might be non-existant: no need to continue.
	{
		goto end;
	}

	do // A reverse loop from previous to previous.
	{
		kint prevIndex = prevEdgeIndex(index);

		// Add the edge and its previous edge (the previous edge share the vertex !).
		result.append(index);
		result.append(prevIndex);

		// Move to the next edge.
		index = _edges.at(prevIndex).pairEdge;

	} while( index != -1 && index != firstEdgeIndex );

end:
	qSort(result); // For afterwards performance.
	return result;
}

QList<kint> Patch::vertexFaces(kint localVertexIndex) const
{
	QList<kint> result;

	kint firstEdgeIndex = _verticesData.at(localVertexIndex).edge;
	kint index = firstEdgeIndex;

	do {
		// Add the edge's face.
		result.append(_edges.at(index).face);

		// Move to the next edge.
		index = _edges.at(nextEdgeIndex(index)).pairEdge;

	} while( index != -1 && index != firstEdgeIndex );

	firstEdgeIndex = _edges.at(firstEdgeIndex).pairEdge;
	index = firstEdgeIndex;

	if(index == -1) // The pair edge from the original edge might be non-existent: no need to continue.
	{
		goto end;
	}

	do // A reverse loop from previous to previous.
	{
		kint faceIndex = _edges.at(index).face;

		if(result.contains(faceIndex))
		{
			// We have already seen that face, and consequently all its precedents: no need to continue.
			goto end;
		}

		// Add the edge's face
		result.append(faceIndex);

		// Move to the next edge.
		index = _edges.at(prevEdgeIndex(index)).pairEdge;

	} while( index != -1 && index != firstEdgeIndex );

end:
	qSort(result); // For afterwards performance.
	return result;
}

kint Patch::insertVertices(kint offset, kint number)
{
	_changingLocalVertices = true;

	// Update the indices of the patch.
	kuint unsignedOffset = offset; // Unisgned to avoid signed/unsigned comparisons + offset are >= 0 (strictly).
	kuint* indices = static_cast<kuint*>(this->indices()); // Might be costly to call, better cache it !
	const kint count = this->count(); // Could be costly to call, better cache it !

	for(kint i = 0; i < count; i++)
	{
		if(indices[i] >= unsignedOffset)
		{
			indices[i] += number;
		}
	}

	// Allocate local space for vertices data.
	_verticesData.insert(offset, number, VertexData());

	mesh()->verticesBuffer()->insertVertices( _verticesOffset + offset, number );

	return offset;
}

void Patch::doneInsertingVertices(kint offset, kint number)
{
	mesh()->verticesBuffer()->doneInsertingVertices( _verticesOffset + offset, number );
	_changingLocalVertices = false;
}

kint Patch::appendVertices(kint number)
{
	_changingLocalVertices = true;

	// Do that BEFORE adding memory in the _verticesData Vector.
	mesh()->verticesBuffer()->insertVertices( _verticesOffset + _verticesData.size(), number );

	// Allocate local space for vertices data.
	_verticesData.insert( _verticesData.size(), number, VertexData());

	return _verticesData.size() - number;
}

void Patch::doneAppendingVertices(kint number)
{
	mesh()->verticesBuffer()->doneInsertingVertices( _verticesOffset + _verticesData.size() - number, number );
	_changingLocalVertices = false;
}

void Patch::removeVertices(kint offset, kint number)
{
	_changingLocalVertices = true;

	// Update the indices of the patch.
	kuint unsignedOffset = offset; // Unisgned to avoid signed/unsigned comparisons + offset are >= 0 (strictly).
	kuint* indices = static_cast<kuint*>(this->indices()); // Might be costly to call, better cache it !
	const kint count = this->count(); // Could be costly to call, better cache it !

	for(kint i = 0; i < count; i++)
	{
		if(indices[i] >= unsignedOffset)
		{
			indices[i] -= number;
		}
	}

	_verticesData.remove(offset, number);

	mesh()->verticesBuffer()->removeVertices( _verticesOffset + offset, number );
}

void Patch::doneRemovingVertices(kint offset, kint number)
{
	mesh()->verticesBuffer()->doneRemovingVertices( _verticesOffset + offset, number );
	_changingLocalVertices = false;
}

void Patch::insertingVerticesInBuffer(kint offset, kint number)
{
	// We must make sure we're not inserting/appending vertices in this patch at the beginning.
	// In such a case, the verticesOffset does not change.
	// However, the previous patch might be inserting elements at its end (which is our _verticesOffset).
	if(offset <= _verticesOffset && !_changingLocalVertices)
	{
		_verticesOffset += number;
	}
}

void Patch::removingVerticesFromBuffer(kint offset, kint number)
{
	if(offset < _verticesOffset)
	{
		_verticesOffset -= number;
	}
}

void Patch::verticesOffset(kint offset)
{
	_verticesOffset = offset;
}

QByteArray Patch::verticesDataArray() const
{
	return QByteArray::fromRawData( reinterpret_cast<const char*>(_verticesData.data()), _verticesData.size()*sizeof(VertexData) );
}

void Patch::verticesDataArray(const QByteArray& data)
{
	// Allocate the buffer
	_verticesData.resize( data.size() / sizeof(VertexData) );
	// Copy the data to the buffer
	qMemCopy( _verticesData.data(), data.constData(), data.size() );
}

QByteArray Patch::facesDataArray() const
{
	return QByteArray::fromRawData( reinterpret_cast<const char*>(_facesData.data()), _facesData.size()*sizeof(FaceMeshData) );
}

void Patch::facesDataArray(const QByteArray& data)
{
	_facesData.resize( data.size() / sizeof(FaceMeshData) );
	qMemCopy( _facesData.data(), data.constData(), data.size() );
}

QByteArray Patch::edgesArray() const
{
	return QByteArray::fromRawData( reinterpret_cast<const char*>(_edges.data()), _edges.size()*sizeof(Edge) );
}

void Patch::edgesArray(const QByteArray& data)
{
	_edges.resize( data.size() / sizeof(Edge) );
	qMemCopy( _edges.data(), data.constData(), data.size() );
}
