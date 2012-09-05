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

#include <math/Matrix4x4fRoutines_CPP.hpp>
#include <math/Math.hpp>
using namespace Nigel::math;

#include <memory>

K_MATH_ROUTINES_I( Nigel::math::Matrix4x4fRoutines_CPP )

Matrix4x4fRoutines_CPP::Matrix4x4fRoutines_CPP()
{
	blockName("Matrix4x4f C++ routines");
}

kint Matrix4x4fRoutines_CPP::routinePerformanceScore(Routine routine) const
{
	return 0;
}

void Matrix4x4fRoutines_CPP::installRoutine(Routine routine) const
{
	switch(routine)
	{
	case Assign:
		doInstallRoutine(Assign, reinterpret_cast<kvoid*>(&AssignImpl));
		break;
	case BatchMultiply:
		doInstallRoutine(BatchMultiply, reinterpret_cast<kvoid*>(&BatchMultiplyImpl));
		break;
	case Clear:
		doInstallRoutine(Clear, reinterpret_cast<kvoid*>(&ClearImpl));
		break;
	case Det:
		doInstallRoutine(Det, reinterpret_cast<kvoid*>(&DetImpl));
		break;
	case Identity:
		doInstallRoutine(Identity, reinterpret_cast<kvoid*>(&IdentityImpl));
		break;
	case Invert:
		doInstallRoutine(Invert, reinterpret_cast<kvoid*>(&InvertImpl));
		break;
	case LookAt:
		doInstallRoutine(LookAt, reinterpret_cast<kvoid*>(&LookAtImpl));
		break;
	case MulMatrix:
		doInstallRoutine(MulMatrix, reinterpret_cast<kvoid*>(&MulMatrixImpl));
		break;
	case Rotation:
		doInstallRoutine(Rotation, reinterpret_cast<kvoid*>(&RotationImpl));
		break;
	case Scale:
		doInstallRoutine(Scale, reinterpret_cast<kvoid*>(&ScaleImpl));
		break;
	case Translation:
		doInstallRoutine(Translation, reinterpret_cast<kvoid*>(&TranslationImpl));
		break;
	case Transpose:
		doInstallRoutine(Transpose, reinterpret_cast<kvoid*>(&TransposeImpl));
		break;
	default:
		break;
	}
}

void Matrix4x4fRoutines_CPP::AssignImpl(mat4x4f& dest, const mat4x4f& src)
{
	dest = src;
}

void Matrix4x4fRoutines_CPP::BatchMultiplyImpl(vec4f* vecs, kuint vecsNb, const mat4x4f& mat)
{
	Matrix4x4f matrix(mat);
	for(kuint i = 0; i < vecsNb; i++)
	{
		Vector4f vec(vecs[i]);
		vec *= matrix;
		vec.storeValues(vecs[i]);
	}
}

void Matrix4x4fRoutines_CPP::ClearImpl(mat4x4f& mat)
{
	memset(&mat, 0x00, sizeof(mat4x4f));
}

kfloat Matrix4x4fRoutines_CPP::DetImpl(const mat4x4f& mat)
{
	// Using LaPlace's thingy.
	// The matrix is a TRANSFORMATION matrix, we can make some assumptions
	//	[ a b c . ]
	//	[ d e f . ]
	//	[ g h i . ]
	//	[ 0 0 0 1 ] <-- That's interesting !

	// TODO: A full implementation !

	// det mat = aei + bfg + cdh - afh - bdi - ceg
	return mat.values[0]*mat.values[5]*mat.values[10] +
		mat.values[1]*mat.values[6]*mat.values[8] +
		mat.values[2]*mat.values[4]*mat.values[9] -
		mat.values[0]*mat.values[6]*mat.values[9] -
		mat.values[1]*mat.values[4]*mat.values[10] -
		mat.values[2]*mat.values[5]*mat.values[8];

}

void Matrix4x4fRoutines_CPP::IdentityImpl(mat4x4f& mat)
{
	ClearImpl(mat);
	mat.values[0] = 1.0f;
	mat.values[5] = 1.0f;
	mat.values[10] = 1.0f;
	mat.values[15] = 1.0f;
}

