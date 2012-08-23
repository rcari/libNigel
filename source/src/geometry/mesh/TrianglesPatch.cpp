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

#include <geometry/mesh/TrianglesPatch.hpp>
using namespace Nigel::geometry::mesh;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::geometry::mesh::TrianglesPatch
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

#include <QtCore/QtEndian>

TrianglesPatch::TrianglesPatch()
{
	blockName(tr("Triangles patch"));
}

kvoid* TrianglesPatch::indices()
{
	return _triangles.data();
}

const kvoid* TrianglesPatch::indices() const
{
	return _triangles.constData();
}

ksize TrianglesPatch::count() const
{
	return _triangles.size()*3; // A triangle has 3 vertices .x
}

kint TrianglesPatch::trianglesNb() const
{
	return _triangles.size();
}

kint TrianglesPatch::prevEdgeIndex(kint edgeIndex) const
{
	return nextEdgeIndex(nextEdgeIndex(edgeIndex)); // 3 edges in a triangle prev is 2nd next.
}

kint TrianglesPatch::appendTriangles(kint number)
{
	emit appendingFaces(number);

	const kint index = _triangles.size();

	_edges.insert(
			index * 3,
			number * 3,
			Edge()
		);

	_triangles.insert(
			index,
			number,
			TriangleFace()
		);

	_facesData.insert(
			index,
			number,
			FaceMeshData()
		);

	return index;
}

void TrianglesPatch::doneAppendingTriangles(kint number)
{
	// Set the edges.
	initializeEdges(_triangles.size() - number, number);
	emit doneAppendingFaces(number);
}

void TrianglesPatch::insertTriangles(kint offset, kint nb)
{
	emit insertingFaces(offset, nb);

	_triangles.insert(
			offset,
			nb,
			TriangleFace()
		);

	_facesData.insert(
			offset,
			nb,
			FaceMeshData()
		);

	_edges.insert(
			offset * 3,
			nb * 3,
			Edge()
		);
}

void TrianglesPatch::doneInsertingTriangles(kint offset, kint nb)
{
	// Set the edges
	initializeEdges(offset, nb);
	emit doneInsertingFaces(offset, nb);
}

void TrianglesPatch::updatingTriangles(kint offset, kint nb)
{
	emit updatingFaces(offset, nb);
}

void TrianglesPatch::doneUpdatingTriangles(kint offset, kint nb)
{
	// Set the edges
	initializeEdges(offset, nb);
	emit doneUpdatingFaces(offset, nb);
}

void TrianglesPatch::removeTriangles(kint offset, kint nb)
{
	emit removingFaces(offset, nb);

	// TODO: Check this actually works... How do the algorithms decimate the mesh ?
	_triangles.remove(offset, nb);
	_facesData.remove(offset, nb);
	_edges.remove(offset*3, nb*3);
}

void TrianglesPatch::doneRemovingTriangles(kint offset, kint nb)
{
	emit doneRemovingFaces(offset, nb);
}

void TrianglesPatch::initializeEdges(kint facesOffset, kint facesNumber)
{
	for(kint i = facesOffset; i < facesOffset + facesNumber; i++)
	{
		// TODO: Pair edges !
		const kint firstEdgeIndex = 3*i; // 3 edges per triangle !

		// Store the first edge's index in the face data.
		_facesData[i].firstEdge = firstEdgeIndex;

		_edges[firstEdgeIndex].nextEdge = firstEdgeIndex+1;
		_edges[firstEdgeIndex].face = i;
		_edges[firstEdgeIndex].endVertex = _triangles[i].v1;
		_verticesData[_triangles[i].v1].edge = firstEdgeIndex;

		_edges[firstEdgeIndex+1].nextEdge = firstEdgeIndex+2;
		_edges[firstEdgeIndex+1].face = i;
		_edges[firstEdgeIndex+1].endVertex = _triangles[i].v2;
		_verticesData[_triangles[i].v2].edge = firstEdgeIndex+1;

		_edges[firstEdgeIndex+2].nextEdge = firstEdgeIndex;
		_edges[firstEdgeIndex+2].face = i;
		_edges[firstEdgeIndex+2].endVertex = _triangles[i].v0;
		_verticesData[_triangles[i].v0].edge = firstEdgeIndex+2;
	}
}

