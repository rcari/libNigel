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

#include "Matrix4x4fRoutines.hpp"

namespace Nigel { namespace math {

class NigelExport Matrix4x4fRoutines_SSE : public Matrix4x4fRoutines
{
	K_MATH_ROUTINES

public:
	Matrix4x4fRoutines_SSE();

	virtual kint routinePerformanceScore(Routine routine) const;
	virtual void installRoutine(Routine routine) const;

private:
	static void AssignImpl(mat4x4f& dest, const mat4x4f& src);
	static void BatchMultiplyImpl(vec4f* vecs, kuint vecsNb, const mat4x4f& mat);
	static void ClearImpl(mat4x4f& mat);
	static kfloat DetImpl(const mat4x4f& mat);
	static void IdentityImpl(mat4x4f& mat);
	static void InvertImpl(mat4x4f& mat, kbool* inversible);
	static void LookAtImpl(mat4x4f& mat, const vec4f& pos, const vec4f& at, const vec4f& up);
	static void MulMatrixImpl(mat4x4f& lMat, const mat4x4f& rMat);
	static void RotationImpl(mat4x4f& mat, kfloat x, kfloat y, kfloat z, kfloat angle);
	static void ScaleImpl(mat4x4f& mat, kfloat kx, kfloat ky, kfloat kz);
	static void TranslationImpl(mat4x4f& mat, kfloat x, kfloat y, kfloat z);
	static void TransposeImpl(mat4x4f& mat);
};

}}