void Matrix4x4fRoutines_CPP::InvertImpl(mat4x4f& mat, kbool* inversible)
{
	// Source: http://developer.intel.com/design/pentiumiii/sml/245043.htm

	float tmp[12]; /* temp array for pairs */
	//float src[16]; /* array of transpose source matrix */
	float det;     /* determinant */

	/* transpose matrix */
	mat4x4f src = mat;
	TransposeImpl(src);

	/* transpose matrix */
	/*for(int i = 0; i < 4; i++)
	{
		src[i]        = mat.values[i*4];
		src[i + 4]    = mat.values[i*4 + 1];
		src[i + 8]    = mat.values[i*4 + 2];
		src[i + 12]   = mat.values[i*4 + 3];
	}*/

	/* calculate pairs for first 8 elements (cofactors) */
	tmp[0]  = src.values[10] * src.values[15];
	tmp[1]  = src.values[11] * src.values[14];
	tmp[2]  = src.values[9]  * src.values[15];
	tmp[3]  = src.values[11] * src.values[13];
	tmp[4]  = src.values[9]  * src.values[14];
	tmp[5]  = src.values[10] * src.values[13];
	tmp[6]  = src.values[8]  * src.values[15];
	tmp[7]  = src.values[11] * src.values[12];
	tmp[8]  = src.values[8]  * src.values[14];
	tmp[9]  = src.values[10] * src.values[12];
	tmp[10] = src.values[8]  * src.values[13];
	tmp[11] = src.values[9]  * src.values[12];

	/* calculate first 8 elements (cofactors) */
	mat.values[0]  = tmp[0]*src.values[5] + tmp[3]*src.values[6] + tmp[4]*src.values[7];
	mat.values[0] -= tmp[1]*src.values[5] + tmp[2]*src.values[6] + tmp[5]*src.values[7];
	mat.values[1]  = tmp[1]*src.values[4] + tmp[6]*src.values[6] + tmp[9]*src.values[7];
	mat.values[1] -= tmp[0]*src.values[4] + tmp[7]*src.values[6] + tmp[8]*src.values[7];
	mat.values[2]  = tmp[2]*src.values[4] + tmp[7]*src.values[5] + tmp[10]*src.values[7];
	mat.values[2] -= tmp[3]*src.values[4] + tmp[6]*src.values[5] + tmp[11]*src.values[7];
	mat.values[3]  = tmp[5]*src.values[4] + tmp[8]*src.values[5] + tmp[11]*src.values[6];
	mat.values[3] -= tmp[4]*src.values[4] + tmp[9]*src.values[5] + tmp[10]*src.values[6];
	mat.values[4]  = tmp[1]*src.values[1] + tmp[2]*src.values[2] + tmp[5]*src.values[3];
	mat.values[4] -= tmp[0]*src.values[1] + tmp[3]*src.values[2] + tmp[4]*src.values[3];
	mat.values[5]  = tmp[0]*src.values[0] + tmp[7]*src.values[2] + tmp[8]*src.values[3];
	mat.values[5] -= tmp[1]*src.values[0] + tmp[6]*src.values[2] + tmp[9]*src.values[3];
	mat.values[6]  = tmp[3]*src.values[0] + tmp[6]*src.values[1] + tmp[11]*src.values[3];
	mat.values[6] -= tmp[2]*src.values[0] + tmp[7]*src.values[1] + tmp[10]*src.values[3];
	mat.values[7]  = tmp[4]*src.values[0] + tmp[9]*src.values[1] + tmp[10]*src.values[2];
	mat.values[7] -= tmp[5]*src.values[0] + tmp[8]*src.values[1] + tmp[11]*src.values[2];

	/* calculate pairs for second 8 elements (cofactors) */
	tmp[0]  = src.values[2]*src.values[7];
	tmp[1]  = src.values[3]*src.values[6];
	tmp[2]  = src.values[1]*src.values[7];
	tmp[3]  = src.values[3]*src.values[5];
	tmp[4]  = src.values[1]*src.values[6];
	tmp[5]  = src.values[2]*src.values[5];
	tmp[6]  = src.values[0]*src.values[7];
	tmp[7]  = src.values[3]*src.values[4];
	tmp[8]  = src.values[0]*src.values[6];
	tmp[9]  = src.values[2]*src.values[4];
	tmp[10] = src.values[0]*src.values[5];
	tmp[11] = src.values[1]*src.values[4];

	/* calculate second 8 elements (cofactors) */
	mat.values[8]  = tmp[0]*src.values[13] + tmp[3]*src.values[14] + tmp[4]*src.values[15];
	mat.values[8] -= tmp[1]*src.values[13] + tmp[2]*src.values[14] + tmp[5]*src.values[15];
	mat.values[9]  = tmp[1]*src.values[12] + tmp[6]*src.values[14] + tmp[9]*src.values[15];
	mat.values[9] -= tmp[0]*src.values[12] + tmp[7]*src.values[14] + tmp[8]*src.values[15];
	mat.values[10] = tmp[2]*src.values[12] + tmp[7]*src.values[13] + tmp[10]*src.values[15];
	mat.values[10]-= tmp[3]*src.values[12] + tmp[6]*src.values[13] + tmp[11]*src.values[15];
	mat.values[11] = tmp[5]*src.values[12] + tmp[8]*src.values[13] + tmp[11]*src.values[14];
	mat.values[11]-= tmp[4]*src.values[12] + tmp[9]*src.values[13] + tmp[10]*src.values[14];
	mat.values[12] = tmp[2]*src.values[10] + tmp[5]*src.values[11] + tmp[1]*src.values[9];
	mat.values[12]-= tmp[4]*src.values[11] + tmp[0]*src.values[9] + tmp[3]*src.values[10];
	mat.values[13] = tmp[8]*src.values[11] + tmp[0]*src.values[8] + tmp[7]*src.values[10];
	mat.values[13]-= tmp[6]*src.values[10] + tmp[9]*src.values[11] + tmp[1]*src.values[8];
	mat.values[14] = tmp[6]*src.values[9] + tmp[11]*src.values[11] + tmp[3]*src.values[8];
	mat.values[14]-= tmp[10]*src.values[11] + tmp[2]*src.values[8] + tmp[7]*src.values[9];
	mat.values[15] = tmp[10]*src.values[10] + tmp[4]*src.values[8] + tmp[9]*src.values[9];
	mat.values[15]-= tmp[8]*src.values[9] + tmp[11]*src.values[10] + tmp[5]*src.values[8];

	/* calculate determinant */
	det=src.values[0]*mat.values[0]+src.values[1]*mat.values[1]+src.values[2]*mat.values[2]+src.values[3]*mat.values[3];

	if(!qFuzzyCompare(1.0f, 1.0f + det))
	{
		if(inversible)
		{
			*inversible = false;
		}
		return;
	}

	if(inversible)
	{
		*inversible = true;
	}

	/* calculate matrix inverse */
	det = 1.0f / det;

	for(int j = 0; j < 16; j++)
	{
		mat.values[j] *= det;
	}
}

