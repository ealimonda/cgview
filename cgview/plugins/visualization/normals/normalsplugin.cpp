/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: normalsplugin.cpp                                                *
 * Description: Normals Visualization Plugin                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "normalsplugin.h"
#include "normalsfaceplugin.h"
#include "normalsvertexplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QtOpenGL> // GLU*
#include <mesh_definition.h> // CGMesh

NormalsPlugin::NormalsPlugin()
{
	this->_plugins.append(new NormalsFacePlugin);
	this->_plugins.append(new NormalsVertexPlugin);
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(visualization_normals, NormalsPlugin)
QT_END_NAMESPACE
