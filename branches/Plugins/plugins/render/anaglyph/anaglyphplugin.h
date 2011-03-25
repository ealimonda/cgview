/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: anaglyphplugin.h                                                 *
 * Description: Anaglyph render mode plugin                                   *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_RENDER_ANAGLYPH_ANAGLYPHPLUGIN_H
#define CGVIEW_PLUGINS_RENDER_ANAGLYPH_ANAGLYPHPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginTransformInterface

class GLMesh;
class GLWindow;

class AnaglyphPlugin : public virtual PluginRenderInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginRenderInterface)

public:
	// PluginTransformInterface
	AnaglyphPlugin();
	void doRender(std::vector<GLMesh> &mesh, GLWindow *window) const;

public slots:
	void enable(bool state);

signals:
	void toggled(void);
};

#endif // CGVIEW_PLUGINS_RENDER_ANAGLYPH_ANAGLYPHPLUGIN_H
