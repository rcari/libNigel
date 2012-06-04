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

#include <math/MathTypes.hpp>

namespace Nigel { namespace geometry { namespace mesh {

struct NigelExport Edge
{
	Edge() { endVertex = -1; pairEdge = -1; face = -1; nextEdge = -1; }
	kint endVertex; //! Index of the edge's vertex.
	kint pairEdge; //! Index of the opposite edge.
	kint face; //! Index of the face.
	kint nextEdge; //! Index of the next edge in the face (CounterClockWise polygon winding).
};

struct NigelExport TriangleFace
{
	TriangleFace() { v0 = -1; v1 = -1; v2 = -1; } // 0xffffffff
	kint v0;
	kint v1;
	kint v2;
};

struct NigelExport QuadFace
{
	QuadFace() { v0 = -1; v1 = -1; v2 = -1; v3 = -1; } // 0xffffffff
	kint v0;
	kint v1;
	kint v2;
	kint v3;
};

struct NigelExport FaceMeshData
{
	FaceMeshData() { firstEdge = -1; }
	kint firstEdge;
};

struct NigelExport _K_SSE_ALIGNED Vertex : Nigel::math::vec4f
{
	Vertex() { this->w = 1.0f; }
	Vertex(kfloat x, kfloat y, kfloat z) { this->x = x; this->y = y; this->z = z; this->w = 1.0f; }

	kvoid* operator new(ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	// This operator is only for QVector container and other containers that will manage the memory themselves.
	kvoid* operator new(ksize size, void* ptr) { K_ASSERT( K_IS_ALIGNED(ptr, _K_SSE_ALIGNMENT) ); return ptr; }
	// QVector does not call the delete operator for these types as it manages its memory by itself.
	void operator delete(kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
	kvoid* operator new[](ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	void operator delete[](kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
};

struct NigelExport VertexData
{
	VertexData() { edge = -1; }
	kint edge; //! Index of the vertex's edge.
};

struct NigelExport SharedVertexData
{
	SharedVertexData() { nextSharedVertex = -1; }
	kint nextSharedVertex; //! Index of a shared vertex.
};

// Vertex attributes.

struct NigelExport _K_SSE_ALIGNED Normal : Nigel::math::vec4f
{
	Normal() {}
	Normal(kfloat x, kfloat y, kfloat z) { this->x = x; this->y = y; this->z = z; }

	kvoid* operator new(ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	// This operator is only for QVector container and other containers that will manage the memory themselves.
	kvoid* operator new(ksize size, void* ptr) { K_ASSERT( K_IS_ALIGNED(ptr, _K_SSE_ALIGNMENT) ); return ptr; }
	// QVector does not call the delete operator for these types as it manages its memory by itself.
	void operator delete(kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
	kvoid* operator new[](ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	void operator delete[](kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
};

struct NigelExport FogCoord
{
	kfloat d;
};

struct NigelExport Color3f
{
	kfloat r;
	kfloat g;
	kfloat b;
};

struct NigelExport Color3i
{
	kbyte r;
	kbyte g;
	kbyte b;
};

struct NigelExport Color4f
{
	kfloat r;
	kfloat g;
	kfloat b;
	kfloat a;
};

struct NigelExport Color4i
{
	kbyte r;
	kbyte g;
	kbyte b;
	kbyte a;
};

struct NigelExport TexCoord2f : Nigel::math::vec2f
{
	inline void u(kfloat f) { x = f; }
	inline kfloat u() const { return x; }
	inline void v(kfloat f) { y = f; }
	inline kfloat v() const { return y; }
};

struct NigelExport TexCoord3f : Nigel::math::vec3f
{
	inline void u(kfloat f) { x = f; }
	inline kfloat u() const { return x; }
	inline void v(kfloat f) { y = f; }
	inline kfloat v() const { return y; }
	inline void w(kfloat f) { z = f; }
	inline kfloat w() const { return z; }
};

}}}
