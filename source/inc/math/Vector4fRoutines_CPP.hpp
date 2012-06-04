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

#include "Vector4fRoutines.hpp"
#include "MathEngine.hpp"

namespace Nigel { namespace math {

class Vector4fRoutines_CPP : public Vector4fRoutines
{
	K_MATH_ROUTINES

public:
	Vector4fRoutines_CPP();

	virtual kint routinePerformanceScore(Routine routine) const;
	virtual void installRoutine(Routine routine) const;

private:
	static void AddImpl(vec4f& lVec, const vec4f& rVec);
	static void	AssignImpl(vec4f& dest, const vec4f& src);
	static void ClearImpl(vec4f& vec);
	static kfloat DotImpl(const vec4f& lVec, const vec4f& rVec);
	static kfloat LengthImpl(const vec4f& vec);
	static void MulMatrixImpl(vec4f& vec, const mat4x4f& mat);
	static void MulScalarImpl(vec4f& vec, kfloat scalar);
	static void NormalizeImpl(vec4f& vec);
	static void ProdImpl(vec4f& lVec, const vec4f& rVec);
	static void	SubImpl(vec4f& lVec, const vec4f& rVec);
};

}}
