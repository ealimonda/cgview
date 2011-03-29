/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: randomoffsetplugin.cpp                                           *
 * Description: Random offset sample plugin                                   *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "randomoffsetplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <mesh_definition.h> // CGMesh

RandomOffsetPlugin::RandomOffsetPlugin()
{
	this->_menuName = tr("Random Offset");
}

void RandomOffsetPlugin::runTransform(CGMesh *mesh) const
{
	if (!mesh)
		return;
	// For each vertex of the mesh
	for (int i = 0; i < mesh->vn; ++i)
	{
		// Take the pointer
		CGMesh::VertexPointer v = &(mesh->vert[i]);
		v->P()[kCoordX] += (rand()%5-2)*0.01*mesh->bbox.Diag();
		v->P()[kCoordY] += (rand()%5-2)*0.01*mesh->bbox.Diag();
		v->P()[kCoordZ] += (rand()%5-2)*0.01*mesh->bbox.Diag();
	}

}

void RandomOffsetPlugin::loaded(void) {
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(transform_randomoffset, RandomOffsetPlugin)
QT_END_NAMESPACE
