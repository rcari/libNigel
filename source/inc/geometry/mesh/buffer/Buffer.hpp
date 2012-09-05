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

#pragma once

#include <NigelExport.hpp>

#include <COLLADA/data/Source.hpp>

namespace Nigel { namespace geometry { namespace mesh {

class Mesh;

namespace buffer {

class NigelExport Buffer : public Nigel::COLLADA::data::Source
{
	Q_OBJECT
	K_BLOCK

public:
	enum ElementType
	{
		Undefined = 0x00,
		Vertex,
		VertexAttribute,
		VertexMeshData,
		TriangleFace,
		QuadFace,
		FaceMeshData,
		Edge,
		Other,
	};

public:
	union BufferInfo
	{
		struct _TexCoordInfo
		{
			kint textureIndex;
		} TexCoordInfo;

		struct _VertexAttribInfo
		{
			kuint attribIndex;
		} VertexAttribInfo;
	};

protected:
	Buffer(ElementType type);

public:
	// For OpenGL.
	virtual const kvoid* data() const = K_NULL;
	virtual ksize dataSize() const = K_NULL;
	virtual ksize elementSize() const = K_NULL;
	virtual kint elementsNb() const = K_NULL;

	Nigel::geometry::mesh::Mesh* mesh();
	const Nigel::geometry::mesh::Mesh* mesh() const;

signals:
	void elementSizeChanged(ksize oldSize, ksize newSize);

	void appendingElements(kint elementsNb);
	void doneAppendingElements(kint elementsNb);

	void insertingElements(kint offset, kint elementsNb);
	void doneInsertingElements(kint offset, kint elementsNb);

	void updatingElements(kint offset, kint elementsNb);
	void doneUpdatingElements(kint offset, kint elementsNb);

	void removingElements(kint offset, kint elementsNb);
	void doneRemovingElements(kint offset, kint elementsNb);

	void bufferInfoChanged();

private:
	ElementType _type;
	BufferInfo _bufferInfo;
};

}}}}

#ifdef NIGEL_MSVC
#include <COLLADA/data/IArray.hpp>
#endif
