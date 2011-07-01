/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glwindow.h                                                       *
 * Description: Definition of the OpenGL window for CGView                    *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_OPENGL_GLWINDOW_H
#define CGVIEW_OPENGL_GLWINDOW_H

#include <QtOpenGL> // QGLWidget
#include "opengl/scene/scene.h" // GLCamera, GLLight, GLMesh
#include "pluginmanager.h" // PluginManager

class PluginTransformInterface;
class PluginRenderInterface;

class GLWindow : public QGLWidget
{
	Q_OBJECT

public:
	/** Constructor */
	GLWindow(QWidget *parent = 0);
	/** Destructor */
	inline ~GLWindow() {
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			this->_mesh[i].~GLMesh();
		}
		this->_mesh.clear();
		this->makeCurrent();
	}
	void runTransformPlugin(PluginTransformInterface *plugin);

public slots:
	/// BOX
	/** Disable the bounding box */
	inline void disableBoundingBox(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].disableBoundingBox();
		}
		this->updateGL();
	}
	/** Set the wired bounding box **/
	inline void enableWiredBoundingBox(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableWiredBoundingBox();
		}
		this->updateGL();
	}
	/** Set the transparent bounding box */
	inline void enableTransBoundingBox(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableTransBoundingBox();
		}
		this->updateGL();
	}
	/** Set the solid bounding box */
	inline void enableSolidBoundingBox(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableSolidBoundingBox();
		}
		this->updateGL();
	}

	/// MESH
	/** Disable the mesh */
	inline void disableMesh(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].disableMesh();
		}
		updateGL();
	}
	/** Set the point visualization */
	inline void enablePointMesh(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enablePointMesh();
		}
		updateGL();
	}
	/** Set the flat shading */
	inline void enableFlatMesh(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableFlatMesh();
		}
		updateGL();
	}
	/** Set the smooth shading */
	inline void enableSmoothMesh(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableSmoothMesh();
		}
		this->updateGL();
	}
	/** Set the voxel visualization */
	inline void enableVoxel(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableVoxel();
		}
		this->updateGL();
	}

	/// COLOR
	/** Disable the colors */
	inline void disableColor(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].disableColor();
		}
		this->updateGL();
	}
	/** Enable the vertex color */
	inline void enableVertexColor(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableVertexColor();
		}
		this->updateGL();
	}
	/** Enable the face color */
	inline void enableFaceColor(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableFaceColor();
		}
		this->updateGL();
	}
	/** Enable the texture */
	inline void enableTexture(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableTexture();
		}
		this->updateGL();
	}
	/** Enable the vertex quality color */
	inline void enableQualityVertex(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableQualityVertex();
		}
		this->updateGL();
	}
	/** Enable the face quality color */
	inline void enableQualityFace(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableQualityFace();
		}
		this->updateGL();
	}
	/** Enable the material */
	inline void enableMaterial(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].enableMaterial();
		}
		updateGL();
	}

	/// WIREFRAME
	/** Enable or Disable the wireframe visualization */
	inline void toggleWireframe(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			if (this->_mesh[i].isSelected())
				this->_mesh[i].toggleWireframe();
		}
		this->updateGL();
	}

	/// GENERAL
	/** Reset the GLWindow */
	void reset(void);
	/** Return the bounding box of the scene */
	inline vcg::Box3d Box(void) const { return this->_box; }
	/** Remove the i-th mesh */
	inline void removeMesh(const unsigned int i)
	{
		assert(/*(i >= 0) &&*/ (i < this->_mesh.size()));

		this->_mesh.erase(this->_mesh.begin() + i);

		this->_box.SetNull();
		for (unsigned int j = 0; j < this->_mesh.size(); ++j)
		{
			this->_box.Add(this->_mesh[j].Box());
		}
	}

	/** Add a mesh to the scene */
	void addMesh(CGMesh* m);
	/** Update the GLWindow **/
	inline void updateWindow(void)
	{
		for (unsigned int i = 0; i < this->_mesh.size(); ++i)
		{
			this->_mesh[i].remakeMesh();
		}
		this->updateGL();
	}
	/** Return the camera */
	inline GLCamera *camera(void)
	{
		return &this->_camera;
	}
	void uiInputEvent(InputEvents::EventType type,float value);

private:
	/// OPENGL
	/** Initialize the OpenGL parameters */
	void initializeGL(void);
	/** Draw the entire scene */
	void paintGL(void);
	/** Set the OpenGL parameters after a windows resize action */
	void resizeGL(int width, int height);

	/// SCENE
	/** Draws the background gradient */
	void drawGradient(void);
	/// Mesh inside the scene
	std::vector<GLMesh> _mesh;
	/// Bounding box of the entire scene
	vcg::Box3<double> _box;

	/// Scene camera
	GLCamera _camera;
	/// Scene light (if needed)
	//GLLight _light;

	/// FLAGS
	/// Flag for knowing if a mesh is loaded or not
	bool _loaded;

	/// INTERACTION
	/** Mouse event handler */
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

signals:
	void hasReset(void);
};

#endif // CGVIEW_OPENGL_GLWINDOW_H
