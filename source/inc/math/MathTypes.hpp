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

#include <Types.hpp>

#include <memory>

#include <QtCore/QMetaType>

#include <KoreApplication.hpp>

// TODO: Add conversion routines (INLINE !)

namespace Nigel { namespace math {

template<typename T>
struct vec4
{
	vec4() { x = (T)0; y = (T)0; z = (T)0; w = (T)0; }
	T x;
	T y;
	T z;
	T w;
};

template<typename T>
struct vec3
{
	vec3() { x = (T)0; y = (T)0; z = (T)0; }
	T x;
	T y;
	T z;
};

template<typename T>
struct vec2
{
	vec2() { x = (T)0; y = (T)0; }
	T x;
	T y;
};

template<typename T, kint w, kint h>
struct mat
{
	mat() { memset(values,0x00,w*h*sizeof(T)); }
	T values[w*h];
};

struct NigelExport vec3f : vec3<kfloat>
{
};

struct NigelExport vec3i : vec3<kint>
{
};

struct NigelExport _K_SSE_ALIGNED vec4f : vec4<kfloat>
{
	vec4f() {}
	vec4f(const vec3f& v) { x = v.x; y = v.y; z = v.z; w = 0.0f; }
	vec4f(const vec3i& v) { x = (kfloat)v.x; y = (kfloat)v.y; z = (kfloat)v.z; w = 0.0f; }

