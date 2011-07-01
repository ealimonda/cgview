/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: gllight.cpp                                                      *
 * Description: OpenGL Lights                                                 *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "gllight.h"

GLLight::GLLight(void)
{
	this->reset();
}

void GLLight::getLight(void)
{
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//if(on) glEnable(GL_LIGHT0);
	//else glDisable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT,               this->_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,               this->_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR,              this->_specular);
	glLightfv(GL_LIGHT0, GL_POSITION,              this->_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,        this->_direction);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT,         this->_exponent);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF,           this->_cutoff);
	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  this->_att_const);
	glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION,    this->_att_lin);
	glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, this->_att_quad);

	glPopMatrix();
}

void GLLight::reset(void)
{
	this->_ambient[kChannelRed] = 0.0f;
	this->_ambient[kChannelGreen] = 0.0f;
	this->_ambient[kChannelBlue] = 0.0f;
	this->_ambient[kChannelAlpha] = 1.0f;

	this->_diffuse[kChannelRed] = 1.0f;
	this->_diffuse[kChannelGreen] = 1.0f;
	this->_diffuse[kChannelBlue] = 1.0f;
	this->_diffuse[kChannelAlpha] = 1.0f;

	this->_specular[kChannelRed] = 1.0f;
	this->_specular[kChannelGreen] = 1.0f;
	this->_specular[kChannelBlue] = 1.0f;
	this->_specular[kChannelAlpha] = 1.0f;

	this->_position[kCoordX] = 0.0f;
	this->_position[kCoordY] = 0.0f;
	this->_position[kCoordZ] = 1.0f;
	this->_position[kCoordW] = 0.0f;

	this->_direction[kCoordX] = 0.0f;
	this->_direction[kCoordY] = 0.0f;
	this->_direction[kCoordZ] = -1.0f;

	this->_exponent[0] = 0.0f;

	this->_cutoff[0] = 180.0f;

	this->_att_const[0] = 1.0f;

	this->_att_lin[0] = 0.0f;

	this->_att_quad[0] = 0.0f;

	this->_on = false;
}
