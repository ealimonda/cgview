/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: secondsampleplugin.h                                             *
 * Description: Sample visualization plugin part of a collection              *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_VISUALIZATION_SAMPLECOLLECTION_SECONDSAMPLEPLUGIN_H
#define CGVIEW_PLUGINS_VISUALIZATION_SAMPLECOLLECTION_SECONDSAMPLEPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginVisualizationInterface

//class GLMesh;
//class GLWindow;

/** The main plugin's class.
 * This must always implement the PluginVisualizationInterface, else it won't
 * be loaded properly as a visualization plugin.
 * All the following methods are required, but you're free to add your
 * own methods if you wish.
 */
class SecondSamplePlugin : public virtual PluginVisualizationInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginVisualizationInterface)

public:
	// PluginVisualizationInterface
	SecondSamplePlugin();
	void doVisualize(CGMesh *mesh) const;

public slots:
	void enable(bool state);

signals:
	void toggled(void);
};

#endif // CGVIEW_PLUGINS_VISUALIZATION_SAMPLECOLLECTION_SECONDSAMPLEPLUGIN_H
