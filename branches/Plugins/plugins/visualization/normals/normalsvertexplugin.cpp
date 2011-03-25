/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: normalsvertexplugin.cpp                                          *
 * Description: Vertex Normals Visualization Plugin                           *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "normalsvertexplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QtOpenGL> // GLU*
#include <mesh_definition.h> // CGMesh

NormalsVertexPlugin::NormalsVertexPlugin()
{
	this->_menuName = tr("Vertex Normals");
	this->setEnabled(false);
}

void NormalsVertexPlugin::doVisualize(CGMesh *mesh) const
{
	glPushMatrix();

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(1.0f);

	glColor4f(1.0f, 0.0f, 0.0f, 0.15f);

	for( int i = 0; i < mesh->vn; ++i )
	{
		CGPoint p = mesh->vert[i].P();
		CGPoint n = mesh->vert[i].N() * (mesh->bbox.Diag() * 0.1f);

		glBegin(GL_LINES);
		glVertex3f((GLfloat)p[kCoordX], (GLfloat)p[kCoordY], (GLfloat)p[kCoordZ]);
		glVertex3f((GLfloat)(p[kCoordX] + n[kCoordX]),
				(GLfloat)(p[kCoordY] + n[kCoordY]),
				(GLfloat)(p[kCoordZ] + n[kCoordZ]));
		glEnd();
	}

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void NormalsVertexPlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}