	kvoid* operator new(ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	// This operator is only for QVector container and other containers that will manage the memory themselves.
	kvoid* operator new(ksize size, void* ptr) { K_ASSERT( K_IS_ALIGNED(ptr, _K_SSE_ALIGNMENT) ); return ptr; }
	// QVector does not call the delete operator for these types as it manages its memory by itself.
	void operator delete(kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
	kvoid* operator new[](ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	void operator delete[](kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
};

struct NigelExport vec4b : vec4<kbool>
{
};

struct NigelExport vec3b : vec3<kbool>
{
};

struct NigelExport vec3ui : vec3<kuint>
{
};

struct NigelExport vec2f : vec2<kfloat>
{
};

struct NigelExport vec2b : vec2<kbool>
{
};

struct NigelExport vec2i : vec2<kint>
{
};

struct NigelExport vec2ui : vec2<kuint>
{
};

struct NigelExport _K_SSE_ALIGNED mat4x4f : mat<kfloat,4,4>
{
	kvoid* operator new(ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	// This operator is only for QVector container and other containers that will manage the memory themselves.
	kvoid* operator new(ksize size, void* ptr) { K_ASSERT( K_IS_ALIGNED(ptr, _K_SSE_ALIGNMENT) ); return ptr; }
	// QVector does not call the delete operator for these types as it manages its memory by itself.
	void operator delete(kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
	kvoid* operator new[](ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	void operator delete[](kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
};

struct NigelExport mat3x3f : mat<kfloat,3,3>
{
};

struct NigelExport _K_SSE_ALIGNED quatf
{
	kfloat x;
	kfloat y;
	kfloat z;
	kfloat s;

	kvoid* operator new(ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	// This operator is only for QVector container and other containers that will manage the memory themselves.
	kvoid* operator new(ksize size, void* ptr) { K_ASSERT( K_IS_ALIGNED(ptr, _K_SSE_ALIGNMENT) ); return ptr; }
	// QVector does not call the delete operator for these types as it manages its memory by itself.
	void operator delete(kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
	kvoid* operator new[](ksize size) { return kApp->memoryManager()->mAlloc_a(size, _K_SSE_ALIGNMENT); }
	void operator delete[](kvoid* ptr) { kApp->memoryManager()->mFree_a(ptr); }
};

// Function pointers typedefs for Vector4f
typedef void	(*Vector4f_Add)				(vec4f& lVec, const vec4f& rVec);
typedef void	(*Vector4f_Assign)			(vec4f& dest, const vec4f& src);
typedef void	(*Vector4f_Clear)			(vec4f& vec);
typedef kfloat	(*Vector4f_Dot)				(const vec4f& lVec, const vec4f& rVec);
typedef kfloat	(*Vector4f_Length)			(const vec4f& vec);
typedef void	(*Vector4f_MulMatrix)		(vec4f& vec, const mat4x4f& mat);
typedef void	(*Vector4f_MulScalar)		(vec4f& vec, kfloat scalar);
typedef void	(*Vector4f_Normalize)		(vec4f& vec);
typedef void	(*Vector4f_Prod)			(vec4f& lVec, const vec4f& rVec);
typedef void	(*Vector4f_Sub)				(vec4f& lVec, const vec4f& rVec);

// Function pointers typedefs for Matrix4x4f
typedef void	(*Matrix4x4f_Assign)		(mat4x4f& dest, const mat4x4f& src);
typedef void	(*Matrix4x4f_BatchMultiply)	(vec4f* vecs, kuint vecsNb, const mat4x4f& mat);
typedef void	(*Matrix4x4f_Clear)			(mat4x4f& mat);
typedef kfloat	(*Matrix4x4f_Det)			(const mat4x4f& mat);
typedef void	(*Matrix4x4f_Identity)		(mat4x4f& mat);
typedef void	(*Matrix4x4f_Invert)		(mat4x4f& mat, kbool* inversible);
typedef void	(*Matrix4x4f_LookAt)		(mat4x4f& mat, const vec4f& pos, const vec4f& at, const vec4f& up);
typedef void	(*Matrix4x4f_MulMatrix)		(mat4x4f& lMat, const mat4x4f& rMat);
typedef void	(*Matrix4x4f_Rotation)		(mat4x4f& mat, kfloat x, kfloat y, kfloat z, kfloat angle);
typedef void	(*Matrix4x4f_Scale)			(mat4x4f& mat, kfloat kx, kfloat ky, kfloat kz);
typedef void	(*Matrix4x4f_Translation)	(mat4x4f& mat, kfloat x, kfloat y, kfloat z);
typedef void	(*Matrix4x4f_Transpose)		(mat4x4f& mat);

// Function pointers typedefs for Quaternionf
typedef void	(*Quaternionf_Add)			(quatf& lQuat, const quatf& rQuat);
typedef void	(*Quaternionf_Assign)		(quatf& dest, const quatf& src);
typedef void	(*Quaternionf_AssignVec)	(quatf& dest, const vec4f& vec, kfloat s);
typedef void	(*Quaternionf_Clear)		(quatf& quat);
typedef void	(*Quaternionf_Identity)		(quatf& quat);
typedef void	(*Quaternionf_Invert)		(quatf& quat);
typedef void	(*Quaternionf_LookAt)		(quatf& quat, const vec4f& center, const vec4f& to, const vec4f& up);
typedef kfloat	(*Quaternionf_Magnitude)	(const quatf& quat);
typedef void	(*Quaternionf_MulQuat)		(quatf& lQuat, const quatf& rQuat);
typedef void	(*Quaternionf_Normalize)	(quatf& quat);
typedef void	(*Quaternionf_RotateVec)	(vec4f& vec, const quatf& quat);
typedef void	(*Quaternionf_Rotation)		(quatf& quat, kfloat x, kfloat y, kfloat z, kfloat angle);
typedef void	(*Quaternionf_RotationMat)	(mat4x4f& mat, const quatf& quat);
typedef void	(*Quaternionf_FromMat)		(quatf& quat, const mat4x4f& mat);
typedef void	(*Quaternionf_AxisAngle)	(kfloat* data, const quatf& quat);
typedef void	(*Quaternionf_Sub)			(quatf& lQuat, const quatf& rQuat);

}}

// Qt metatypes declarations !
Q_DECLARE_METATYPE( Nigel::math::vec4f )
Q_DECLARE_METATYPE( Nigel::math::vec4b )

Q_DECLARE_METATYPE( Nigel::math::vec3f )
Q_DECLARE_METATYPE( Nigel::math::vec3b )
Q_DECLARE_METATYPE( Nigel::math::vec3i )
Q_DECLARE_METATYPE( Nigel::math::vec3ui )

Q_DECLARE_METATYPE( Nigel::math::vec2f )
Q_DECLARE_METATYPE( Nigel::math::vec2b )
Q_DECLARE_METATYPE( Nigel::math::vec2i )
Q_DECLARE_METATYPE( Nigel::math::vec2ui )

Q_DECLARE_METATYPE( Nigel::math::mat4x4f )
Q_DECLARE_METATYPE( Nigel::math::mat3x3f )

Q_DECLARE_METATYPE( Nigel::math::quatf )
