/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: normalsplugin.h                                                  *
 * Description: Normals Visualization Plugin                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_VISUALIZATION_NORMALS_NORMALSPLUGIN_H
#define CGVIEW_PLUGINS_VISUALIZATION_NORMALS_NORMALSPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginVisualizationInterface

//class GLMesh;
//class GLWindow;

class NormalsPlugin : public virtual CGViewPluginCollectionInterface
{
	Q_OBJECT
	Q_INTERFACES(CGViewPluginCollectionInterface)

public:
	// CGViewPluginCollectionInterface
	NormalsPlugin();
};

#endif // CGVIEW_PLUGINS_VISUALIZATION_NORMALS_NORMALSPLUGIN_H
