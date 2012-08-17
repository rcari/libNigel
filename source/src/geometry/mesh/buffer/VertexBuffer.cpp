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

#include <geometry/mesh/buffer/VertexBuffer.hpp>
using namespace Nigel::geometry::mesh::buffer;

#include <geometry/mesh/Mesh.hpp>
using namespace Nigel::geometry::mesh;

#include <math/Vector4f.hpp>
using namespace Nigel::math;

#define K_BLOCK_TYPE Nigel::geometry::mesh::buffer::VertexBuffer
#include <BlockMacros.hpp>
K_BLOCK_BEGIN
	K_BLOCK_ICON_DEFAULT
	K_BLOCK_ALLOCABLE
	K_BLOCK_PROPERTY_DEFAULT
K_BLOCK_END

#include <QtCore/QtEndian>
#include <QtCore/QSet>

VertexBuffer::VertexBuffer()
:	Buffer(Buffer::Vertex)/*,
 	_vertexArray(this)*/
{
	blockName(tr("Vertex Buffer"));
}

void VertexBuffer::library(Kore::data::Library* lib)
{
	if(hasParent())
	{
		static_cast<Mesh*>(Library::library())->unregisterVertices(this);
	}
	Buffer::library(lib);
	if(lib)
	{
		static_cast<Mesh*>(lib)->registerVertices(this);
	}
}

const kvoid* VertexBuffer::data() const
{
	return this->vertices();
}

ksize VertexBuffer::dataSize() const
{
	return _vertices.size() * sizeof(Nigel::geometry::mesh::Vertex);
}

ksize VertexBuffer::elementSize() const
{
	return sizeof(Nigel::geometry::mesh::Vertex);
}

kint VertexBuffer::elementsNb() const
{
	return verticesNb();
}

kint VertexBuffer::nextSharedVertexIndex(kint vertexIndex) const
{
	return _verticesData.at(vertexIndex).nextSharedVertex;
}

QList<kint> VertexBuffer::getAllSharedVerticesIndices(const QList<kint>& verticesIndices) const
{
	QSet<kint> set; // We need a set to guarantee the uniqueness of the elements in the list.

	for(kint i = 0; i < verticesIndices.size(); i++)
	{
		kint vertexIndex = verticesIndices.at(i);
		for	(
				kint sharedVertexIndex = nextSharedVertexIndex(vertexIndex); // Initial shared vertex
				sharedVertexIndex != -1 && sharedVertexIndex != vertexIndex; // There's no shared vertex or we completed the loop !
				sharedVertexIndex = nextSharedVertexIndex(vertexIndex) // Next shared vertex index
			)
		{
			set.insert(sharedVertexIndex);
		}
	}

	QList<kint> result = set.toList();
	qSort(result); // The list is sorted, better for cache fetching when modifying data. This might have some drawbacks.
	return result;
}

QList<kint> VertexBuffer::getAllSharedVerticesIndices(kint vertexIndex) const
{
	QList<kint> result;
	result.append(vertexIndex);
	for(
			kint sharedVertexIndex = nextSharedVertexIndex(vertexIndex);
			sharedVertexIndex != -1 && sharedVertexIndex != vertexIndex;
			sharedVertexIndex = nextSharedVertexIndex(vertexIndex)
		)
	{
		result.append(sharedVertexIndex);
	}
	qSort(result); // Sort for better cache access afterwards.
	return result;
}

QList<kint> VertexBuffer::mergeVerticesIndices(const QList<kint>& v1, const QList<kint>& v2) const
{
	QSet<kint> set = QSet<kint>::fromList(v1);
	set.unite(QSet<kint>::fromList(v2));

	QList<kint> result = set.values();
	qSort(result);
	return result;
}

void VertexBuffer::bindVertices(const QList<kint>& verticesIndices, kbool doCleanList)
{
	QList<kint> vertices;
	if(doCleanList)
	{
		QSet<kint> set = QSet<kint>::fromList(verticesIndices);
		vertices = set.values();
		qSort(vertices);
	}
	else
	{
		vertices = verticesIndices; // No deep copy (implicitly shared classes !).
	}

	for(kint i = 0; i < vertices.size(); i++)
	{
		kint nextIndex = (i + 1) % vertices.size();
		_verticesData[i].nextSharedVertex = vertices.at(nextIndex);
	}
}

void VertexBuffer::setVerticesPosition(QList<kint> verticesIndices, const vec4f& position)
{
	// Vertices MUST be ORDERED !
	int offset = verticesIndices.first();
	int range = verticesIndices.last() - offset;

	emit updatingElements(offset, range);

	const Vector4f pos(position);
	for(kint i = 0; i < verticesIndices.size(); i++)
	{
		pos.assignTo(_vertices[i]);
	}

	emit doneUpdatingElements(offset, range);
}

