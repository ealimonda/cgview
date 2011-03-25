/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: gridplugin.h                                                     *
 * Description: Grid Visualization Plugin                                     *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_VISUALIZATION_GRID_GRIDPLUGIN_H
#define CGVIEW_PLUGINS_VISUALIZATION_GRID_GRIDPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginVisualizationInterface

//class GLMesh;
//class GLWindow;

class GridPlugin : public virtual PluginVisualizationInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginVisualizationInterface)

public:
	// PluginVisualizationInterface
	GridPlugin();
	void doVisualize(CGMesh *mesh) const;

public slots:
	void enable(bool state);

signals:
	void toggled(void);

private:
	static const unsigned int kDefaultGrid = 10;
	unsigned int _grid;
};

#endif // CGVIEW_PLUGINS_VISUALIZATION_GRID_GRIDPLUGIN_H
