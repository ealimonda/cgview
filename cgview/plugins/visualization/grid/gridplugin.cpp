/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: gridplugin.cpp                                                   *
 * Description: Grid Visualization Plugin                                     *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "gridplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QtOpenGL> // GLU*
#include <mesh_definition.h> // CGMesh

GridPlugin::GridPlugin()
{
	this->_menuName = tr("Grid");
	this->_grid = this->kDefaultGrid;
	this->setEnabled(false);
}

void GridPlugin::doVisualize(CGMesh *mesh) const
{
	CGPoint min = mesh->bbox.min;
	CGPoint max = mesh->bbox.max;
	double dx = mesh->bbox.DimX() / this->_grid;
	double dy = mesh->bbox.DimY() / this->_grid;
	double dz = mesh->bbox.DimZ() / this->_grid;
	unsigned int div = this->_grid;

	glPushMatrix();

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glLineWidth(1.0f);

	for (unsigned int i = 0; i < (div + 1); ++i)
	{
		for (unsigned int j = 0; j < (div + 1); ++j)
		{
			// Davanti
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX] + (i * dx),
					(GLfloat)min[kCoordY] + (j * dy),
					(GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX] + (i * dx),
					(GLfloat)min[kCoordY] + (j * dy),
					(GLfloat)max[kCoordZ]);
			glEnd();

			// Lato
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX],
					(GLfloat)min[kCoordY] + (j * dy),
					(GLfloat)min[kCoordZ] + (i * dz));
			glVertex3f((GLfloat)max[kCoordX],
					(GLfloat)min[kCoordY] + (j * dy),
					(GLfloat)min[kCoordZ] + (i * dz));
			glEnd();

			// Sotto
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX] + (j * dx),
					(GLfloat)min[kCoordY],
					(GLfloat)min[kCoordZ] + (i * dz));
			glVertex3f((GLfloat)min[kCoordX] + (j * dx),
					(GLfloat)max[kCoordY],
					(GLfloat)min[kCoordZ] + (i * dz));
			glEnd();
		}
	}
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void GridPlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}

void GridPlugin::loaded(void) {
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(visualization_grid, GridPlugin)
QT_END_NAMESPACE
