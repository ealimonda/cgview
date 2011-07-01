/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glcamera.cpp                                                     *
 * Description: OpenGL Camera                                                 *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "glcamera.h"
#include <QtOpenGL>

GLCamera::GLCamera(void)
{
	this->reset();
}

GLCamera::GLCamera(float width)
{
	this->reset();
	this->fitWidth(width);
}

void GLCamera::camProjection(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->_fov, this->_aspect, this->_zNear, this->_zFar);
}

void GLCamera::camPosition(EyePosition e)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch (e)
	{
	case kEyePositionCenter:
	  {
		gluLookAt(this->_eye[kCoordX], this->_eye[kCoordY], this->_eye[kCoordZ],
				this->_center[kCoordX], this->_center[kCoordY], this->_center[kCoordZ],
				this->_vup[kCoordX], this->_vup[kCoordY], this->_vup[kCoordZ]);
          }
		break;

	case kEyePositionLeft:
	  {
		gluLookAt(this->_eye[kCoordX] + (-this->_distance / 30.0f) * this->_vr[kCoordX],
				this->_eye[kCoordY] + (-this->_distance / 30.0f) * this->_vr[kCoordY],
				this->_eye[kCoordZ] + (-this->_distance / 30.0f) * this->_vr[kCoordZ],
				this->_center[kCoordX], this->_center[kCoordY], this->_center[kCoordZ],
				this->_vup[kCoordX], this->_vup[kCoordY], this->_vup[kCoordZ]);
	  }
		break;

	case kEyePositionRight:
	  {
		gluLookAt(this->_eye[kCoordX] + (this->_distance / 30.0f) * this->_vr[kCoordX],
				this->_eye[kCoordY] + (this->_distance / 30.0f) * this->_vr[kCoordY],
				this->_eye[kCoordZ] + (this->_distance / 30.0f) * this->_vr[kCoordZ],
				this->_center[kCoordX], this->_center[kCoordY], this->_center[kCoordZ],
				this->_vup[kCoordX], this->_vup[kCoordY], this->_vup[kCoordZ]);
	  }
		break;
	}
}

void GLCamera::changeDistance(float d)
{
	this->_eye[kCoordX] = this->_eye[kCoordX] + (d * this->_dir[kCoordX]);
	this->_eye[kCoordY] = this->_eye[kCoordY] + (d * this->_dir[kCoordY]);
	this->_eye[kCoordZ] = this->_eye[kCoordZ] + (d * this->_dir[kCoordZ]);
	this->_distance = vcg::Distance(this->_eye, this->_center);
}

void GLCamera::strafeCam(float d)
{
	this->_eye[kCoordX] = this->_eye[kCoordX] + (d * this->_vr[kCoordX]);
	this->_eye[kCoordY] = this->_eye[kCoordY] + (d * this->_vr[kCoordY]);
	this->_eye[kCoordZ] = this->_eye[kCoordZ] + (d * this->_vr[kCoordZ]);
	this->_distance = vcg::Distance(this->_eye, this->_center);
}

void GLCamera::liftCam(float d)
{
	this->_eye[kCoordX] = this->_eye[kCoordX] + (d * this->_vup[kCoordX]);
	this->_eye[kCoordY] = this->_eye[kCoordY] + (d * this->_vup[kCoordY]);
	this->_eye[kCoordZ] = this->_eye[kCoordZ] + (d * this->_vup[kCoordZ]);
	this->_distance = vcg::Distance(this->_eye, this->_center);
}

void GLCamera::rotateVUp(float angle)
{
	vcg::Matrix44d t;
	vcg::Matrix44d r;

	t.SetTranslate(-this->_center);
	r.SetRotateRad(angle, this->_vup);

	this->_eye = t * this->_eye;

	this->_eye = r * this->_eye;
	this->_dir = r * this->_dir;
	this->_vr  = r * this->_vr;

	t.SetTranslate(this->_center);
	this->_eye = t * this->_eye;
}

void GLCamera::rotateVR(float angle)
{
	vcg::Matrix44d t;
	vcg::Matrix44d r;

	t.SetTranslate(-this->_center);
	r.SetRotateRad(angle, this->_vr);

	this->_eye = t * this->_eye;

	this->_eye = r * this->_eye;
	this->_dir = r * this->_dir;
	this->_vup  = r * this->_vup;

	t.SetTranslate(this->_center);
	this->_eye = t * this->_eye;
}

void GLCamera::rotateDir(float angle)
{
	vcg::Matrix44d r;
	r.SetRotateRad(angle, this->_dir);

	this->_eye = r * this->_eye;
	this->_vup = r * this->_vup;
	this->_vr  = r * this->_vr;
}

void GLCamera::reset(void)
{
	this->_center = CGPoint(0.0f, 0.0f, 0.0f);
	this->_eye = CGPoint(0.0f, 0.0f, -1.0f);
	this->_vup = CGPoint(0.0f, 1.0f, 0.0f);
	this->_vr = CGPoint(1.0f, 0.0f, 0.0f);
	this->_dir = CGPoint(0.0f, 0.0f, 1.0f);
	this->_distance = 1.0f;

	this->_fov = 60.0f;
	this->_aspect = 1.0f;
	this->_zNear = 0.5f;
	this->_zFar = 1.5f;
}

void GLCamera::fitWidth(float d)
{
	float BC = d;
	float BH = BC / 2.0f;
	float alpha = vcg::math::ToRad((float)this->_fov/2.0);
	float AB = BH / vcg::math::Sin(alpha / 2.0f);
	float AH = vcg::math::Sqrt( AB - BH );

	this->_eye[kCoordX] = this->_center[kCoordX] + (AH + BH) * this->_dir[kCoordX];
	this->_eye[kCoordY] = this->_center[kCoordY] + (AH + BH) * this->_dir[kCoordY];
	this->_eye[kCoordZ] = this->_center[kCoordZ] + (AH + BH) * this->_dir[kCoordZ];
	this->_distance = AH + BH;
}
