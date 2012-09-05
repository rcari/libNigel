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

#include <geometry/mesh/QuadsPatch.hpp>
using namespace Nigel::geometry::mesh;

#include <NigelModule.hpp>

#define K_BLOCK_TYPE Nigel::geometry::mesh::QuadsPatch
#include <data/BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

#include <QtCore/QtEndian>

QuadsPatch::QuadsPatch()
{
	blockName(tr("Quads patch"));
}

kvoid* QuadsPatch::indices()
{
	return _quads.data();
}

const kvoid* QuadsPatch::indices() const
{
	return _quads.constData();
}

ksize QuadsPatch::count() const
{
	return _quads.size()*4; // A quad has 4 vertices .x
}

kint QuadsPatch::prevEdgeIndex(kint edgeIndex) const
{
	return nextEdgeIndex(nextEdgeIndex(nextEdgeIndex(edgeIndex))); // 4 edges in a QUAD prev is 3rd next.
}

kint QuadsPatch::appendQuads(kint number)
{
	emit appendingFaces(number);

	_quads.insert(
			_quads.size(),
			number,
			QuadFace()
		);

	_facesData.insert(
			_facesData.size(),
			number,
			FaceMeshData()
		);

	_edges.insert(
			_quads.size() * 3,
			number * 3,
			Edge()
		);

	// TODO : change return by the index of the first quad appended
	return 0;
}

void QuadsPatch::doneAppendingQuads(kint number)
{
	// Set the edges.
	initializeEdges(_quads.size() - number, number);
	emit doneAppendingFaces(number);
}

void QuadsPatch::insertQuads(kint offset, kint nb)
{
	emit insertingFaces(offset, nb);

	_quads.insert(
			offset,
			nb,
			QuadFace()
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

void QuadsPatch::doneInsertingQuads(kint offset, kint nb)
{
	// Set the edges
	initializeEdges(offset, nb);
	emit doneInsertingFaces(offset, nb);
}

void QuadsPatch::updatingQuads(kint offset, kint nb)
{
	emit updatingFaces(offset, nb);
}

void QuadsPatch::doneUpdatingQuads(kint offset, kint nb)
{
	// Set the edges
	initializeEdges(offset, nb);
	emit doneUpdatingFaces(offset, nb);
}

void QuadsPatch::removeQuads(kint offset, kint nb)
{
	emit removingFaces(offset, nb);

	_quads.remove(offset, nb);
	_facesData.remove(offset, nb);
	_edges.remove(offset*4, nb*4);
}

void QuadsPatch::doneRemovingQuads(kint offset, kint nb)
{
	emit doneRemovingFaces(offset, nb);
}

void QuadsPatch::initializeEdges(kint facesOffset, kint facesNumber)
{
	for(kint i = facesOffset; i < facesOffset + facesNumber; i++)
	{
		// TODO: Pair edges !
		const kint firstEdgeIndex = 4*i; // 4 edges per quad !

		// Store the first edge's index in the face data.
		_facesData[i].firstEdge = firstEdgeIndex;

		_edges[firstEdgeIndex].nextEdge = firstEdgeIndex + 1;
		_edges[firstEdgeIndex].face = i;
		_edges[firstEdgeIndex].endVertex = _quads[i].v1;
		_verticesData[_quads[i].v1].edge = firstEdgeIndex;

		_edges[firstEdgeIndex+1].nextEdge = firstEdgeIndex + 2;
		_edges[firstEdgeIndex+1].face = i;
		_edges[firstEdgeIndex+1].endVertex = _quads[i].v2;
		_verticesData[_quads[i].v2].edge = firstEdgeIndex + 1;

		_edges[firstEdgeIndex+2].nextEdge = firstEdgeIndex + 3;
		_edges[firstEdgeIndex+2].face = i;
		_edges[firstEdgeIndex+2].endVertex = _quads[i].v3;
		_verticesData[_quads[i].v3].edge = firstEdgeIndex + 2;

		_edges[firstEdgeIndex+3].nextEdge = firstEdgeIndex;
		_edges[firstEdgeIndex+3].face = i;
		_edges[firstEdgeIndex+3].endVertex = _quads[i].v0;
		_verticesData[_quads[i].v0].edge = firstEdgeIndex + 3;
	}
}

kint QuadsPatch::findPairEdgeIndex(const Edge& edge) const
{
	if(edge.pairEdge == -2)
	{
		return -1; // No pair edge and NO NEED TO LOOK FOR IT !
	}
	else if(edge.pairEdge != -1)
	{
		return edge.pairEdge;
	}

	QuadFace quad = _quads.at(edge.face);

	// First find the start vertex.
	kint startVertex = _edges.at(nextEdgeIndex(nextEdgeIndex(edge.nextEdge))).endVertex; // Because it's a triangle...

	// TODO: Find a way to parallelize that ! // QFuture ? + split problem domain (only large sets ?)
	// Second go through all the triangles
	for(kint i = 0; i < _quads.size(); i++)
	{
		quad = _quads.at(i);
		if(quad.v0 == edge.endVertex && quad.v1 == startVertex)
		{
			// First edge.
			return firstEdgeIndex(i);
		}
		else if(quad.v1 == edge.endVertex && quad.v2 == startVertex)
		{
			// Second edge.
			return secondEdgeIndex(i);
		}
		else if(quad.v2 == edge.endVertex && quad.v3 == startVertex)
		{
			// Third edge.
			return thirdEdgeIndex(i);
		}
		else if(quad.v3 == edge.endVertex && quad.v0 == startVertex)
		{
			return fourthEdgeIndex(i);
		}
	}

	// No pair edge was found !
	return -1;
}

kint QuadsPatch::edgeStartVertexIndex(const Edge& edge) const
{
	QuadFace triangle = _quads.at(edge.face);

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

QList<kint> QuadsPatch::adjacentFaces(kint faceIndex) const
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

QVariant QuadsPatch::quadsArray() const
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	QByteArray data(reinterpret_cast<const char*>(_quads.data()), _quads.size()*sizeof(QuadFace));
	QuadFace* quads = reinterpret_cast<QuadFace*>(data.data());
	for(int i = 0; i < _quads.size(); i++)
	{
		quads[i].v0 = qToLittleEndian<qint32>(quads[i].v0);
		quads[i].v1 = qToLittleEndian<qint32>(quads[i].v1);
		quads[i].v2 = qToLittleEndian<qint32>(quads[i].v2);
		quads[i].v3 = qToLittleEndian<qint32>(quads[i].v3);
	}
	return data;
#else
	return QByteArray::fromRawData( reinterpret_cast<const char*>(_quads.data()), _quads.size()*sizeof(QuadFace) );
#endif
}

void QuadsPatch::quadsArray(const QVariant& v)
{
	const QByteArray& data = v.toByteArray();
	_quads.resize( data.size() / sizeof(QuadFace) );
	qMemCopy( _quads.data(), data.constData(), data.size() );

#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	for(int i = 0; i < _quads.size(); i++)
	{
		_quads[i].v0 = qFromLittleEndian<qint32>(_quads[i].v0);
		_quads[i].v1 = qFromLittleEndian<qint32>(_quads[i].v1);
		_quads[i].v2 = qFromLittleEndian<qint32>(_quads[i].v2);
		_quads[i].v3 = qFromLittleEndian<qint32>(_quads[i].v3);
	}
#endif
}