void Matrix4x4fRoutines_CPP::LookAtImpl(mat4x4f& mat, const vec4f& pos, const vec4f& at, const vec4f& up)
{
	Vector4f forward(at), side, finalUp;
	forward -= pos;
	forward.normalize();

	side = forward ^ up;
	side.normalize();

	finalUp = side ^ forward;

	// Clear this matrix
	ClearImpl(mat);

	kfloat* vals = mat.values;
	vals[ 0] = side.values().x; vals[ 1] = finalUp.values().x;	vals[ 2] = -forward.values().x;
	vals[ 4] = side.values().y;	vals[ 5] = finalUp.values().y;	vals[ 6] = -forward.values().y;
	vals[ 8] = side.values().z; vals[ 9] = finalUp.values().z;	vals[10] = -forward.values().z;

	// Apply the translation !
	mat4x4f translation;
	TranslationImpl(translation, -pos.x, -pos.y, -pos.z);

	MulMatrixImpl(mat, translation);
}

void Matrix4x4fRoutines_CPP::MulMatrixImpl(mat4x4f& lMat, const mat4x4f& rMat)
{
	mat4x4f mat = lMat;
	for(kint i = 0; i < 4; ++i)
	{
		/*for(kint j = 0; j < 4; ++j)
		{
			lMat.values[4*i+j] =
					mat.values[ 4*i     ]*rMat.values[ j      ] +
					mat.values[ 4*i + 1 ]*rMat.values[ j + 4  ] +
					mat.values[ 4*i + 2 ]*rMat.values[ j + 8  ] +
					mat.values[ 4*i + 3 ]*rMat.values[ j + 12 ];
		}*/

		// Local speedup ?
		kfloat x = mat.values[4*i+0];
		kfloat y = mat.values[4*i+1];
		kfloat z = mat.values[4*i+2];
		kfloat w = mat.values[4*i+3];

		lMat.values[4*i+0] = x*rMat.values[0] + y*rMat.values[4] + z*rMat.values[ 8] + w*rMat.values[12];
		lMat.values[4*i+1] = x*rMat.values[1] + y*rMat.values[5] + z*rMat.values[ 9] + w*rMat.values[13];
		lMat.values[4*i+2] = x*rMat.values[2] + y*rMat.values[6] + z*rMat.values[10] + w*rMat.values[14];
		lMat.values[4*i+3] = x*rMat.values[3] + y*rMat.values[7] + z*rMat.values[11] + w*rMat.values[15];
	}
}

