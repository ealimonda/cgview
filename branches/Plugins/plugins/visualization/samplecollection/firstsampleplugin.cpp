/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: firstsampleplugin.cpp                                            *
 * Description: First sample Visualization Plugin inside a collection         *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "firstsampleplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QtOpenGL> // GLU*
#include <mesh_definition.h> // CGMesh

/** Constructor.
 * The constructor shouls always set this->_menuName to the name you want to be
 * shown in the plugin's menu entry, as well as run this->setEnabled(false);
 * so that it won't be automatically enabled at startup
 */
FirstSamplePlugin::FirstSamplePlugin()
{
	this->_menuName = tr("First sample");
	this->setEnabled(false);
}

/** Visualization method
 * Do your fun stuff here.  This will be run before the actual rendering of the
 *   mesh.  You may do an GL processing you want here.
 *
 * \param	CGMesh *mesh	A pointer to the mesh to be processed.
 * TODO: Change to a vector of mesh when CGView will be able to process more than one
 */
void FirstSamplePlugin::doVisualize(CGMesh *mesh) const
{
	glPushMatrix();

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(1.0f);

	glColor4f(0.0f, 0.0f, 1.0f, 0.15f);

	for (int i = 0; i < mesh->fn; ++i)
	{
		glBegin(GL_LINES);
		// Fun stuff here

		glEnd();
	}

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void FirstSamplePlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}

/* Please note that there's no Q_EXPORT_PLUGIN2 here, since this is part of
 * a plugin collection and may not be loaded alone, as it's bundled in the
 * same library as other plugins.
 */
