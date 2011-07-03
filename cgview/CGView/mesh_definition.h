/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: mesh_definition.h                                                *
 * Description: Interface to the VCG library's mesh definition                *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_MESH_DEFINITION_H
#define CGVIEW_MESH_DEFINITION_H

#include <vector> // std::vector

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/vertex/component.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component.h>
#include <vcg/simplex/face/component_ocf.h>

#include <vcg/complex/trimesh/base.h>

//class CGEdge;
class CGFace;
class CGVertex;

class CGTypes : public vcg::UsedTypes<
		vcg::Use<CGVertex>::AsVertexType,
		vcg::Use<CGFace>::AsFaceType/*,
		vcg::Use<CGEdge>::AsEdgeType*/ >{};

class CGVertex: public vcg::Vertex<CGTypes,
		vcg::vertex::Coord3d,
		vcg::vertex::Normal3d,
		vcg::vertex::Color4b,
		vcg::vertex::Qualityf,
		vcg::vertex::VFAdj> {};

class CGFace: public vcg::Face<CGTypes,
		vcg::face::FFAdj,
		vcg::face::Normal3d,
		vcg::face::VertexRef,
		vcg::face::BitFlags,
		vcg::vertex::Color4b,
		vcg::vertex::Qualityf> {};

class CGMesh : public vcg::tri::TriMesh<
		std::vector<CGVertex>, std::vector<CGFace> > {};

typedef CGMesh::CoordType CGPoint;

enum Coords {
	kCoordX = 0,
	kCoordY,
	kCoordZ,
	kCoordW,
	kCoordsMax,
	kCoordsXYZ = kCoordZ+1,
	kCoordsXYZW = kCoordW+1,
};

#endif // CGVIEW_MESH_DEFINITION_H
