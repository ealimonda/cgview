/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: normalsfaceplugin.h                                              *
 * Description: Face Normals Visualization Plugin                             *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_VISUALIZATION_NORMALS_NORMALSFACEPLUGIN_H
#define CGVIEW_PLUGINS_VISUALIZATION_NORMALS_NORMALSFACEPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginVisualizationInterface

//class GLMesh;
//class GLWindow;

class NormalsFacePlugin : public virtual PluginVisualizationInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginVisualizationInterface)

public:
	// PluginVisualizationInterface
	NormalsFacePlugin();
	void doVisualize(CGMesh *mesh) const;
	void loaded(void);

public slots:
	void enable(bool state);

signals:
	void toggled(void);
};

#endif // CGVIEW_PLUGINS_VISUALIZATION_NORMALS_NORMALSFACEPLUGIN_H
