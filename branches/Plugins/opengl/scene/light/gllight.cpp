#include "gllight.h"

GLLight::GLLight()
{
    reset();
}

void GLLight::getLight()
{
    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //if(on) glEnable(GL_LIGHT0);
    //else glDisable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT,                ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,                diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,               specular);
    glLightfv(GL_LIGHT0, GL_POSITION,               position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,         direction);
    glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT,          exponent);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF,            cutoff);
    glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION,   att_const);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION,     att_lin);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,  att_quad);

    glPopMatrix();
}

void GLLight::reset()
{
    ambient[0] = 0.0f;
    ambient[1] = 0.0f;
    ambient[2] = 0.0f;
    ambient[3] = 1.0f;

    diffuse[0] = 1.0f;
    diffuse[1] = 1.0f;
    diffuse[2] = 1.0f;
    diffuse[3] = 1.0f;

    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;
    specular[3] = 1.0f;

    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 1.0f;
    position[3] = 0.0f;

    direction[0] = 0.0f;
    direction[1] = 0.0f;
    direction[2] = -1.0f;

    exponent[0] = 0.0f;

    cutoff[0] = 180.0f;

    att_const[0] = 1.0f;

    att_lin[0] = 0.0f;

    att_quad[0] = 0.0f;

    on = false;
}
