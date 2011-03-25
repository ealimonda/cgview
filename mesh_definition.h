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

#include <QString>
#include <GL/gl.h>

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

class CGMesh : public vcg::tri::TriMesh<std::vector<CGVertex>, std::vector<CGFace> >
{
public:
    inline CGMesh() : vcg::tri::TriMesh<std::vector<CGVertex>, std::vector<CGFace> >()
    {
        _select = false;
        _draw   = true;
        _active = false;

        // set a default name
        _name = "new_mesh";

        // set the centre as the origin
        _x = 0.0f;
        _y = 0.0f;
        _z = 0.0f;
    }

    inline void set_name(QString name)
    {
        _name = name;
    }

    inline const QString get_name()
    {
        return _name;
    }

    inline bool is_select(){return _select;}
    inline bool is_active(){return _active;}
    inline bool is_drawn(){return _draw;}

    inline GLfloat get_x() {return _x;}
    inline GLfloat get_y() {return _y;}
    inline GLfloat get_z() {return _z;}

    inline void set_x(GLfloat x) { _x = x;}
    inline void set_y(GLfloat y) { _y = y;}
    inline void set_z(GLfloat z) { _z = z;}

    inline void add_x(GLfloat x) { _x = _x + x;}
    inline void add_y(GLfloat y) { _y = _y + y;}
    inline void add_z(GLfloat z) { _z = _z + z;}

    inline void set_drawn(bool state) { _draw = state;}
    inline void set_select(bool state){ _select = state;}
    inline void set_active(bool state){ _active = state;}

private:

    // True if the mesh is selected
    bool _select;
    // True if the mesh has to be rendered
    bool _draw;
    // True if the mesh is active
    bool _active;

    // mesh name for GUI reference
    QString _name;

    // center coordinates
    GLfloat _x;
    GLfloat _y;
    GLfloat _z;


};

typedef CGMesh::CoordType CGPoint;


#endif // MESH_DEFINITION_H
