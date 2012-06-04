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

#include "MathTypes.hpp"
#include "Matrix4x4f.hpp"

namespace Nigel { namespace math {

class Vector4fRoutines;
class Quaternionf;

/*!
 * Vector4f class.
 *
 * Because of the implementation, avoid using this class on the heap except in large arrays.
 * Each allocation requires using the aligned memory allocator and might therefore be slowish compared to stack-based use.
 *
 */
class NigelExport _K_SSE_ALIGNED Vector4f
{
	friend class Vector4fRoutines;
	friend class Quaternionf;

public:
	enum ElementIndex {
		X = 0,
		Y,
		Z,
		W,
	};

public:
	inline Vector4f()
	{
	}

	inline Vector4f(kfloat x, kfloat y, kfloat z, kfloat w = 1.0f)
	{
		_values.x = x;
		_values.y = y;
		_values.z = z;
		_values.w = w;
	}

	inline Vector4f(const vec4f& vec)
	{
		(*_Assign)(_values, vec);
	}

	inline Vector4f(const Vector4f& vec)
	{
		(*_Assign)(values(), vec.values());
	}

	inline Vector4f& normalize() { (*_Normalize)(_values); return *this; }
	inline Vector4f normalized() const { Vector4f result(*this); result.normalize(); return result; }
	inline kfloat length() const { return (*_Length)(_values); }

	inline void storeValues(vec4f& vec) const { (*_Assign)(vec, _values); }

	inline void assignTo(vec4f& v) const { (*_Assign)(v, _values); }
	inline Vector4f& operator=(const vec4f& v) { (*_Assign)(_values, v); return *this; }
	inline Vector4f& operator=(const Vector4f& v) { (*_Assign)(_values, v._values); return *this; }

	inline kfloat operator*(const Vector4f& v) const { return (*_Dot)(_values, v._values); }

	inline void addTo(vec4f& v) const { (*_Add)(v, _values); }
	inline Vector4f operator+(const Vector4f& v) const { Vector4f result(*this); result += v; return result; }
	inline Vector4f& operator+=(const Vector4f& v) { (*_Add)(_values, v._values); return *this; }

	inline Vector4f operator-(const Vector4f& v) const { Vector4f result(*this); result -= v; return result; }
	inline Vector4f& operator-=(const Vector4f& v) { (*_Sub)(_values, v._values); return *this; }

	inline 	Vector4f operator^(const Vector4f& v) const { Vector4f result(*this); result ^= v; return result; }
	inline Vector4f& operator^=(const Vector4f& v) { (*_Prod)(_values, v._values); return *this; }

	inline 	Vector4f operator*(const Matrix4x4f& m) const { Vector4f result(*this); result *= m; return result; }
	inline Vector4f& operator*=(const Matrix4x4f& m) { (*_MulMatrix)(_values, m._values); return *this; }

	inline Vector4f operator*(kfloat f) const { Vector4f result(*this); result *= f; return result; }
	inline Vector4f& operator*=(kfloat f) { (*_MulScalar)(_values, f); return *this; }

	inline const kfloat& operator[](ElementIndex index) const { return (&_values.x)[index]; }
	inline kfloat& operator[](ElementIndex index) { return (&_values.x)[index]; }

	inline vec4f& values() { return _values; }
	inline const vec4f& values() const { return _values; }

public:
	kvoid* operator new(ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	// This operator is only for QVector container and other containers that will manage the memory themselves.
	kvoid* operator new(ksize size, void* ptr) { K_ASSERT( K_IS_ALIGNED(ptr, _K_SSE_ALIGNMENT) ); return ptr; }
	// QVector does not call the delete operator for these types as it manages its memory by itself.
	void operator delete(kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
	kvoid* operator new[](ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	void operator delete[](kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }

private:
	vec4f _values;

private:
	static Vector4f_Assign		_Assign;
	static Vector4f_Normalize	_Normalize;
	static Vector4f_Length		_Length;
	static Vector4f_Dot			_Dot;
	static Vector4f_Prod		_Prod;
	static Vector4f_Add			_Add;
	static Vector4f_Sub			_Sub;
	static Vector4f_MulScalar	_MulScalar;
	static Vector4f_MulMatrix	_MulMatrix;

};

}}
