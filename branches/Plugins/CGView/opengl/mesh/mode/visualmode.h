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
    //Disable the bounding box
    inline void Disable_Box()
    {
        _status = _status & VIS_BOX_DISABLE;
    }
    //Enable the wired bounding box
    inline void Enable_Box_Wired()
    {
        _status = (_status & VIS_BOX_DISABLE) | VIS_BOX_WIRED;
    }
    //Enable the transparent bounding box
    inline void Enable_Box_Trans()
    {
        _status = (_status & VIS_BOX_DISABLE) | VIS_BOX_TRANS;
    }
    //Enable the solid bounding box
    inline void Enable_Box_Solid()
    {
        _status = (_status & VIS_BOX_DISABLE) | VIS_BOX_SOLID;
    }

    //Return true if the box is disabled
    inline bool isBoxDisabled()
    {
        return !(_status & (VIS_NULL ^ VIS_BOX_DISABLE));
    }
    //Return true if the box is enabled
    inline bool isBoxEnabled()
    {
        return (_status & (VIS_NULL ^ VIS_BOX_DISABLE));
    }
    //Return true if the wired box is enabled
    inline bool isBoxWired()
    {
        return ((_status & VIS_BOX_WIRED) && !(_status & VIS_BOX_TRANS));
    }
    //Return true if the transparent box is enabled
    inline bool isBoxTrans()
    {
        return(!(_status & VIS_BOX_WIRED) && (_status & VIS_BOX_TRANS));
    }
    //Return true if the solid box is enabled
    inline bool isBoxSolid()
    {
        return ((_status & VIS_BOX_WIRED) && (_status & VIS_BOX_TRANS));
    }

	/// MESH
    //Disable the mesh visualization
    inline void Disable_Mesh()
    {
        _status = _status & VIS_MESH_DISABLE;
    }
    //Enable the visualization of the point of the mesh
    inline void Enable_Mesh_Point()
    {
        _status = (_status & VIS_MESH_DISABLE) | VIS_MESH_POINT;
    }
    //Enable the flat shading visualization of the mesh
    inline void Enable_Mesh_Flat()
    {
        _status = (_status & VIS_MESH_DISABLE) | VIS_MESH_FLAT;
    }
    //Enable the smooth shading visualization of the mesh
    inline void Enable_Mesh_Smooth()
    {
        _status = (_status & VIS_MESH_DISABLE) | VIS_MESH_SMOOTH;
    }
    //Enable the voxel visualization
    inline void Enable_Mesh_Voxel()
    {
        _status = (_status & VIS_MESH_DISABLE) | VIS_MESH_VOXEL;
    }

    //Return true if the mesh is disabled
    inline bool isMeshDisabled()
    {
        return !(_status & (VIS_NULL ^ VIS_MESH_DISABLE));
    }
    //Return true if the mesh is enabled
    inline bool isMeshEnabled()
    {
        return (_status & (VIS_NULL ^ VIS_MESH_DISABLE));
    }
    //Return true if the point visualization is enabled
    inline bool isMeshPoint()
    {
        return ((_status & VIS_MESH_POINT) && !(_status & VIS_MESH_FLAT));
    }
    //Return true if the flat shading is enabled
    inline bool isMeshFlat()
    {
        return (!(_status & VIS_MESH_POINT) && (_status & VIS_MESH_FLAT));
    }
    //Return true if the smooth shading is enabled
    inline bool isMeshSmooth()
    {
        return ((_status & VIS_MESH_POINT) && (_status & VIS_MESH_FLAT));
    }
    //Return true if the voxel visualization is enabled
    inline bool isMeshVoxel()
    {
        return (_status & VIS_MESH_VOXEL);
    }

	/// COLOR
    //Disable the colors visualization
    inline void Disable_Color()
    {
        _status = _status & VIS_COLOR_DISABLE;
    }
    //Enable the colors of the vertex
    inline void Enable_Color_Vertex()
    {
        _status = (_status & VIS_COLOR_DISABLE) | VIS_COLOR_VERTEX;
    }
    //Enable the colors of the faces
    inline void Enable_Color_Face()
    {
        _status = (_status & VIS_COLOR_DISABLE) | VIS_COLOR_FACE;
    }
    //Enable the texture
    inline void Enable_Color_Texture()
    {
        _status = (_status & VIS_COLOR_DISABLE) | VIS_COLOR_TEXTURE;
    }
    //Enable the quality color for vertex
    inline void Enable_Color_Quality_Vertex()
    {
        _status = (_status & VIS_COLOR_DISABLE) | VIS_COLOR_QUALITY_V;
    }
    //Enable the quality color for face
    inline void Enable_Color_Quality_Face()
    {
        _status = (_status & VIS_COLOR_DISABLE) | VIS_COLOR_QUALITY_F;
    }
    //Enable the material color
    inline void Enable_Color_Material()
    {
        _status = (_status & VIS_COLOR_DISABLE) | VIS_COLOR_MATERIAL;
    }

    //Return true if the color is disabled
    inline bool isColorDisabled()
    {
        return !(_status & (VIS_NULL ^ VIS_COLOR_DISABLE));
    }
    //Return true if the color is enabled
    inline bool isColorEnabled()
    {
        return (_status & (VIS_NULL ^ VIS_COLOR_DISABLE));
    }
    //Return true if the vertex color is enabled
    inline bool isColorVertex()
    {
        return ((_status & VIS_COLOR_VERTEX) && !(_status & VIS_COLOR_FACE) && !(_status & VIS_COLOR_QUALITY_V));
    }
    //Return true if the face color is enabled
    inline bool isColorFace()
    {
        return (!(_status & VIS_COLOR_VERTEX) && (_status & VIS_COLOR_FACE) && !(_status & VIS_COLOR_QUALITY_V));
    }
    //Return true if the texture is enabled
    inline bool isColorTexture()
    {
        return ((_status & VIS_COLOR_VERTEX) && (_status & VIS_COLOR_FACE) && !(_status & VIS_COLOR_QUALITY_V));
    }
    //Return true if the quality color for vertex is enabled
    inline bool isColorQualityV()
    {
        return (!(_status & VIS_COLOR_VERTEX) && !(_status & VIS_COLOR_FACE) && (_status & VIS_COLOR_QUALITY_V));
    }
    //Return true if the quality color for face is enabled
    inline bool isColorQualityF()
    {
        return ((_status & VIS_COLOR_VERTEX) && !(_status & VIS_COLOR_FACE) && (_status & VIS_COLOR_QUALITY_V));
    }
    //Return true if the material color is enabled
    inline bool isColorMaterial()
    {
        return (!(_status & VIS_COLOR_VERTEX) && (_status & VIS_COLOR_FACE) && (_status & VIS_COLOR_QUALITY_V));
    }

	/// NORMAL
    //Disable the vertex and the face normals
    inline void Disable_Normal()
    {
        _status = _status & VIS_NORMAL_DISABLE;
    }
    //Disable the vertex normals
    inline void Disable_Normal_Vertex()
    {
        _status = _status & (VIS_NORMAL_VERTEX ^ VIS_NULL);
    }
    //Disable the face normals
    inline void Disable_Normal_Face()
    {
        _status = _status & (VIS_NORMAL_FACE ^ VIS_NULL);
    }
    //Enable the vertex normals
    inline void Enable_Normal_Vertex()
    {
        _status = _status | VIS_NORMAL_VERTEX;
    }
    //Enable the face normals
    inline void Enable_Normal_Face()
    {
        _status = _status | VIS_NORMAL_FACE;
    }

    //Return true if the normal visualization is disabled
    inline bool isNormalDisabled()
    {
        return !(_status & (VIS_NULL ^ VIS_NORMAL_DISABLE));
    }
    //Return true if the normal visualization is enabled
    inline bool isNormalEnabled()
    {
        return (_status & (VIS_NULL ^ VIS_NORMAL_DISABLE));
    }
    //Return true if the vertex normals are enabled
    inline bool isNormalVertex()
    {
        return (_status & VIS_NORMAL_VERTEX);
    }
    //Return true if the face normals are enabled
    inline bool isNormalFace()
    {
        return (_status & VIS_NORMAL_FACE);
    }

	/// WIREFRAME
    //Disable the wireframe visualization
    inline void Disable_Wireframe()
    {
        _status = _status & VIS_WIRE_DISABLE;
    }
    //Enable the wireframe visualization
    inline void Enable_Wireframe()
    {
        _status = _status | VIS_WIRE_ENABLE;
    }

    //Return true if the wireframe is disabled
    inline bool isWireframeDisabled()
    {
        return !(_status & VIS_WIRE_ENABLE);
    }
    //Return true if the wireframe is enabled
    inline bool isWireframeEnabled()
    {
        return _status & VIS_WIRE_ENABLE;
    }

	/// GRID
    //Disable the grid visualization
    inline void Disable_Grid()
    {
        _status = _status & VIS_GRID_DISABLE;
    }
    //Enable the grid visualization
    inline void Enable_Grid()
    {
        _status = _status | VIS_GRID_ENABLE;
    }

    //Return true if the grid is disabled
    inline bool isGridDisabled()
    {
        return !(_status & VIS_GRID_ENABLE);
    }
    //Return true if the grid is enabled
    inline bool isGridEnabled()
    {
        return _status & VIS_GRID_ENABLE;
    }

	/// AXIS
    //Disable the axis visualization
    inline void Disable_Axis()
    {
        _status = _status & VIS_AXIS_DISABLE;
    }
    //Enable the axis visualization
    inline void Enable_Axis()
    {
        _status = _status | VIS_AXIS_ENABLE;
    }

    //Return true if the axis visualization is disabled
    inline bool isAxisDisabled()
    {
        return !(_status & VIS_WIRE_ENABLE);
    }
    //Return true if the axis visualization is enabled
    inline bool isAxisEnabled()
    {
        return _status & VIS_AXIS_ENABLE;
    }


