/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: sampleplugin.cpp                                                 *
 * Description: Sample transformation plugin                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "sampleplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <mesh_definition.h> // CGMesh

/** Constructor.
 * The constructor shouls always set this->_menuName to the name you want to be
 * shown in the plugin's menu entry.
 */
SamplePlugin::SamplePlugin()
{
	this->_menuName = tr("Sample");
}

/** Transformation method
 * Do your fun stuff here.  This will be run as soon as the menu entry is
 *   triggered, and may edit the mesh.
 *
 * \param	CGMesh *mesh	A pointer to the mesh to be processed.
 * TODO: Change to a vector of mesh when CGView will be able to process more than one
 */
void SamplePlugin::runTransform(CGMesh *mesh) const
{
	if (!mesh)
		return;
	// For each vertex of the mesh
	for (int i = 0; i < mesh->vn; ++i)
	{
		// Do fun stuff
	}

}

QT_BEGIN_NAMESPACE
/** Edit the next line to match the plugin's name (as a convention, we use
 * the same name as the library's filename), followed by the plugin's class
 */
Q_EXPORT_PLUGIN2(transform_sample, SamplePlugin)
QT_END_NAMESPACE
