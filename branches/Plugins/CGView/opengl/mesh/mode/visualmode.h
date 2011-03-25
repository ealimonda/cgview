/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: visualmode.h                                                     *
 * Description: Visualization modes                                           *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_OPENGL_MESH_MODE_VISUALMODE_H
#define CGVIEW_OPENGL_MESH_MODE_VISUALMODE_H

/**
 * Visualization Modes:
 * - BOX       : disable the bounding box visualization, or enable one of its three forms (wired, transparent and solid)
 * - MESH      : disable the mesh visualization, or enable one of its forms (points, flat shaded, smooth shaded, voxel)
 * - COLOR     : disable the colors, or enable one of its forms (vertex, face, texture, vertex quality, face quality, material)
 * - WIREFRAME : disable or enable the wireframe visualization (used also to make the flat lines visualization)
 *
 * The representation is the following (4 byte):
 *	xxBB xMMM xCCC xxxx xWxx xxxx xxxx xxxx
 * where 'B' is a bit for the bounding box, 'M' a bit for the mesh, 'C' for color, 'W' for wireframe,
 * The 'x' stands for an unused bit, so there is enough space for futher expantions.
 */

class VisualMode
{
public:
	/** Constructor */
	inline VisualMode() { this->reset(); }
	/** Destructor */
	inline ~VisualMode() {}

	/** Reset the visualization mode */
	inline void reset(void)
	{
		// Reset the status
		this->_status = kVisReset;
		// Setting the mesh to flat shading
		this->_status |= kVisMeshFlat;
	}

	/// BOUNDING BOX
	/** Disable the bounding box */
	inline void disableBox(void)
	{
		this->_status &= kVisBoxDisable;
	}
	/** Enable the wired bounding box */
	inline void enableBoxWired(void)
	{
		this->_status = (this->_status & kVisBoxDisable) | kVisBoxWired;
	}
	/** Enable the transparent bounding box */
	inline void enableBoxTrans(void)
	{
		this->_status = (this->_status & kVisBoxDisable) | kVisBoxTrans;
	}
	/** Enable the solid bounding box */
	inline void enableBoxSolid(void)
	{
		this->_status = (this->_status & kVisBoxDisable) | kVisBoxSolid;
	}
	/** Return true if the box is enabled */
	inline bool isBoxEnabled(void) const
	{
		return (this->_status & (kVisNull ^ kVisBoxDisable));
	}
	/** Return true if the wired box is enabled */
	inline bool isBoxWired(void) const
	{
		return ((this->_status & kVisBoxWired) && !(this->_status & kVisBoxTrans));
	}
	/** Return true if the transparent box is enabled */
	inline bool isBoxTrans(void) const
	{
		return (!(this->_status & kVisBoxWired) && (this->_status & kVisBoxTrans));
	}
	/** Return true if the solid box is enabled */
	inline bool isBoxSolid(void) const
	{
		return ((this->_status & kVisBoxWired) && (this->_status & kVisBoxTrans));
	}

	/// MESH
	/** Disable the mesh visualization */
	inline void disableMesh(void)
	{
		this->_status &= kVisMeshDisable;
	}
	/** Enable the visualization of the point of the mesh */
	inline void enableMeshPoint(void)
	{
		this->_status = (this->_status & kVisMeshDisable) | kVisMeshPoint;
	}
	/** Enable the flat shading visualization of the mesh */
	inline void enableMeshFlat(void)
	{
		this->_status = (this->_status & kVisMeshDisable) | kVisMeshFlat;
	}
	/** Enable the smooth shading visualization of the mesh */
	inline void enableMeshSmooth(void)
	{
		this->_status = (this->_status & kVisMeshDisable) | kVisMeshSmooth;
	}
	/** Enable the voxel visualization */
	inline void enableMeshVoxel(void)
	{
		this->_status = (this->_status & kVisMeshDisable) | kVisMeshVoxel;
	}
	/** Return true if the mesh is enabled */
	inline bool isMeshEnabled(void) const
	{
		return (this->_status & (kVisNull ^ kVisMeshDisable));
	}
	/** Return true if the point visualization is enabled */
	inline bool isMeshPoint(void) const
	{
		return ((this->_status & kVisMeshPoint) && !(this->_status & kVisMeshFlat));
	}
	/** Return true if the flat shading is enabled */
	inline bool isMeshFlat(void) const
	{
		return (!(this->_status & kVisMeshPoint) && (this->_status & kVisMeshFlat));
	}
	/** Return true if the smooth shading is enabled */
	inline bool isMeshSmooth(void) const
	{
		return ((this->_status & kVisMeshPoint) && (this->_status & kVisMeshFlat));
	}
	/** Return true if the voxel visualization is enabled */
	inline bool isMeshVoxel(void) const
	{
		return (this->_status & kVisMeshVoxel);
	}

