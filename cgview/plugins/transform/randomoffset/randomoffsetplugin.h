/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: randomoffsetplugin.h                                             *
 * Description: Random Offset sample plugin                                   *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_TRANSFORM_RANDOMOFFSET_RANDOMOFFSETPLUGIN_H
#define CGVIEW_PLUGINS_TRANSFORM_RANDOMOFFSET_RANDOMOFFSETPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginTransformInterface

class CGMesh;

class RandomOffsetPlugin : public virtual PluginTransformInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginTransformInterface)

public:
	// PluginTransformInterface
	RandomOffsetPlugin();
	void runTransform(CGMesh *mesh) const;
	void loaded(void);
};

#endif // CGVIEW_PLUGINS_TRANSFORM_RANDOMOFFSET_RANDOMOFFSETPLUGIN_H 
