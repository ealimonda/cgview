#ifndef GLMESH_H
#define GLMESH_H

#include <QtOpenGL/QtOpenGL>
#include "mesh_definition.h"
#include "opengl/mesh/mode/visualmode.h"
#include "opengl/mesh/material/glmaterial.h"

class GLMesh
{
    //Q_OBJECT

public:
    //Constructor
    inline GLMesh() { Reset(); }
    inline GLMesh(CGMesh* m) { Reset(); setMesh(m); }
    //Deconstructor
    inline ~GLMesh()
    {
        for(unsigned int i = 0; i < m_PROP; i++)
        {
            glDeleteLists(_meshGL[i], 1);
        }
    }

    //Draws the mesh and its properties
    inline void drawMesh()
    {
        glPushMatrix();
        if(_vis.isAxisEnabled())      glCallList(_meshGL[AXIS]);
        if(_vis.isMeshEnabled())      glCallList(_meshGL[MESH]);
        if(_vis.isNormalEnabled())    glCallList(_meshGL[NORMAL]);
        if(_vis.isWireframeEnabled()) glCallList(_meshGL[WIRE]);
        if(_vis.isGridEnabled())      glCallList(_meshGL[GRID]);
        if(_vis.isBoxEnabled())       glCallList(_meshGL[BOX]);
        glPopMatrix();
    }
    //Remake the mesh for visualization purposes
    inline void remakeMesh()
    {
        if(_vis.isAxisEnabled())      remakeProp(AXIS);
        if(_vis.isMeshEnabled())      remakeProp(MESH);
        if(_vis.isNormalEnabled())    remakeProp(NORMAL);
        if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        if(_vis.isGridEnabled())      remakeProp(GRID);
        if(_vis.isBoxEnabled())       remakeProp(BOX);
    }
    //Reset the mesh visual setting
    inline void Reset()
    {
        _vis.Reset();
        _mat.Reset();
        _mat.setMaterial(GLMaterial::CHROME);

        _meshGL[BOX] = 0;
        _meshGL[MESH] = 0;
        _meshGL[NORMAL] = 0;
        _meshGL[WIRE] = 0;
        _meshGL[GRID] = 0;
        _meshGL[AXIS] = 0;

        _grid = CELL;

        _load = false;
        _select = true;
    }

    //Set a mesh
    inline void setMesh(CGMesh* m)
    {
        _m = m;

        _load = true;

        //Make everything needed for the mesh
        if(_vis.isBoxEnabled())       _meshGL[BOX] = makeProp(BOX);
        if(_vis.isMeshEnabled())      _meshGL[MESH] = makeProp(MESH);
        if(_vis.isNormalEnabled())    _meshGL[NORMAL] = makeProp(NORMAL);
        if(_vis.isWireframeEnabled()) _meshGL[WIRE] = makeProp(WIRE);
        if(_vis.isGridEnabled())      _meshGL[GRID] = makeProp(GRID);
        if(_vis.isAxisEnabled())      _meshGL[AXIS] = makeProp(AXIS);
    }
    //Return the bounding box of the mesh
    inline vcg::Box3d Box()
    {
        return _m->bbox;
    }

    //Set the cell per side of the grid
    inline void setGrid(const unsigned int side)
    {
        _grid = side;
        if(_vis.isGridEnabled()) remakeProp(GRID);
    }
    //Return true if the mesh is selected
    inline bool isSelected()
    {
        return _select;
    }

    /// BOX
    //Disable the bounding box
    inline void DisableBoundingBox()
    {
        if(_load)
        {
            _vis.Disable_Box();
            if(_meshGL[BOX] != 0) glDeleteLists(_meshGL[BOX], 1);
            _meshGL[BOX] = 0;
        }
    }
    //Set the wired bounding box
    inline void EnableWiredBoundingBox()
    {
        if(_load)
        {
            _vis.Enable_Box_Wired();
            remakeProp(BOX);
        }
    }
    //Set the transparent bounding box
    inline void EnableTransBoundingBox()
    {
        if(_load)
        {
            _vis.Enable_Box_Trans();
            remakeProp(BOX);
        }
    }
    //Set the solid bounding box
    inline void EnableSolidBoundingBox()
    {
        if(_load)
        {
            _vis.Enable_Box_Solid();
            remakeProp(BOX);
        }
    }

