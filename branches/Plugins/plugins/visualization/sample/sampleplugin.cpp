/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: sampleplugin.cpp                                                 *
 * Description: Sample Visualization Plugin                                   *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "sampleplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QtOpenGL> // GLU*
#include <mesh_definition.h> // CGMesh

/** Constructor.
 * The constructor shouls always set this->_menuName to the name you want to be
 * shown in the plugin's menu entry, as well as run this->setEnabled(false);
 * so that it won't be automatically enabled at startup
 */
SamplePlugin::SamplePlugin()
{
	this->_menuName = tr("Sample");
	this->setEnabled(false);
}

/** Visualization method
 * Do your fun stuff here.  This will be run before the actual rendering of the
 *   mesh.  You may do an GL processing you want here.
 *
 * \param	CGMesh *mesh	A pointer to the mesh to be processed.
 * TODO: Change to a vector of mesh when CGView will be able to process more than one
 */
void SamplePlugin::doVisualize(CGMesh *mesh) const
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
void SamplePlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}

QT_BEGIN_NAMESPACE
/** Edit the next line to match the plugin's name (as a convention, we use
 * the same name as the library's filename), followed by the plugin's class
 */
Q_EXPORT_PLUGIN2(visualization_sample, SamplePlugin)
QT_END_NAMESPACE
