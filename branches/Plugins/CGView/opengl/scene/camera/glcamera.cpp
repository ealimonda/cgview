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

GLCamera::GLCamera()
{
	reset();
}

GLCamera::GLCamera(float width)
{
	reset();
    fitWidth(width);
}

void GLCamera::camProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, zNear, zFar);
}

void GLCamera::camPosition(EyePosition e)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    switch(e)
    {
	case kEyePositionCenter:
        {
            gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], vup[0], vup[1], vup[2]);
        }
        break;

	case kEyePositionLeft:
        {
            gluLookAt(eye[0] + (-distance / 30.0f) * vr[0],
                      eye[1] + (-distance / 30.0f) * vr[1],
                      eye[2] + (-distance / 30.0f) * vr[2],
                      center[0], center[1], center[2],
                      vup[0], vup[1], vup[2]);
        }
        break;

	case kEyePositionRight:
        {
            gluLookAt(eye[0] + (distance / 30.0f) * vr[0],
                      eye[1] + (distance / 30.0f) * vr[1],
                      eye[2] + (distance / 30.0f) * vr[2],
                      center[0], center[1], center[2],
                      vup[0], vup[1], vup[2]);
        }
        break;
    }
}

void GLCamera::changeDistance(float d)
{
    eye[0] = eye[0] + (d * dir[0]);
    eye[1] = eye[1] + (d * dir[1]);
    eye[2] = eye[2] + (d * dir[2]);
    distance = vcg::Distance(eye, center);
}

void GLCamera::strafeCam(float d)
{
    eye[0] = eye[0] + (d * vr[0]);
    eye[1] = eye[1] + (d * vr[1]);
    eye[2] = eye[2] + (d * vr[2]);
    distance = vcg::Distance(eye, center);
}

void GLCamera::liftCam(float d)
{
    eye[0] = eye[0] + (d * vup[0]);
    eye[1] = eye[1] + (d * vup[1]);
    eye[2] = eye[2] + (d * vup[2]);
    distance = vcg::Distance(eye, center);
}

void GLCamera::rotateVUp(float angle)
{
    vcg::Matrix44d t;
    vcg::Matrix44d r;

    t.SetTranslate(-center);
    r.SetRotateRad(angle, vup);

    eye = t * eye;

    eye = r * eye;
    dir = r * dir;
    vr  = r * vr;

    t.SetTranslate(center);
    eye = t * eye;
}

void GLCamera::rotateVR(float angle)
{
    vcg::Matrix44d t;
    vcg::Matrix44d r;

    t.SetTranslate(-center);
    r.SetRotateRad(angle, vr);

    eye = t * eye;

    eye = r * eye;
    dir = r * dir;
    vup  = r * vup;

    t.SetTranslate(center);
    eye = t * eye;
}

void GLCamera::rotateDir(float angle)
{
    vcg::Matrix44d r;
    r.SetRotateRad(angle, dir);

    eye = r * eye;
    vup = r * vup;
    vr  = r * vr;
}

void GLCamera::reset(void)
{
    center = CGPoint(0.0f, 0.0f, 0.0f);
    eye = CGPoint(0.0f, 0.0f, -1.0f);
    vup = CGPoint(0.0f, 1.0f, 0.0f);
    vr = CGPoint(1.0f, 0.0f, 0.0f);
    dir = CGPoint(0.0f, 0.0f, 1.0f);
    distance = 1.0f;

    fov = 60.0f;
    aspect = 1.0f;
    zNear = 0.5f;
    zFar = 1.5f;
}

void GLCamera::fitWidth(float d)
{
    float BC = d;
    float BH = BC / 2.0f;
    float alpha = vcg::math::ToRad((float)fov/2.0);
    float AB = BH / vcg::math::Sin(alpha / 2.0f);
    float AH = vcg::math::Sqrt( AB - BH );

    eye[0] = center[0] + (AH + BH) * dir[0];
    eye[1] = center[1] + (AH + BH) * dir[1];
    eye[2] = center[2] + (AH + BH) * dir[2];
    distance = AH + BH;
}
