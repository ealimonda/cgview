/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: sampleplugin.h                                                   *
 * Description: Sample render mode plugin                                     *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_RENDER_SAMPLE_SAMPLEPLUGIN_H
#define CGVIEW_PLUGINS_RENDER_SAMPLE_SAMPLEPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginTransformInterface

class GLMesh;
class GLWindow;

/** The main plugin's class.
 * This must always implement the PluginRenderInterface, else it won't be
 * loaded properly as a rendering plugin.
 * All the following methods are required, but you're free to add your
 * own methods if you wish.
 */
class SamplePlugin : public virtual PluginRenderInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginRenderInterface)

public:
	// PluginTransformInterface
	SamplePlugin();
	void doRender(std::vector<GLMesh> &mesh, GLWindow *window) const;
	void loaded(void);

public slots:
	void enable(bool state);

signals:
	void toggled(void);
};

#endif // CGVIEW_PLUGINS_RENDER_SAMPLE_SAMPLEPLUGIN_H
