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

//#include <math/Matrix4x4f.hpp>
#include "../../inc/math/Matrix4x4f.hpp"
#include "../../inc/math/Quaternionf.hpp"
using namespace Nigel::math;

Matrix4x4f::Matrix4x4f(const Quaternionf& q)
{
	q.setRotationMatrix(*this);
}

Matrix4x4f& Matrix4x4f::lookAt(const Vector4f& pos, const Vector4f& at, const Vector4f& up)
{
	(*_LookAt)(_values, pos.values(), at.values(), up.values());
	return *this;
}

Matrix4x4f_Assign			Matrix4x4f::_Assign			= K_NULL;
Matrix4x4f_BatchMultiply	Matrix4x4f::_BatchMultiply	= K_NULL;
Matrix4x4f_Clear			Matrix4x4f::_Clear			= K_NULL;
Matrix4x4f_Det				Matrix4x4f::_Det			= K_NULL;
Matrix4x4f_Identity			Matrix4x4f::_Identity		= K_NULL;
Matrix4x4f_Invert			Matrix4x4f::_Invert			= K_NULL;
Matrix4x4f_LookAt			Matrix4x4f::_LookAt			= K_NULL;
Matrix4x4f_MulMatrix 		Matrix4x4f::_MulMatrix		= K_NULL;
Matrix4x4f_Rotation			Matrix4x4f::_Rotation		= K_NULL;
Matrix4x4f_Scale			Matrix4x4f::_Scale			= K_NULL;
Matrix4x4f_Translation		Matrix4x4f::_Translation	= K_NULL;
Matrix4x4f_Transpose		Matrix4x4f::_Transpose		= K_NULL;
