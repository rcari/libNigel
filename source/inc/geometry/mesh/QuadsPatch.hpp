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

#include "Patch.hpp"
#include "buffer/VertexBuffer.hpp"

namespace Nigel { namespace geometry { namespace mesh {

class NigelExport QuadsPatch : public Patch
{
	Q_OBJECT
	Q_PROPERTY( QVariant quads READ quadsArray WRITE quadsArray STORED true DESIGNABLE false FINAL )

	K_BLOCK

protected:
	QuadsPatch();

public:
	virtual kvoid* indices();
	virtual const kvoid* indices() const;
	virtual ksize count() const;

	inline Vertex* vertices() { return &( mesh()->verticesBuffer()->vertices()[this->verticesOffset()] ); }

	virtual kint prevEdgeIndex(kint edgeIndex) const;

	kint edgeStartVertexIndex(const Edge& edge) const;

	inline kint firstEdgeIndex(kint faceIndex) const { return _facesData.at(faceIndex).firstEdge; }
	inline kint secondEdgeIndex(kint faceIndex) const { return nextEdgeIndex(firstEdgeIndex(faceIndex)); }
	inline kint thirdEdgeIndex(kint faceIndex) const { return nextEdgeIndex(secondEdgeIndex(faceIndex)); }
	inline kint fourthEdgeIndex(kint faceIndex) const { return nextEdgeIndex(thirdEdgeIndex(faceIndex)); }

	kint appendQuads(kint number);
	void doneAppendingQuads(kint number);

	void insertQuads(kint offset, kint nb);
	void doneInsertingQuads(kint offset, kint nb);

	void updatingQuads(kint offset, kint nb);
	void doneUpdatingQuads(kint offset, kint nb);

	void removeQuads(kint offset, kint nb);
	void doneRemovingQuads(kint offset, kint nb);

	virtual QList<kint> adjacentFaces(kint faceIndex) const;

private:
	void initializeEdges(kint facesOffset, kint facesNumber);
	kint findPairEdgeIndex(const Edge& edge) const;

private:
	QVariant quadsArray() const;
	void quadsArray(const QVariant& v);

private:
	QVector<QuadFace> _quads;
};

}}}