void Matrix4x4fRoutines_CPP::RotationImpl(mat4x4f& mat, kfloat x, kfloat y, kfloat z, kfloat angle)
{
	ClearImpl(mat);
	// See: http://en.wikipedia.org/wiki/Rotation_matrix#Axis_and_angle

	kfloat c = Math::Cosf(angle);	kfloat s = Math::Sinf(angle);	kfloat C = 1.0f - c;
	kfloat xs = x*s;				kfloat ys = y*s;				kfloat zs = z*s;
	kfloat xC = x*C;				kfloat yC = y*C;				kfloat zC = z*C;
	kfloat xyC = x*yC;				kfloat yzC = y*zC;				kfloat zxC = z*xC;

	mat.values[ 0] = x*xC+c;	mat.values[ 1] = xyC-zs;	mat.values[ 2] = zxC+ys;
	mat.values[ 4] = xyC+zs;	mat.values[ 5] = y*yC+c;	mat.values[ 6] = yzC-xs;
	mat.values[ 8] = zxC-ys;	mat.values[ 9] = yzC+xs;	mat.values[10] = z*zC+c;
	mat.values[15] = 1.0f;
}

void Matrix4x4fRoutines_CPP::ScaleImpl(mat4x4f& mat, kfloat kx, kfloat ky, kfloat kz)
{
	ClearImpl(mat);
	mat.values[0] = kx;
	mat.values[5] = ky;
	mat.values[10] = kz;
	mat.values[15] = 1.0f;
}

void Matrix4x4fRoutines_CPP::TranslationImpl(mat4x4f& mat, kfloat x, kfloat y, kfloat z)
{
	IdentityImpl(mat);
	mat.values[3] = x;
	mat.values[7] = y;
	mat.values[11] = z;
}

void Matrix4x4fRoutines_CPP::TransposeImpl(mat4x4f& mat)
{
	mat4x4f temp = mat;

	mat.values[ 1] = temp.values[ 4];
	mat.values[ 2] = temp.values[ 8];
	mat.values[ 3] = temp.values[12];

	mat.values[ 4] = temp.values[ 1];
	mat.values[ 6] = temp.values[ 9];
	mat.values[ 7] = temp.values[13];

	mat.values[ 8] = temp.values[ 2];
	mat.values[ 9] = temp.values[ 6];
	mat.values[11] = temp.values[14];

	mat.values[12] = temp.values[ 3];
	mat.values[13] = temp.values[ 7];
	mat.values[14] = temp.values[11];
}