    /// MESH
    //Disable the mesh
    inline void DisableMesh()
    {
        if(_load)
        {
            _vis.Disable_Mesh();
            if(_meshGL[MESH] != 0) glDeleteLists(_meshGL[MESH], 1);
            _meshGL[MESH] = 0;
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Set the point visualization
    inline void EnablePointMesh()
    {
        if(_load)
        {
            _vis.Enable_Mesh_Point();
            remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Set the flat shading
    inline void EnableFlatMesh()
    {
        if(_load)
        {
            if(_m->fn > 0)
            {
                _vis.Enable_Mesh_Flat();
            }
            else
            {
                _vis.Enable_Mesh_Point();
            }
            remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Set the smooth shading
    inline void EnableSmoothMesh()
    {
        if(_load)
        {
            if(_m->fn > 0)
            {
                _vis.Enable_Mesh_Smooth();
            }
            else
            {
                _vis.Enable_Mesh_Point();
            }
            remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Set the voxel visualization
    inline void EnableVoxel()
    {
        if(_load)
        {
            _vis.Enable_Mesh_Voxel();
            remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }

    /// COLOR
    //Disable the colors
    inline void DisableColor()
    {
        if(_load)
        {
            _vis.Disable_Color();
            if(_vis.isMeshEnabled()) remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Enable the vertex color
    inline void EnableVertexColor()
    {
        if(_load)
        {
            _vis.Enable_Color_Vertex();
            if(_vis.isMeshEnabled()) remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Enable the face color
    inline void EnableFaceColor()
    {
        if(_load)
        {
            _vis.Enable_Color_Face();
            if(_vis.isMeshEnabled()) remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Enable the texture
    inline void EnableTexture()
    {
        if(_load)
        {
            _vis.Enable_Color_Texture();
            if(_vis.isMeshEnabled()) remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Enable the vertex quality color
    inline void EnableQualityVertex()
    {
        if(_load)
        {
            _vis.Enable_Color_Quality_Vertex();
            if(_vis.isMeshEnabled()) remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Enable the face quality color
    inline void EnableQualityFace()
    {
        if(_load)
        {
            _vis.Enable_Color_Quality_Face();
            if(_vis.isMeshEnabled()) remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }
    //Enable the material
    inline void EnableMaterial()
    {
        if(_load)
        {
            _vis.Enable_Color_Material();
            _mat.Reset();
            _mat.setMaterial(rand()%20);
            //_mat.setMaterial(GLMaterial::CHROME);
            if(_vis.isMeshEnabled()) remakeProp(MESH);
            if(_vis.isWireframeEnabled()) remakeProp(WIRE);
        }
    }

    /// NORMAL
    //Disable the normal visualization
    inline void DisableNormal()
    {
        if(_load)
        {
            _vis.Disable_Normal();
            if(_meshGL[NORMAL] != 0) glDeleteLists(_meshGL[NORMAL], 1);
            _meshGL[NORMAL] = 0;
        }
    }
    //Enable or Disable the vertex normal
    inline void ToggleNormalVertex()
    {
        if(_load)
        {
            if(_vis.isNormalVertex())
            {
                _vis.Disable_Normal_Vertex();
                if(_vis.isNormalFace())
                {
                    remakeProp(NORMAL);
                }
                else
                {
                    if(_meshGL[NORMAL] != 0) glDeleteLists(_meshGL[NORMAL], 1);
                    _meshGL[NORMAL] = 0;
                }
            }
            else
            {
                _vis.Enable_Normal_Vertex();
                remakeProp(NORMAL);
            }
        }
    }
    //Enable or Disable the face normal
    inline void ToggleNormalFace()
    {
        if(_load)
        {
            if(_vis.isNormalFace())
            {
                _vis.Disable_Normal_Face();
                if(_vis.isNormalVertex())
                {
                    remakeProp(NORMAL);
                }
                else
                {
                    if(_meshGL[NORMAL] != 0) glDeleteLists(_meshGL[NORMAL], 1);
                    _meshGL[NORMAL] = 0;
                }
            }
            else
            {
                _vis.Enable_Normal_Face();
                remakeProp(NORMAL);
            }
        }
    }

    /// WIREFRAME
    //Enable or Disable the wireframe visualization
    inline void ToggleWireframe()
    {
        if(_load)
        {
            if(_vis.isWireframeEnabled())
            {
                _vis.Disable_Wireframe();
                if(_meshGL[WIRE] != 0) glDeleteLists(_meshGL[WIRE], 1);
                _meshGL[WIRE] = 0;
            }
            else
            {
                _vis.Enable_Wireframe();
                remakeProp(WIRE);
            }
        }
    }

    /// GRID
    //Enable or Disable the grid visualization
    inline void ToggleGrid()
    {
        if(_load)
        {
            if(_vis.isGridEnabled())
            {
                _vis.Disable_Grid();
                if(_meshGL[GRID] != 0) glDeleteLists(_meshGL[GRID], 1);
                _meshGL[GRID] = 0;
            }
            else
            {
                _vis.Enable_Grid();
                remakeProp(GRID);
            }
        }
    }

    /// AXIS
    //Enable or Disable the axis visualization
    inline void ToggleAxis()
    {
        if(_load)
        {
            if(_vis.isAxisEnabled())
            {
                _vis.Disable_Axis();
                if(_meshGL[AXIS] != 0) glDeleteLists(_meshGL[AXIS], 1);
                _meshGL[AXIS] = 0;
            }
            else
            {
                _vis.Enable_Axis();
                remakeProp(AXIS);
            }
        }
    }


private:

protected:
    //Identify the property of the mesh
    enum MeshProp
    {
        BOX,
        MESH,
        COLOR,
        NORMAL,
        WIRE,
        GRID,
        AXIS
    };
    //Number of properties
    static const unsigned int m_PROP = 7;

    //Construct the selected property of the mesh
    GLuint makeProp(MeshProp p);
    //Remake the selected property of the mesh
    inline void remakeProp(MeshProp p = MESH)
    {
        glDeleteLists(_meshGL[p], 1);
        _meshGL[p] = 0;
        _meshGL[p] = makeProp(p);
    }

    //OpenGL identifier for the mesh and its properties
    GLuint _meshGL[m_PROP];
    //Real mesh
    CGMesh* _m;
    //Visualization flags
    VisualMode _vis;
    //Mesh Material
    GLMaterial _mat;
    //Voxelized mesh
    //Voxelization* _vox;

    static const unsigned int CELL = 10;
    unsigned int _grid;
    //unsigned int _grid[3];

    bool _load;
    bool _select;

//signals:

//public slots:

//private slots:

};

#endif // GLMESH_H
