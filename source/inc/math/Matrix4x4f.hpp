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

namespace Nigel { namespace math {

class Quaternionf;
class Vector4f;

class Matrix4x4fRoutines;

class NigelExport _K_SSE_ALIGNED Matrix4x4f
{
	friend class Matrix4x4fRoutines;

	friend class Quaternionf;
	friend class Vector4f;

public:
	/*!
	 * Create a null matrix (filled with 0s).
	 * @return a null matrix.
	 */
	inline Matrix4x4f() { (*_Clear)(_values); }
	/*!
	 * Copy constructor.
	 * @param m matrix to copy
	 * @return copy of m.
	 */
	inline Matrix4x4f(const mat4x4f& m) { (*_Assign)(_values, m); }
	/*!
	 * Copy constructor.
	 * @param m matrix to copy.
	 * @return copy of m.
	 */
	inline Matrix4x4f(const Matrix4x4f& m) { (*_Assign)(_values, m._values); }
	/*!
	 * Rotation matrix constructor.
	 * @param axis rotation axis.
	 * @param angle rotation angle.
	 * @return a rotation matrix.
	 */
	inline Matrix4x4f(const vec3f& axis, kfloat angle) { (*_Rotation)(_values, axis.x, axis.y, axis.z, angle); }

	Matrix4x4f(const Quaternionf& q);

	/*!
	 * Const array accessor.
	 * @return
	 */
	inline const kfloat* values() const { return _values.values; }
	/*!
	 * Array accessor.
	 * @return
	 */
	inline kfloat* values() { return _values.values; }

	/*!
	 * Store the matrix
	 */
	inline void assign(mat4x4f& m) const { (*_Assign)(m, _values); }

	/*!
	 * Matrix multiplication (slower than in-memory).
	 * @param m
	 * @return
	 */
	inline Matrix4x4f operator*(const Matrix4x4f& m) const { Matrix4x4f result(*this); result *= m; return result; }
	/*!
	 * Matrix multiplication.
	 * @param m
	 * @return
	 */
	inline Matrix4x4f& operator*=(const Matrix4x4f& m) { (*_MulMatrix)(_values, m._values); return *this; }
	/*!
	 * Multiplies a vector array of number elements by the Matrix.
	 * @param vectors vectors to multiply.
	 * @param number number of vectors to multiply.
	 */
	inline void batchMultiply(vec4f* vectors, kint number) const { (*_BatchMultiply)(vectors, number, _values); }

	/*!
	 * Direct member accessor.
	 * @param i index of the element to access.
	 * @return reference to the element.
	 */
	inline kfloat& operator[](kindex i) { return _values.values[i]; }
	/*!
	 * Direct member const accessor.
	 * @param i index of the element to access.
	 * @return reference to the element.
	 */
	inline const kfloat& operator[](kindex i) const { return _values.values[i]; }

	/*!
	 * Assignment operator.
	 * @param m matrix to copy in this matrix.
	 * @return reference to this matrix.
	 */
	inline Matrix4x4f& operator=(const Matrix4x4f& m) { (*_Assign)(_values, m._values); return *this; }

	/*!
	 * Load the identity matrix in this matrix.
	 * @return reference to this matrix.
	 */
	inline Matrix4x4f& identity() { (*_Identity)(_values); return *this; }

	/*!
	 * Load a rotation matrix in this matrix.
	 * @param x x axis component.
	 * @param y y axis component.
	 * @param z z axis component.
	 * @param angle rotation angle.
	 * @return reference to this matrix.
	 */
	inline Matrix4x4f& rotation(kfloat x, kfloat y, kfloat z, kfloat angle) { (*_Rotation)(_values, x, y, z, angle); return *this; }
	/*!
	 * Load a scale matrix in this matrix.
	 * @param kx x scale factor.
	 * @param ky y scale factor.
	 * @param kz z scale factor.
	 * @return reference to this matrix.
	 */
	inline Matrix4x4f& scale(kfloat kx, kfloat ky, kfloat kz) { (*_Scale)(_values, kx, ky, kz); return *this; }

	/*!
	 * Load a translation matrix in this matrix.
	 * @param x x component.
	 * @param y y component.
	 * @param z z component.
	 * @return reference to this matrix.
	 */
	inline Matrix4x4f& translation(kfloat x, kfloat y, kfloat z) { (*_Translation)(_values, x, y ,z); return *this; }

	/*!
	 * Transpose of the matrix.
	 * @return the transpose of this matrix.
	 */
	inline Matrix4x4f transposed() const { Matrix4x4f result(*this); result.transpose(); return result; }

	/*!
	 * Transpose of the matrix.
	 *
	 * Transpose this matrix.
	 *
	 * @return a reference to this matrix,
	 */
	inline Matrix4x4f& transpose() { (*_Transpose)(_values); return *this; }

	/*!
	 * Look at matrix.
	 *
	 * Creates the lookAt matrix based on the parameters.
	 * @param pos Camera position.
	 * @param at Target position.
	 * @param up Up vector.
	 *
	 * @return reference to this matrix.
	 */
	Matrix4x4f& lookAt(const Vector4f& pos, const Vector4f& at, const Vector4f& up);

	/*!
	 * Determinant of the matrix.
	 * @return this matrix determinant.
	 */
	inline kfloat det() const { return (*_Det)(_values); }

	/*!
	 * Inverse matrix.
	 *
	 * If inversible != K_NULL, *inversible is set to TRUE if the matrix is inversible, false otherwise.
	 *
	 * @param inversible pointer to a kbool
	 * @return the inverse of this matrix.
	 */
	inline Matrix4x4f inverse(kbool* inversible = K_NULL) const { Matrix4x4f result(*this); result.invert(inversible); return result; }

	/*!
	 * Inverse matrix.
	 *
	 * This method inverses this matrix (in-memory).
	 * If inversible != K_NULL, *inversible is set to TRUE if the matrix is inversible, false otherwise.
	 *
	 * @param inversible pointer to a kbool
	 * @return reference to this matrix.
	 */
	inline Matrix4x4f& invert(kbool* inversible = K_NULL) { (*_Invert)(_values, inversible); return *this; }

	/*!
	 * Set all values to 0.0f
	 */
	inline void clear() { (*_Clear)(_values); }

public:
	kvoid* operator new(ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	// This operator is only for QVector container and other containers that will manage the memory themselves.
	kvoid* operator new(ksize size, void* ptr) { K_ASSERT( K_IS_ALIGNED(ptr, _K_SSE_ALIGNMENT) ); return ptr; }
	// QVector does not call the delete operator for these types as it manages its memory by itself.
	void operator delete(kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
	kvoid* operator new[](ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	void operator delete[](kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }

private:
	mat4x4f _K_SSE_ALIGNED  _values;

private:
	static Matrix4x4f_Assign		_Assign;
	static Matrix4x4f_BatchMultiply _BatchMultiply;
	static Matrix4x4f_Clear			_Clear;
	static Matrix4x4f_Det			_Det;
	static Matrix4x4f_Identity		_Identity;
	static Matrix4x4f_Invert		_Invert;
	static Matrix4x4f_LookAt		_LookAt;
	static Matrix4x4f_MulMatrix 	_MulMatrix;
	static Matrix4x4f_Rotation		_Rotation;
	static Matrix4x4f_Scale			_Scale;
	static Matrix4x4f_Translation	_Translation;
	static Matrix4x4f_Transpose		_Transpose;

};

}}
