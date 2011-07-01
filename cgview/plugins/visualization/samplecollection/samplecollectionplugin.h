/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: samplecollectionplugin.h                                         *
 * Description: Collection of (sample) Visualization Plugins                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_VISUALIZATION_SAMPLECOLLECTION_SAMPLECOLLECTIONPLUGIN_H
#define CGVIEW_PLUGINS_VISUALIZATION_SAMPLECOLLECTION_SAMPLECOLLECTIONPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginVisualizationInterface

//class GLMesh;
//class GLWindow;

/** The main plugin's class.
 * This must always implement the CGViewPluginCollectionInterface, else it won't
 * be loaded properly as a plugin collection.
 * The class shouldn't have any methods except for constructors/destructors.
 */
class SampleCollectionPlugin : public virtual CGViewPluginCollectionInterface
{
	Q_OBJECT
	Q_INTERFACES(CGViewPluginCollectionInterface)

public:
	// CGViewPluginCollectionInterface
	SampleCollectionPlugin();
};

#endif // CGVIEW_PLUGINS_VISUALIZATION_SAMPLECOLLECTION_SAMPLECOLLECTIONPLUGIN_H