void VertexBuffer::moveVertices(QList<kint> verticesIndices, const vec4f& direction)
{
	// Vertices MUST be ORDERED !
	int offset = verticesIndices.first();
	int range = verticesIndices.last() - offset;

	emit updatingElements(offset, range);

	const Vector4f dir(direction);
	for(kint i = 0; i < verticesIndices.size(); i++)
	{
		dir.addTo(_vertices[i]); // In place add !
	}

	emit doneUpdatingElements(offset, range);
}

Nigel::geometry::mesh::Vertex* VertexBuffer::insertVertices(kint offset, kint number)
{
	emit insertingElements(offset, number);
	_vertices.insert(offset, number, mesh::Vertex());
	_verticesData.insert(offset, number, SharedVertexData());
	return _vertices.data() + offset;
}

void VertexBuffer::doneInsertingVertices(kint offset, kint number)
{
	emit doneInsertingElements(offset, number);
}

Nigel::geometry::mesh::Vertex* VertexBuffer::updateVertices(kint offset, kint number)
{
	emit updatingElements(offset, number);
	return _vertices.data() + offset;
}

void VertexBuffer::doneUpdatingVertices(kint offset, kint number)
{
	emit doneUpdatingElements(offset, number);
}

void VertexBuffer::removeVertices(kint offset, kint number)
{
	emit removingElements(offset, number);
	_vertices.remove(offset, number);
	_verticesData.remove(offset, number);
}

void VertexBuffer::doneRemovingVertices(kint offset, kint number)
{
	emit doneRemovingElements(offset, number);
}

QByteArray VertexBuffer::verticesArray() const
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	QByteArray* data( reinterpret_cast<const char*>(_vertices.constData()), _vertices.size()*sizeof(mesh::Vertex) );
	mesh::Vertex* vertices = reinterpret_cast<mesh::Vertex*>(data.data());
	for(kint i = 0; i < _vertices.size(); i++)
	{
		qint32* vertex = reinterpret_cast<qint32*>( vertices + i );
		vertex[0] = qToLittleEndian<qint32>(vertex[0]);
		vertex[1] = qToLittleEndian<qint32>(vertex[1]);
		vertex[2] = qToLittleEndian<qint32>(vertex[2]);
		vertex[3] = qToLittleEndian<qint32>(vertex[3]);
	}
	return data;
#else
	return QByteArray::fromRawData( reinterpret_cast<const char*>(_vertices.data()), _vertices.size()*sizeof(mesh::Vertex) );
#endif
}

void VertexBuffer::verticesArray(const QByteArray& data)
{
	// Allocate the buffer.
	_vertices.resize(data.size() / sizeof(mesh::Vertex));
	// Copy the data back to the buffer.
	qMemCopy(_vertices.data(), data.constData(), data.size());

#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	for(kint i = 0; i < _vertices.size(); i++)
	{
		qint32* vertex = reinterpret_cast<qint32*>( _vertices.data() + i );
		vertex[0] = qFromLittleEndian<qint32>(vertex[0]);
		vertex[1] = qFromLittleEndian<qint32>(vertex[1]);
		vertex[2] = qFromLittleEndian<qint32>(vertex[2]);
		vertex[3] = qFromLittleEndian<qint32>(vertex[3]);
	}
#endif
}

QByteArray VertexBuffer::verticesDataArray() const
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	QByteArray* data( reinterpret_cast<const char*>(_verticesData.constData()), _verticesData.size()*sizeof(SharedVertexData) );
	SharedVertexData* vertexData = reinterpret_cast<SharedVertexData*>(data.data());
	for(kint i = 0; i < _verticesData.size(); i++)
	{
		vertexData[i].nextSharedIndex = qToLittleEndian<qint32>(vertexData[i].nextSharedIndex);
	}
	return data;
#else
	return QByteArray::fromRawData( reinterpret_cast<const char*>(_verticesData.constData()), _verticesData.size()*sizeof(SharedVertexData) );
#endif
}

void VertexBuffer::verticesDataArray(const QByteArray& data)
{
	// Allocate the buffer.
	_verticesData.resize(data.size() / sizeof(mesh::SharedVertexData));
	// Copy the data back to the buffer.
	qMemCopy(_verticesData.data(), data.constData(), data.size());

#if Q_BYTE_ORDER == Q_BIG_ENDIAN
	for(kint i = 0; i < _verticesData.size(); i++)
	{
		_verticesData[i].nextSharedVertex = qFromLittleEndian<qint32>(_verticesData[i].nextSharedVertex);
	}
#endif
}