private:

protected:
    /// AND masks
    //Used to turn off a visualization mode
    static const unsigned int VIS_RESET           = 0x00000000; //0000 0000 0000 0000 0000 0000 0000 0000

    static const unsigned int VIS_BOX_DISABLE     = 0xCFFFFFFF; //1100 1111 1111 1111 1111 1111 1111 1111
    static const unsigned int VIS_MESH_DISABLE    = 0xF8FFFFFF; //1111 1000 1111 1111 1111 1111 1111 1111
    static const unsigned int VIS_COLOR_DISABLE   = 0xFF8FFFFF; //1111 1111 1000 1111 1111 1111 1111 1111
    static const unsigned int VIS_NORMAL_DISABLE  = 0xFFFCFFFF; //1111 1111 1111 1100 1111 1111 1111 1111
    static const unsigned int VIS_WIRE_DISABLE    = 0xFFFFBFFF; //1111 1111 1111 1111 1011 1111 1111 1111
    static const unsigned int VIS_GRID_DISABLE    = 0xFFFFDFFF; //1111 1111 1111 1111 1101 1111 1111 1111
    static const unsigned int VIS_AXIS_DISABLE    = 0xFFFFEFFF; //1111 1111 1111 1111 1110 1111 1111 1111

    /// OR masks
    //Used to turn on a visualization mode
    static const unsigned int VIS_NULL            = 0xFFFFFFFF; //1111 1111 1111 1111 1111 1111 1111 1111

    static const unsigned int VIS_BOX_WIRED       = 0x10000000; //0001 0000 0000 0000 0000 0000 0000 0000
    static const unsigned int VIS_BOX_TRANS       = 0x20000000; //0010 0000 0000 0000 0000 0000 0000 0000
    static const unsigned int VIS_BOX_SOLID       = 0x30000000; //0011 0000 0000 0000 0000 0000 0000 0000
    static const unsigned int VIS_MESH_POINT      = 0x01000000; //0000 0001 0000 0000 0000 0000 0000 0000
    static const unsigned int VIS_MESH_FLAT       = 0x02000000; //0000 0010 0000 0000 0000 0000 0000 0000
    static const unsigned int VIS_MESH_SMOOTH     = 0x03000000; //0000 0011 0000 0000 0000 0000 0000 0000
    static const unsigned int VIS_MESH_VOXEL      = 0x04000000; //0000 0100 0000 0000 0000 0000 0000 0000
    static const unsigned int VIS_COLOR_VERTEX    = 0x00100000; //0000 0000 0001 0000 0000 0000 0000 0000
    static const unsigned int VIS_COLOR_FACE      = 0x00200000; //0000 0000 0010 0000 0000 0000 0000 0000
    static const unsigned int VIS_COLOR_TEXTURE   = 0x00300000; //0000 0000 0011 0000 0000 0000 0000 0000
    static const unsigned int VIS_COLOR_QUALITY_V = 0x00400000; //0000 0000 0100 0000 0000 0000 0000 0000
    static const unsigned int VIS_COLOR_QUALITY_F = 0x00500000; //0000 0000 0101 0000 0000 0000 0000 0000
    static const unsigned int VIS_COLOR_MATERIAL  = 0x00600000; //0000 0000 0110 0000 0000 0000 0000 0000
    static const unsigned int VIS_NORMAL_VERTEX   = 0x00010000; //0000 0000 0000 0001 0000 0000 0000 0000
    static const unsigned int VIS_NORMAL_FACE     = 0x00020000; //0000 0000 0000 0010 0000 0000 0000 0000
    static const unsigned int VIS_WIRE_ENABLE     = 0x00004000; //0000 0000 0000 0000 0100 0000 0000 0000
    static const unsigned int VIS_GRID_ENABLE     = 0x00002000; //0000 0000 0000 0000 0010 0000 0000 0000
    static const unsigned int VIS_AXIS_ENABLE     = 0x00001000; //0000 0000 0000 0000 0001 0000 0000 0000



    //The current visualization mode
    unsigned int _status;
};

#endif // VISUALMODE_H
