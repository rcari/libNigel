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

#include "../GeometricElement.hpp"

#include <COLLADA/ICollection.hpp>

namespace Nigel { namespace geometry { namespace mesh {

namespace buffer { class VertexBuffer; }

class Primitive;

class NigelExport Mesh
:	public Nigel::geometry::GeometricElement,
 	public Nigel::COLLADA::ICollection<Primitive>
{
	Q_OBJECT

	K_BLOCK

	friend class Primitive;
	friend class buffer::VertexBuffer;

private:
	Mesh();

public:
	inline buffer::VertexBuffer* verticesBuffer() { return _vertices; }
	inline const buffer::VertexBuffer* verticesBuffer() const { return _vertices; }

	kint primitivesNb() const;
	Primitive* primitive(kint i);

public:
	virtual Kore::data::Library* toLibrary() { return this; }
	virtual Nigel::COLLADA::Element* toElement() { return this; }

protected:
	virtual kint elementsOffset(Nigel::COLLADA::data::Source*) const;
	virtual kint elementsOffset(Primitive*) const;
	virtual void notifyElementRegistered(Primitive*);
	virtual kint elementsOffset(Nigel::COLLADA::extra::Extra*) const;

private:
	void registerVertices(buffer::VertexBuffer* vertices) { _vertices = vertices; }
	void unregisterVertices(buffer::VertexBuffer* vertices) { K_ASSERT( _vertices == vertices ); _vertices = K_NULL; }

private:
	buffer::VertexBuffer* _vertices;

public:
	static Mesh* CreateMesh();
};

}}}

#ifdef NIGEL_MSVC
#include <geometry/mesh/Primitive.hpp>
#endif
