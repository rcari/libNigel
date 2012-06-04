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

#include <COLLADA/Element.hpp>
#include "Mesh.hpp"
#include "Primitive.hpp"
#include "Structures.hpp"

#include <QtCore/QVector>

namespace Nigel { namespace geometry { namespace mesh {

class NigelExport Patch : public Primitive
{
	Q_OBJECT
	Q_PROPERTY( QString patchName READ blockName WRITE blockName STORED true DESIGNABLE false )
	Q_PROPERTY( int verticesOffset READ verticesOffset WRITE verticesOffset STORED true DESIGNABLE false FINAL )
	Q_PROPERTY( QByteArray verticesData READ verticesDataArray WRITE verticesDataArray STORED true DESIGNABLE false FINAL )
	Q_PROPERTY( QByteArray facesData READ facesDataArray WRITE facesDataArray STORED true DESIGNABLE false FINAL )
	Q_PROPERTY( QByteArray edges READ edgesArray WRITE edgesArray STORED true DESIGNABLE false FINAL )

	K_BLOCK

protected:
	Patch();

	virtual void library(Kore::data::Library*);

public:
	// Data access (for OpenGL, really...)
	virtual kvoid* indices() = K_NULL;
	virtual const kvoid* indices() const = K_NULL;
	virtual ksize count() const = K_NULL;

	inline Mesh* mesh() { return static_cast<Mesh*>(Library::library()); }
	inline const Mesh* mesh() const { return static_cast<const Mesh*>(Library::library()); }

	inline kint verticesOffset() const { return _verticesOffset; }
	inline kint verticesNb() const { return _verticesData.size(); }

	inline kint nextEdgeIndex(kint edgeIndex) const { return _edges.at(edgeIndex).nextEdge; }

	inline const Edge& nextEdge(kint edgeIndex) const { return _edges.at( nextEdgeIndex(edgeIndex) ); }
	inline Edge& nextEdge(kint edgeIndex) { return _edges[nextEdgeIndex(edgeIndex)]; }

	inline const Edge& nextEdge(const Edge& edge) const { return _edges.at( edge.nextEdge ); }
	inline Edge& nextEdge(const Edge& edge) { return _edges[edge.nextEdge]; }

	virtual kint prevEdgeIndex(kint edgeIndex) const = K_NULL;
	inline const Edge& prevEdge(kint edgeIndex) const { return _edges.at( prevEdgeIndex(edgeIndex) ); }
	inline Edge& prevEdge(kint edgeIndex) { return _edges[prevEdgeIndex(edgeIndex)]; }

	virtual QList<kint> adjacentFaces(kint faceIndex) const = K_NULL;
	QList<kint> faceEdges(kint faceIndex) const;
	QList<kint> vertexEdges(kint localVertexIndex) const;
	QList<kint> vertexFaces(kint localVertexIndex) const;

public:
	// Convenience methods.
	kint insertVertices(kint offset, kint number);
	void doneInsertingVertices(kint offset, kint number);

	kint appendVertices(kint number);
	void doneAppendingVertices(kint number);

	void removeVertices(kint offset, kint number);
	void doneRemovingVertices(kint offset, kint number);

	void updateVertices(kint offset, kint number);
	void doneUpdatingVertices(kint offset, kint number);

private slots:
	// These private slots are used to update the _verticesOffset value.
	void insertingVerticesInBuffer(kint offset ,kint number);
	void removingVerticesFromBuffer(kint offset, kint number);

private:
	// For serialization purposes.
	void verticesOffset(kint offset);

	QByteArray verticesDataArray() const;
	void verticesDataArray(const QByteArray&);

	QByteArray facesDataArray() const;
	void facesDataArray(const QByteArray&);

	QByteArray edgesArray() const;
	void edgesArray(const QByteArray&);

signals:
	void appendingFaces(kint facesNb);
	void doneAppendingFaces(kint facesNb);

	void insertingFaces(kint offset, kint facesNb);
	void doneInsertingFaces(kint offset, kint facesNb);

	void updatingFaces(kint offset, kint facesNb);
	void doneUpdatingFaces(kint offset, kint facesNb);

	void removingFaces(kint offset, kint facesNb);
	void doneRemovingFaces(kint offset, kint facesNb);

private:
	kint _verticesOffset;
	kbool _changingLocalVertices;

protected:
	QVector<VertexData> _verticesData;
	QVector<FaceMeshData> _facesData;
	QVector<Edge> _edges;

};

}}}
