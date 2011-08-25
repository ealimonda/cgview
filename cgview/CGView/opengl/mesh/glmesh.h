/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glmesh.h                                                         *
 * Description: OpenGL mesh hadling functions                                 *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_OPENGL_MESH_GLMESH_H
#define CGVIEW_OPENGL_MESH_GLMESH_H

#include "opengl/mesh/mode/visualmode.h" // VisualMode
#include "opengl/mesh/material/glmaterial.h" // GLMaterial
#include "pluginmanager.h" // PluginManager

class CGMesh;
class PluginVisualizationInterface;

class GLMesh
{
	//Q_OBJECT

public:
	/** Constructor */
	inline GLMesh() { this->reset(); }
	explicit inline GLMesh(CGMesh* m) { this->reset(); this->setMesh(m); }
	/** Destructor */
	inline ~GLMesh()
	{
		for (unsigned int i = 0; i < kPropertiesMax; ++i)
		{
			glDeleteLists(this->_meshGL[i], 1);
		}
	}

	/** Draws the mesh and its properties */
	inline void drawMesh(void)
	{
		if ( !_visible ) return;
		glPushMatrix();
		if( this->_vis.isMeshEnabled() )      glCallList(this->_meshGL[kPropertyMesh]);
		if( this->_vis.isWireframeEnabled() ) glCallList(this->_meshGL[kPropertyWireframe]);
		if( this->_vis.isBoxEnabled() )       glCallList(this->_meshGL[kPropertyBox]);
		glCallList(this->_meshGL[kPropertyPlugins]);
		glPopMatrix();
	}
	/** Remake the mesh for visualization purposes */
	inline void remakeMesh(void)
	{
		if( this->_vis.isMeshEnabled() )      this->remakeProp(kPropertyMesh);
		if( this->_vis.isWireframeEnabled() ) this->remakeProp(kPropertyWireframe);
		if( this->_vis.isBoxEnabled() )       this->remakeProp(kPropertyBox);
		this->remakeProp(kPropertyPlugins);
	}
	/** Reset the mesh visual setting */
	inline void reset(void)
	{
		this->_vis.reset();
		this->_mat.reset();
		this->_mat.setMaterial(GLMaterial::kMaterialChrome);

		this->_meshGL[kPropertyBox] = 0;
		this->_meshGL[kPropertyMesh] = 0;
		this->_meshGL[kPropertyWireframe] = 0;
		this->_meshGL[kPropertyPlugins] = 0;

		this->_loaded = false;
		this->_selected = true;
		this->_visible = true;
	}
	/** Set a mesh */
	inline void setMesh(CGMesh* m)
	{
		this->_m = m;

		this->_loaded = true;

		// Make everything needed for the mesh
		if (this->_vis.isBoxEnabled())
			this->_meshGL[kPropertyBox] = this->makeProp(kPropertyBox);
		if (this->_vis.isMeshEnabled())
			this->_meshGL[kPropertyMesh] = this->makeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled())
			this->_meshGL[kPropertyWireframe] = this->makeProp(kPropertyWireframe);
		this->makeProp(kPropertyPlugins);
	}
	/** Return the bounding box of the mesh */
	inline vcg::Box3d Box(void) const
	{
		return this->_m->bbox;
	}
	/** Return true if the mesh is selected */
	inline bool isSelected(void) const
	{
		return this->_selected;
	}

	/// BOX
	/** Disable the bounding box */
	inline void disableBoundingBox(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.disableBox();
		if (this->_meshGL[kPropertyBox] != 0)
			glDeleteLists(this->_meshGL[kPropertyBox], 1);
		this->_meshGL[kPropertyBox] = 0;
	}
	/** Set the wired bounding box */
	inline void enableWiredBoundingBox(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableBoxWired();
		this->remakeProp(kPropertyBox);
	}
	/** Set the transparent bounding box */
	inline void enableTransBoundingBox(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableBoxTrans();
		this->remakeProp(kPropertyBox);
	}
	/** Set the solid bounding box */
	inline void enableSolidBoundingBox(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableBoxSolid();
		this->remakeProp(kPropertyBox);
	}

	/// MESH
	/** Disable the mesh */
	inline void disableMesh(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.disableMesh();
		if (this->_meshGL[kPropertyMesh] != 0)
			glDeleteLists(this->_meshGL[kPropertyMesh], 1);
		this->_meshGL[kPropertyMesh] = 0;
		if (this->_vis.isWireframeEnabled())
			this->remakeProp(kPropertyWireframe);
	}
	/** Set the point visualization */
	inline void enablePointMesh(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableMeshPoint();
		this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled())
			this->remakeProp(kPropertyWireframe);
	}
	/** Set the flat shading */
	inline void enableFlatMesh(void)
	{
		if (!this->_loaded)
			return;
		if (this->_m->fn > 0)
		{
			this->_vis.enableMeshFlat();
		}
		else
		{
			this->_vis.enableMeshPoint();
		}
		this->remakeProp(kPropertyMesh);
		if( this->_vis.isWireframeEnabled() )
			this->remakeProp(kPropertyWireframe);
	}
	/** Set the smooth shading */
	inline void enableSmoothMesh(void)
	{
		if (!this->_loaded)
			return;
		if (this->_m->fn > 0)
		{
			this->_vis.enableMeshSmooth();
		}
		else
		{
			this->_vis.enableMeshPoint();
		}
		this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled())
			this->remakeProp(kPropertyWireframe);
	}
	/** Set the voxel visualization */
	inline void enableVoxel(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableMeshVoxel();
		this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled())
			this->remakeProp(kPropertyWireframe);
	}

	/// COLOR
	/** Disable the colors */
	inline void disableColor(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.disableColor();
		if (this->_vis.isMeshEnabled())      this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled()) this->remakeProp(kPropertyWireframe);
	}
	/** Enable the vertex color */
	inline void enableVertexColor(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableColorVertex();
		if (this->_vis.isMeshEnabled())      this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled()) this->remakeProp(kPropertyWireframe);
	}
	/** Enable the face color */
	inline void enableFaceColor(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableColorFace();
		if (this->_vis.isMeshEnabled())      this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled()) this->remakeProp(kPropertyWireframe);
	}
	/** Enable the texture */
	inline void enableTexture(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableColorTexture();
		if (this->_vis.isMeshEnabled())      this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled()) this->remakeProp(kPropertyWireframe);
	}
	/** Enable the vertex quality color */
	inline void enableQualityVertex(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableColorQualityVertex();
		if (this->_vis.isMeshEnabled())      this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled()) this->remakeProp(kPropertyWireframe);
	}
	/** Enable the face quality color */
	inline void enableQualityFace(void)
	{
		if (!this->_loaded)
			return;
		this->_vis.enableColorQualityFace();
		if (this->_vis.isMeshEnabled())      this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled()) this->remakeProp(kPropertyWireframe);
	}
	/** Enable the material */
	inline void enableMaterial(void) {
		if (!this->_loaded)
			return;
		this->_vis.enableColorMaterial();
		this->_mat.reset();
		this->_mat.setMaterial(rand()%GLMaterial::kMaterialsMax); // FIXME: Remove the rand()?
		//this->_mat.setMaterial(GLMaterial::kMaterialChrome);
		if (this->_vis.isMeshEnabled())      this->remakeProp(kPropertyMesh);
		if (this->_vis.isWireframeEnabled()) this->remakeProp(kPropertyWireframe);
	}

	/// WIREFRAME
	/** Enable or Disable the wireframe visualization */
	inline void toggleWireframe(void)
	{
		if (!this->_loaded)
			return;
		if (this->_vis.isWireframeEnabled())
		{
			this->_vis.disableWireframe();
			if (this->_meshGL[kPropertyWireframe] != 0)
				glDeleteLists(this->_meshGL[kPropertyWireframe], 1);
			this->_meshGL[kPropertyWireframe] = 0;
		}
		else
		{
			this->_vis.enableWireframe();
			this->remakeProp(kPropertyWireframe);
		}
	}

	inline CGMesh *mesh(void) const {
		return this->_m;
	}

	inline void show() {
		_visible = true;
	}

	inline void hide() {
		_visible = false;
	}

private:
	/** Identify the property of the mesh **/
	enum MeshProperty {
		kPropertyBox,
		kPropertyMesh,
		kPropertyColor,
		kPropertyWireframe,
		kPropertyPlugins,
		kPropertiesMax
	};

	/** Construct the selected property of the mesh */
	GLuint makeProp(MeshProperty p);
	/** Remake the selected property of the mesh */
	inline void remakeProp(MeshProperty p)
	{
		glDeleteLists(this->_meshGL[p], 1);
		this->_meshGL[p] = 0;
		this->_meshGL[p] = this->makeProp(p);
	}

	/// OpenGL identifier for the mesh and its properties
	GLuint _meshGL[kPropertiesMax];
	/// Real mesh
	CGMesh* _m;
	/// Visualization flags
	VisualMode _vis;
	/// Mesh Material
	GLMaterial _mat;
	/// Voxelized mesh
	// Voxelization* _vox;

	bool _loaded;
	bool _selected;
	bool _visible;
};

#endif // CGVIEW_OPENGL_MESH_GLMESH_H
