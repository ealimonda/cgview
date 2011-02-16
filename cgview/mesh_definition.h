/**********************************************************************
*                                                                     *
*    CCCCCCCCCC  GGGGGGGGGG  VV        VV                             *
*    CC          GG           VV      VV   II   EEEEE    W       W    *
*    CC          GG            VV    VV        E     E   W       W    *
*    CC          GG    GGGG     VV  VV     II  EEEEEE    W   W   W    *
*    CC          GG      GG      VVVV      II  E         W   W   W    *
*    CCCCCCCCCC  GGGGGGGGGG       VV       II   EEEEEE    WWW WWW     *
*                                                                     *
**********************************************************************/


/*
  L'header mesh_definition viene utilizzato per creare un'interfaccia
  con la definizione di mesh della libreira VCG
*/


#ifndef MESH_DEFINITION_H
#define MESH_DEFINITION_H

#include <vector>

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/vertex/component.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component.h>
#include <vcg/simplex/face/component_ocf.h>

#include <vcg/complex/trimesh/base.h>

//class CGEdge;
class CGFace;
class CGVertex;

class CGTypes : public vcg::UsedTypes< vcg::Use<CGVertex>::AsVertexType, vcg::Use<CGFace>::AsFaceType/*,
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


#endif // MESH_DEFINITION_H
