/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: samplecollectionplugin.cpp                                       *
 * Description: Collection of (sample) visualization plugins                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "samplecollectionplugin.h"
#include "firstsampleplugin.h"
#include "secondsampleplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QtOpenGL> // GLU*
#include <mesh_definition.h> // CGMesh

SampleCollectionPlugin::SampleCollectionPlugin()
{
	this->_plugins.append(new FirstSamplePlugin);
	this->_plugins.append(new SecondSamplePlugin);
	// Add as many as you wish
}

QT_BEGIN_NAMESPACE
/** Edit the next line to match the plugin's name (as a convention, we use
 * the same name as the library's filename), followed by the plugin collection's
 * class.
 * NOTE: This line must appear ONCE per COLLECTION, or it won't link.
 */
Q_EXPORT_PLUGIN2(visualization_samplecollection, SampleCollectionPlugin)
QT_END_NAMESPACE