kint TrianglesPatch::findPairEdgeIndex(const Edge& edge) const
{
	if(edge.pairEdge == -2)
	{
		return -1; // No pair edge and NO NEED TO LOOK FOR IT !
	}
	else if(edge.pairEdge != -1)
	{
		return edge.pairEdge;
	}

	TriangleFace triangle = _triangles.at(edge.face);

	// First find the start vertex.
	kint startVertex = _edges.at(nextEdgeIndex(edge.nextEdge)).endVertex; // Because it's a triangle...

	// TODO: Find a way to parallelize that ! // QFuture ? + split problem domain (only large sets ?)
	// Second go through all the triangles
	for(kint i = 0; i < _triangles.size(); i++)
	{
		triangle = _triangles.at(i);
		if(triangle.v0 == edge.endVertex && triangle.v1 == startVertex)
		{
			// First edge.
			return firstEdgeIndex(i);
		}
		else if(triangle.v1 == edge.endVertex && triangle.v2 == startVertex)
		{
			// Second edge.
			return secondEdgeIndex(i);
		}
		else if(triangle.v2 == edge.endVertex && triangle.v0 == startVertex)
		{
			// Third edge.
			return thirdEdgeIndex(i);
		}
	}

	// No pair edge was found !
	return -1;
}

kint TrianglesPatch::edgeStartVertexIndex(const Edge& edge) const
{
	TriangleFace triangle = _triangles.at(edge.face);

	if(edge.endVertex == triangle.v0)
	{
		return triangle.v2;
	}
	else if(edge.endVertex == triangle.v1)
	{
		return triangle.v0;
	}

	K_ASSERT( edge.endVertex == triangle.v2 )
	return triangle.v1;
}

QList<kint> TrianglesPatch::adjacentFaces(kint faceIndex) const
{
	QList<kint> result;

	// Unrolled loop (no branching condition for the loop).

	kint edgeIndex = _facesData.at(faceIndex).firstEdge;
	kint pairEdgeIndex = _edges.at(edgeIndex).pairEdge;

	if(pairEdgeIndex != -1)
	{
		result.append( _edges.at(pairEdgeIndex).face );
	}

	edgeIndex = _edges.at(edgeIndex).nextEdge;
	pairEdgeIndex = _edges.at(edgeIndex).pairEdge;

	if(pairEdgeIndex != -1)
	{
		result.append( _edges.at(pairEdgeIndex).face );
	}

	edgeIndex = _edges.at(edgeIndex).nextEdge;
	pairEdgeIndex = _edges.at(edgeIndex).pairEdge;

	if(pairEdgeIndex != -1)
	{
		result.append( _edges.at(pairEdgeIndex).face );
	}

	// At most 3 adjacent faces.
	qSort(result);
	return result;
}

QByteArray TrianglesPatch::trianglesArray() const
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	QByteArray data(reinterpret_cast<const char*>(_triangles.data()), _triangles.size()*sizeof(TriangleFace));
	TriangleFace* triangles = reinterpret_cast<TriangleFace*>(data.data());
	for(int i = 0; i < _triangles.size(); i++)
	{
		triangles[i].v0 = qToLittleEndian<qint32>(triangles[i].v0);
		triangles[i].v1 = qToLittleEndian<qint32>(triangles[i].v1);
		triangles[i].v2 = qToLittleEndian<qint32>(triangles[i].v2);
	}
	return data;
#else
	return QByteArray::fromRawData( reinterpret_cast<const char*>(_triangles.data()), _triangles.size()*sizeof(TriangleFace) );
#endif
}

void TrianglesPatch::trianglesArray(const QByteArray& data)
{
	_triangles.resize( data.size() / sizeof(TriangleFace) );
	qMemCopy( _triangles.data(), data.constData(), data.size() );

#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	for(kint i = 0; i < _triangles.size(); i++)
	{
		_triangles[i].v0 = qFromLittleEndian<qint32>(_triangles[i].v0);
		_triangles[i].v1 = qFromLittleEndian<qint32>(_triangles[i].v1);
		_triangles[i].v2 = qFromLittleEndian<qint32>(_triangles[i].v2);
	}
#endif
}
