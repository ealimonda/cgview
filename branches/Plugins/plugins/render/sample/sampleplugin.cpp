/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: sampleplugin.cpp                                                 *
 * Description: Sample render plugin                                          *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "sampleplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
//#include <QtOpenGL> // QT_*
#include <opengl/glwindow.h> // GLWindow
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

/** Render method
 * Do your fun stuff here.  This will be run after all the mesh processing bits
 *   and should never write into the mesh, or Very Bad Things(tm) will happen.
 *
 * \param	std::vector<GLMesh> &mesh	A reference to the mesh vector
 *		to be rendered.
 * \param	GLWindow *window		A pointer to the GLWindow
 * 		to render into
 */
void SamplePlugin::doRender(std::vector<GLMesh> &mesh, GLWindow *window) const
{
	if (!window)
		return;

	// More rendering code goes over here
#if 0
	for (unsigned int i = 0; i < mesh.size(); ++i)
	{
		// doStuff();
	}
#endif
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

/** Post-initialization actions
 * This is called after the plugin is loaded and all of its slots/signals
 * are connected and set up
 */
void SamplePlugin::loaded(void) {
}

QT_BEGIN_NAMESPACE
/** Edit the next line to match the plugin's name (as a convention, we use
 * the same name as the library's filename), followed by the plugin's class
 */
Q_EXPORT_PLUGIN2(render_sample, SamplePlugin)
QT_END_NAMESPACE
