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
#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QtOpenGL/QGLWidget>
#include <QtGui>
#include <QtOpenGL/QtOpenGL>
#include "mesh_definition.h"
#include "mesh_handler.h"
#include "opengl/scene/scene.h"

class GLWindow : public QGLWidget
{
    Q_OBJECT

public:
    //Constructor
    GLWindow(QWidget *parent = 0);
    GLWindow(QWidget *parent = 0, MeshHandler* = NULL );
    //Deconstructor
    inline ~GLWindow()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            _mesh[i].~GLMesh();
        }
        _mesh.clear();

        makeCurrent();
    }

private:

protected:
    /// OPENGL
    //Initialize the OpenGL parameters
    void initializeGL();
    //Draw the entire scene
    void paintGL();
    //Set the OpenGL parameters after a windows resize action
    void resizeGL(int width, int height);

    /// SCENE
    //Mesh inside the scene
    std::vector<GLMesh> _mesh;
    //Bounding box of the entire scene
    vcg::Box3<double> _box;
    //Draws the background gradient
    void drawGradient();

    // puntatore al gestore delle mesh nel box
    MeshHandler *_handler;

    //Scene camera
    GLCamera _camera;
    //Scene light (if needed)
    //GLLight _light;

    /// MOUSE
    //Last position clicked
    QPoint _lastPos;
    //Sensivity of the mouse
    float _mouseSens;

    /// FLAGS
    //Flag for knowing if a mesh is loaded or not
    bool _load;
    //Flag for activating the anaglyph mode
    bool _anaglyph;

    /// INTERACTION
    //Keyboard event handler
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    //Mouse event handler
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    /// INTERACTION FLAGS

    bool _shift_mode;
    bool _rotate_mode;


signals:
    void hasReset();

public slots:
    /// BOX
    //Disable the bounding box
    inline void DisableBoundingBox()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive())
                _mesh[i].DisableBoundingBox();
        }
        updateGL();
    }
    //Set the wired bounding box
    inline void EnableWiredBoundingBox()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableWiredBoundingBox();
        }
        updateGL();
    }
    //Set the transparent bounding box
    inline void EnableTransBoundingBox()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableTransBoundingBox();
        }
        updateGL();
    }
    //Set the solid bounding box
    inline void EnableSolidBoundingBox()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive())
                _mesh[i].EnableSolidBoundingBox();
        }
        updateGL();
    }

    //Set the solid bounding box
    inline void EnableActiveBoundingBox()
    {
        // disable every other active bounding box
        for(unsigned int i = 0; i < _mesh.size(); i++)
            if(_mesh[i].isActive())
                _mesh[i].EnableActiveBoundingBox();
            else
                _mesh[i].DisableActiveBoundingBox();

        updateGL();
    }

    /// MESH
    //Disable the mesh
    inline void DisableMesh()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].DisableMesh();
        }
        updateGL();
    }
    //Set the point visualization
    inline void EnablePointMesh()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnablePointMesh();
        }
        updateGL();
    }
    //Set the flat shading
    inline void EnableFlatMesh()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableFlatMesh();
        }
        updateGL();
    }
    //Set the smooth shading
    inline void EnableSmoothMesh()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableSmoothMesh();
        }
        updateGL();
    }
    //Set the voxel visualization
    inline void EnableVoxel()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableVoxel();
        }
        updateGL();
    }

    /// COLOR
    //Disable the colors
    inline void DisableColor()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].DisableColor();
        }
        updateGL();
    }
    //Enable the vertex color
    inline void EnableVertexColor()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableVertexColor();
        }
        updateGL();
    }
    //Enable the face color
    inline void EnableFaceColor()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableFaceColor();
        }
        updateGL();
    }
    //Enable the texture
    inline void EnableTexture()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableTexture();
        }
        updateGL();
    }
    //Enable the vertex quality color
    inline void EnableQualityVertex()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableQualityVertex();
        }
        updateGL();
    }
    //Enable the face quality color
    inline void EnableQualityFace()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableQualityFace();
        }
        updateGL();
    }
    //Enable the material
    inline void EnableMaterial()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].EnableMaterial();
        }
        updateGL();
    }

    /// NORMAL
    //Disable the normal visualization
    inline void DisableNormal()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].DisableNormal();
        }
        updateGL();
    }
    //Enable or Disable the vertex normal
    inline void ToggleNormalVertex()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].ToggleNormalVertex();
        }
        updateGL();
    }
    //Enable or Disable the face normal
    inline void ToggleNormalFace()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].ToggleNormalFace();
        }
        updateGL();
    }

    /// WIREFRAME
    //Enable or Disable the wireframe visualization
    inline void ToggleWireframe()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].ToggleWireframe();
        }
        updateGL();
    }

    /// GRID
    //Enable or Disable the grid visualization
    inline void ToggleGrid()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].ToggleGrid();
        }
        updateGL();
    }

    /// AXIS
    //Enable or Disable the axis visualization
    inline void ToggleAxis()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].ToggleAxis();
        }
        updateGL();
    }

    /// OTHERS
    //Set the number of cell per side of the grid
    inline void setGrid(const unsigned int side)
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            if(_mesh[i].isActive()) _mesh[i].setGrid(side);
        }
    }

    /// GENERAL
    //Reset the GLWindow
    void Reset();
    //Return the bounding box of the scene
    inline vcg::Box3d Box()
    {
        return _box;
    }
    //Remove the i-th mesh
    inline void removeMesh(const unsigned int i)
    {
        assert((i >= 0) && (i < _mesh.size()));

        _mesh.erase(_mesh.begin() + i);

        _box.SetNull();
        for(unsigned int j = 0; j < _mesh.size(); j++)
        {
            _box.Add(_mesh[j].Box());
        }
    }

    //Add a mesh to the scene
    void addMesh(CGMesh* m);
    //Update the GLWindow
    inline void UpdateWindow()
    {
        for(unsigned int i = 0; i < _mesh.size(); i++)
        {
            _mesh[i].remakeMesh();
        }
        EnableActiveBoundingBox();
        updateGL();
    }

    /// RENDERING
    //Enable or disable the anaglyph
    inline void useAnaglyph()
    {
        if(_load) _anaglyph = !_anaglyph;
        updateGL();
    }

    inline void update_camera(int i)
    {
        CGMesh *m;
        m = _mesh[i].get_mesh();
        _camera.setCenterXYZ(m->get_x(),m->get_y(),m->get_z());
        updateGL();
    }

private slots:

protected slots:

};

#endif //GLWINDOW_H
