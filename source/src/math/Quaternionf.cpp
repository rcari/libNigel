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

#include "../../inc/math/Quaternionf.hpp"
#include "../../inc/math/Matrix4x4f.hpp"
using namespace Nigel::math;

Quaternionf_Add			Quaternionf::_Add			= K_NULL;
Quaternionf_Assign		Quaternionf::_Assign		= K_NULL;
Quaternionf_AssignVec	Quaternionf::_AssignVec		= K_NULL;
Quaternionf_Clear		Quaternionf::_Clear			= K_NULL;
Quaternionf_FromMat		Quaternionf::_FromMat		= K_NULL;
Quaternionf_Identity	Quaternionf::_Identity		= K_NULL;
Quaternionf_Invert		Quaternionf::_Invert		= K_NULL;
Quaternionf_LookAt		Quaternionf::_LookAt		= K_NULL;
Quaternionf_Magnitude	Quaternionf::_Magnitude		= K_NULL;
Quaternionf_MulQuat		Quaternionf::_MulQuat		= K_NULL;
Quaternionf_Normalize	Quaternionf::_Normalize		= K_NULL;
Quaternionf_RotateVec	Quaternionf::_RotateVec		= K_NULL;
Quaternionf_Rotation	Quaternionf::_Rotation		= K_NULL;
Quaternionf_RotationMat	Quaternionf::_RotationMat	= K_NULL;
Quaternionf_AxisAngle	Quaternionf::_AxisAngle		= K_NULL;
Quaternionf_Sub			Quaternionf::_Sub			= K_NULL;
