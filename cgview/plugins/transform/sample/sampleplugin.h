/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: sampleplugin.h                                                   *
 * Description: Sample transformation plugin                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_TRANSFORM_SAMPLE_SAMPLEPLUGIN_H
#define CGVIEW_PLUGINS_TRANSFORM_SAMPLE_SAMPLEPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginTransformInterface

class CGMesh;

/** The main plugin's class.
 * This must always implement the PluginTransformrInterface, else it won't be
 * loaded properly as a transformation plugin.
 * All the following methods are required, but you're free to add your
 * own methods if you wish.
 */
class SamplePlugin : public virtual PluginTransformInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginTransformInterface)

public:
	// PluginTransformInterface
	SamplePlugin();
	void runTransform(CGMesh *mesh) const;
	void loaded(void);
};

#endif // CGVIEW_PLUGINS_TRANSFORM_SAMPLE_SAMPLEPLUGIN_H 
