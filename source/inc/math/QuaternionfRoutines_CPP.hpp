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

#include "QuaternionfRoutines.hpp"

namespace Nigel { namespace math {

class NigelExport QuaternionfRoutines_CPP : public QuaternionfRoutines
{
	K_MATH_ROUTINES

public:
	QuaternionfRoutines_CPP();

	virtual kint routinePerformanceScore(Routine routine) const;
	virtual void installRoutine(Routine routine) const;

private:
	static void AddImpl(quatf& lQuat, const quatf& rQuat);
	static void	AssignImpl(quatf& dest, const quatf& src);
	static void AssignVecImpl(quatf& dest, const vec4f& src, kfloat s);
	static void AxisAngleImpl(kfloat* data, const quatf& quat);
	static void	ClearImpl(quatf& quat);
	static void FromMatImpl(quatf& quat, const mat4x4f& mat);
	static void	IdentityImpl(quatf& quat);
	static void	InvertImpl(quatf& quat);
	static void	LookAtImpl(quatf& quat, const vec4f& center, const vec4f& to, const vec4f& up);
	static kfloat MagnitudeImpl(const quatf& quat);
	static void	MulQuatImpl(quatf& lQuat, const quatf& rQuat);
	static void	NormalizeImpl(quatf& quat);
	static void	RotateVecImpl(vec4f& vec, const quatf& quat);
	static void	RotationImpl(quatf& quat, kfloat x, kfloat y, kfloat z, kfloat angle);
	static void	RotationMatImpl(mat4x4f& mat, const quatf& quat);
	static void	SubImpl(quatf& lQuat, const quatf& rQuat);
};

}}
