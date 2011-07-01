/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: secondsampleplugin.cpp                                           *
 * Description: Second sample Visualization Plugin inside a collection        *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "secondsampleplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QtOpenGL> // GLU*
#include <mesh_definition.h> // CGMesh

/** Constructor.
 * The constructor shouls always set this->_menuName to the name you want to be
 * shown in the plugin's menu entry, as well as run this->setEnabled(false);
 * so that it won't be automatically enabled at startup
 */
SecondSamplePlugin::SecondSamplePlugin()
{
	this->_menuName = tr("Second Sample");
	this->setEnabled(false);
}

/** Visualization method
 * Do your fun stuff here.  This will be run before the actual rendering of the
 *   mesh.  You may do an GL processing you want here.
 *
 * \param	CGMesh *mesh	A pointer to the mesh to be processed.
 * TODO: Change to a vector of mesh when CGView will be able to process more than one
 */
void SecondSamplePlugin::doVisualize(CGMesh *mesh) const
{
	glPushMatrix();

	glDisable(GL_LIGHTING);
	
	// Fun stuff here
	
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

/** enable() slot
 * This is called whenever the user toggles the plugin's state by choosing
 * the plugin's menu entry.
 * Feel free to add anything here, but make sure you won't remove the
 * existing lines (this->setEnabled(state); emit(toggled()); or a lot of
 * things will break
 *
 * \param	bool state	Boolean flag of the on/off state we toggled to
 */
void SecondSamplePlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}

/** Post-initialization actions
 * This is called after the plugin is loaded and all of its slots/signals
 * are connected and set up
 */
void SecondSamplePlugin::loaded(void) {
}

/* Please note that there's no Q_EXPORT_PLUGIN2 here, since this is part of
 * a plugin collection and may not be loaded alone, as it's bundled in the
 * same library as other plugins.
 */
