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

#pragma once

#include <NigelExport.hpp>

#include "Buffer.hpp"
#include "../Structures.hpp"

#include <math/MathTypes.hpp>

#include <COLLADA/data/IArray.hpp>

#include <QtCore/QByteArray>
#include <QtCore/QVector>

namespace Nigel { namespace geometry { namespace mesh {

class Patch;

namespace buffer {

class NigelExport VertexBuffer : public Buffer
{
	Q_OBJECT
	Q_PROPERTY( QString verticesName READ blockName WRITE blockName STORED true DESIGNABLE false )
	Q_PROPERTY( QByteArray vertices READ verticesArray WRITE verticesArray STORED true DESIGNABLE false FINAL )
	Q_PROPERTY( QByteArray verticesData READ verticesDataArray WRITE verticesDataArray STORED true DESIGNABLE false FINAL )
	Q_PROPERTY( int verticesNb READ elementsNb STORED false DESIGNABLE true )

	K_BLOCK

	friend class Nigel::geometry::mesh::Patch;

protected:
	VertexBuffer();

	virtual void library(Kore::data::Library* lib);

public:
	virtual const kvoid* data() const;
	virtual ksize dataSize() const;
	virtual ksize elementSize() const;
	virtual kint elementsNb() const;

	inline Nigel::geometry::mesh::Vertex* vertices() { return _vertices.data(); }
	inline const Nigel::geometry::mesh::Vertex* vertices() const { return _vertices.data(); }
	inline Nigel::geometry::mesh::SharedVertexData* verticesData() { return _verticesData.data(); }
	inline const Nigel::geometry::mesh::SharedVertexData* verticesData() const { return _verticesData.data(); }
	inline kint verticesNb() const { return _vertices.size(); }

	/*
	 * Some vertices are present multiple times in the buffer but represent the same vertex in reality.
	 * When a user selects a Vertex, we want to select ALL the vertices in the buffer for modification.
	 * This methods makes the link between those elements by using the underlying data structures.
	 */
	kint nextSharedVertexIndex(kint vertexIndex) const;
	QList<kint> getAllSharedVerticesIndices(const QList<kint>& verticesIndices) const;
	QList<kint> getAllSharedVerticesIndices(kint vertexIndex) const;
	QList<kint> mergeVerticesIndices(const QList<kint>& v1, const QList<kint>& v2) const;
	void bindVertices(const QList<kint>& verticesIndices, kbool doCleanList = true);

	void setVerticesPosition(QList<kint> verticesIndices, const Nigel::math::vec4f& position);
	void moveVertices(QList<kint> verticesIndices, const Nigel::math::vec4f& direction);

protected:
	Nigel::geometry::mesh::Vertex* insertVertices(kint offset, kint number);
	void doneInsertingVertices(kint offset, kint number);

	Nigel::geometry::mesh::Vertex* updateVertices(kint offset, kint number);
	void doneUpdatingVertices(kint offset, kint number);

	void removeVertices(kint offset, kint number);
	void doneRemovingVertices(kint offset, kint number);

private:
	// Serialization properties
	QByteArray verticesArray() const;
	void verticesArray(const QByteArray&);

	QByteArray verticesDataArray() const;
	void verticesDataArray(const QByteArray&);

private:
	/*class VertexArray : public Nigel::COLLADA::data::IArray
	{
		friend class VertexBuffer;
	public:
		VertexArray(VertexBuffer* buffer) : _buffer(buffer) { addFlag(SystemOwned); }
		virtual ~VertexArray() { addFlag(IsBeingDeleted); }
		virtual IArray::ArrayType type() { return Float; }
		virtual kint elementsNb() const { return _buffer->_vertices.size() * 4; }
		virtual kvoid* elementsData() { return _buffer->_vertices.data(); }
	private:
		VertexBuffer* _buffer;
	} _vertexArray;*/

	QVector<Nigel::geometry::mesh::Vertex> _vertices;
	QVector<Nigel::geometry::mesh::SharedVertexData> _verticesData;
};

}}}}