	/// COLOR
	/** Disable the colors visualization */
	inline void disableColor(void)
	{
		this->_status &= kVisColorDisable;
	}
	/** Enable the colors of the vertex */
	inline void enableColorVertex(void)
	{
		this->_status = (this->_status & kVisColorDisable) | kVisColorVertex;
	}
	/** Enable the colors of the faces */
	inline void enableColorFace(void)
	{
		this->_status = (this->_status & kVisColorDisable) | kVisColorFace;
	}
	/** Enable the texture */
	inline void enableColorTexture(void)
	{
		this->_status = (this->_status & kVisColorDisable) | kVisColorTexture;
	}
	/** Enable the quality color for vertex */
	inline void enableColorQualityVertex(void)
	{
		this->_status = (this->_status & kVisColorDisable) | kVisColorQualityV;
	}
	/** Enable the quality color for face */
	inline void enableColorQualityFace(void)
	{
		this->_status = (this->_status & kVisColorDisable) | kVisColorQualityF;
	}
	/** Enable the material color */
	inline void enableColorMaterial(void)
	{
		this->_status = (this->_status & kVisColorDisable) | kVisColorMaterial;
	}
	/** Return true if the color is enabled */
	inline bool isColorEnabled(void) const
	{
		return (this->_status & (kVisNull ^ kVisColorDisable));
	}
	/** Return true if the vertex color is enabled */
	inline bool isColorVertex(void) const
	{
		return ((this->_status & kVisColorVertex)
				&& !(this->_status & kVisColorFace)
				&& !(this->_status & kVisColorQualityV));
	}
	/** Return true if the face color is enabled */
	inline bool isColorFace(void) const
	{
		return (!(this->_status & kVisColorVertex)
				&& (this->_status & kVisColorFace)
				&& !(this->_status & kVisColorQualityV));
	}
	/** Return true if the texture is enabled */
	inline bool isColorTexture(void) const
	{
		return ((this->_status & kVisColorVertex)
				&& (this->_status & kVisColorFace)
				&& !(this->_status & kVisColorQualityV));
	}
	/** Return true if the quality color for vertex is enabled */
	inline bool isColorQualityV(void) const
	{
		return (!(this->_status & kVisColorVertex)
				&& !(this->_status & kVisColorFace)
				&& (this->_status & kVisColorQualityV));
	}
	/** Return true if the quality color for face is enabled */
	inline bool isColorQualityF(void) const
	{
		return ((this->_status & kVisColorVertex)
				&& !(this->_status & kVisColorFace)
				&& (this->_status & kVisColorQualityV));
	}
	/** Return true if the material color is enabled */
	inline bool isColorMaterial(void) const
	{
		return (!(this->_status & kVisColorVertex)
				&& (this->_status & kVisColorFace)
				&& (this->_status & kVisColorQualityV));
	}

	/// WIREFRAME
	/** Disable the wireframe visualization */
	inline void disableWireframe(void)
	{
		this->_status &= kVisWireDisable;
	}
	/** Enable the wireframe visualization */
	inline void enableWireframe(void)
	{
		this->_status |= kVisWireEnable;
	}
	/** Return true if the wireframe is enabled */
	inline bool isWireframeEnabled(void) const
	{
		return this->_status & kVisWireEnable;
	}

private:
	/// AND masks
	/** Used to turn off a visualization mode */
	static const unsigned int kVisReset         = 0x00000000; //0000 0000 0000 0000 0000 0000 0000 0000

	static const unsigned int kVisBoxDisable    = 0xCFFFFFFF; //1100 1111 1111 1111 1111 1111 1111 1111
	static const unsigned int kVisMeshDisable   = 0xF8FFFFFF; //1111 1000 1111 1111 1111 1111 1111 1111
	static const unsigned int kVisColorDisable  = 0xFF8FFFFF; //1111 1111 1000 1111 1111 1111 1111 1111
	static const unsigned int kVisWireDisable   = 0xFFFFBFFF; //1111 1111 1111 1111 1011 1111 1111 1111

	/// OR masks
	/** Used to turn on a visualization mode */
	static const unsigned int kVisNull          = 0xFFFFFFFF; //1111 1111 1111 1111 1111 1111 1111 1111

	static const unsigned int kVisBoxWired      = 0x10000000; //0001 0000 0000 0000 0000 0000 0000 0000
	static const unsigned int kVisBoxTrans      = 0x20000000; //0010 0000 0000 0000 0000 0000 0000 0000
	static const unsigned int kVisBoxSolid      = 0x30000000; //0011 0000 0000 0000 0000 0000 0000 0000
	static const unsigned int kVisMeshPoint     = 0x01000000; //0000 0001 0000 0000 0000 0000 0000 0000
	static const unsigned int kVisMeshFlat      = 0x02000000; //0000 0010 0000 0000 0000 0000 0000 0000
	static const unsigned int kVisMeshSmooth    = 0x03000000; //0000 0011 0000 0000 0000 0000 0000 0000
	static const unsigned int kVisMeshVoxel     = 0x04000000; //0000 0100 0000 0000 0000 0000 0000 0000
	static const unsigned int kVisColorVertex   = 0x00100000; //0000 0000 0001 0000 0000 0000 0000 0000
	static const unsigned int kVisColorFace     = 0x00200000; //0000 0000 0010 0000 0000 0000 0000 0000
	static const unsigned int kVisColorTexture  = 0x00300000; //0000 0000 0011 0000 0000 0000 0000 0000
	static const unsigned int kVisColorQualityV = 0x00400000; //0000 0000 0100 0000 0000 0000 0000 0000
	static const unsigned int kVisColorQualityF = 0x00500000; //0000 0000 0101 0000 0000 0000 0000 0000
	static const unsigned int kVisColorMaterial = 0x00600000; //0000 0000 0110 0000 0000 0000 0000 0000
	static const unsigned int kVisWireEnable    = 0x00004000; //0000 0000 0000 0000 0100 0000 0000 0000

	/// The current visualization mode
	unsigned int _status;
};

#endif // CGVIEW_OPENGL_MESH_MODE_VISUALMODE_H
