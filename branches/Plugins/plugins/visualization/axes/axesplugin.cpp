/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: axesplugin.cpp                                                   *
 * Description: Axes Visualization Plugin                                     *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "axesplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QtOpenGL> // GLU*
#include <mesh_definition.h> // CGMesh

AxesPlugin::AxesPlugin()
{
	this->_menuName = tr("Axes");
	this->setEnabled(false);
}

void AxesPlugin::doVisualize(CGMesh *mesh) const
{
	double tot_lenght = mesh->bbox.Diag() * 0.1f;
	double body_lenght = tot_lenght * 0.7f;
	double head_lenght = tot_lenght * 0.3f;
	double body_radius = body_lenght * 0.1f;
	double head_radius = 2 * body_radius;

	GLUquadric* body = gluNewQuadric();
	GLUquadric* head = gluNewQuadric();
	gluQuadricDrawStyle(body, GLU_FILL);
	gluQuadricDrawStyle(head, GLU_FILL);

	glPushMatrix();
	glDisable(GL_LIGHTING);

	glTranslatef(mesh->bbox.min[kCoordX], mesh->bbox.min[kCoordY], mesh->bbox.min[kCoordZ]);

	/// SPHERE
	glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
	glPushMatrix();
	gluSphere(body, head_radius, 20, 20);
	glPopMatrix();

	/// Z
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	// BODY
	glPushMatrix();
	gluCylinder(body, body_radius, body_radius, body_lenght, 20, 10);
	glPopMatrix();
	// HEAD
	glPushMatrix();
	glTranslatef(0, 0, body_lenght);
	gluCylinder(head, head_radius, 0, head_lenght, 20, 10);
	glPopMatrix();

	/// Y
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	// BODY
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(body, body_radius, body_radius, body_lenght, 20, 10);
	glPopMatrix();
	// HEAD
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0, 0, body_lenght);
	gluCylinder(head, head_radius, 0, head_lenght, 20, 10);
	glPopMatrix();

	/// X
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	// BODY
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(body, body_radius, body_radius, body_lenght, 20, 10);
	glPopMatrix();
	// HEAD
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, body_lenght);
	gluCylinder(head, head_radius, 0, head_lenght, 20, 10);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void AxesPlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(visualization_axes, AxesPlugin)
QT_END_NAMESPACE
