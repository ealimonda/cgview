/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: gllight.h                                                        *
 * Description: OpenGL Lights                                                 *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_OPENGL_SCENE_LIGHT_GLLIGHT_H
#define CGVIEW_OPENGL_SCENE_LIGHT_GLLIGHT_H

#include <QtOpenGL> // GL_*
#include "mesh_definition.h" // CGPoint

class GLLight
{
public:
	enum ColorChannel
	{
		kChannelRed = 0,
		kChannelGreen,
		kChannelBlue,
		kChannelAlpha,
		kChannelsMax,
		kChannelsRGB = kChannelBlue+1,
		kChannelsRGBA = kChannelAlpha+1,
	};

	GLLight();

	void getLight(void);

	/** LIT */
	//inline bool isOn(void) { return this->on; }
	inline void turnLight(bool b) { if (b) glEnable(GL_LIGHT0); else glEnable(GL_LIGHT0); }

	/** AMBIENT */
	inline float getAmbientRed(void) const   { return this->_ambient[kChannelRed]; }
	inline float getAmbientGreen(void) const { return this->_ambient[kChannelGreen]; }
	inline float getAmbientBlue(void) const  { return this->_ambient[kChannelBlue]; }
	inline float getAmbientAlpha(void) const { return this->_ambient[kChannelAlpha]; }
	inline CGPoint getAmbientRGB(void) const
	{
		return CGPoint(this->_ambient[kChannelRed], this->_ambient[kChannelGreen], this->_ambient[kChannelBlue]);
	}

	inline void setAmbientRed(float v)   { this->_ambient[kChannelRed] = v; }
	inline void setAmbientGreen(float v) { this->_ambient[kChannelGreen] = v; }
	inline void setAmbientBlue(float v)  { this->_ambient[kChannelBlue] = v; }
	inline void setAmbientAlpha(float v) { this->_ambient[kChannelAlpha] = v; }

	inline void setAmbientRGB(float r, float g, float b)
	{
		this->_ambient[kChannelRed] = r;
		this->_ambient[kChannelGreen] = g;
		this->_ambient[kChannelBlue] = b;
	}

	inline void setAmbientRGB(CGPoint p)
	{
		this->setAmbientRGB(p[kChannelRed], p[kChannelGreen], p[kChannelBlue]);
	}

	inline void setAmbientRGBA(float r, float g, float b, float a)
	{
		this->_ambient[kChannelRed] = r;
		this->_ambient[kChannelGreen] = g;
		this->_ambient[kChannelBlue] = b;
		this->_ambient[kChannelAlpha] = a;
	}

	inline void setAmbientWhite(float v) { this->setAmbientRGB(v, v, v); }

	/** DIFFUSE */
	inline float getDiffuseRed(void) const   { return this->_diffuse[kChannelRed]; }
	inline float getDiffuseGreen(void) const { return this->_diffuse[kChannelGreen]; }
	inline float getDiffuseBlue(void) const  { return this->_diffuse[kChannelBlue]; }
	inline float getDiffuseAlpha(void) const { return this->_diffuse[kChannelAlpha]; }
	inline CGPoint getDiffuseRGB(void) const
	{
		return CGPoint(this->_diffuse[kChannelRed],
				this->_diffuse[kChannelGreen],
				this->_diffuse[kChannelBlue]);
	}

	inline void setDiffuseRed(float v)   { this->_diffuse[kChannelRed] = v; }
	inline void setDiffuseGreen(float v) { this->_diffuse[kChannelGreen] = v; }
	inline void setDiffuseBlue(float v)  { this->_diffuse[kChannelBlue] = v; }
	inline void setDiffuseAlpha(float v) { this->_diffuse[kChannelAlpha] = v; }

	inline void setDiffuseRGB(float r, float g, float b)
	{
		this->_diffuse[kChannelRed] = r;
		this->_diffuse[kChannelGreen] = g;
		this->_diffuse[kChannelBlue] = b;
	}
	inline void setDiffuseRGB(CGPoint p)
	{
		this->setDiffuseRGB(p[kChannelRed], p[kChannelGreen], p[kChannelBlue]);
	}

	inline void setDiffuseRGBA(float r, float g, float b, float a)
	{
		this->_diffuse[kChannelRed] = r;
		this->_diffuse[kChannelGreen] = g;
		this->_diffuse[kChannelBlue] = b;
		this->_diffuse[kChannelAlpha] = a;
	}

	inline void setDiffuseWhite(float v) { this->setDiffuseRGB(v, v, v); }

	/** SPECULAR */
	inline float getSpecularRed(void) const   { return this->_specular[kChannelRed]; }
	inline float getSpecularGreen(void) const { return this->_specular[kChannelGreen]; }
	inline float getSpecularBlue(void) const  { return this->_specular[kChannelBlue]; }
	inline float getSpecularAlpha(void) const { return this->_specular[kChannelAlpha]; }
	inline CGPoint getSpecularRGB(void) const
	{
		return CGPoint(this->_specular[kChannelRed],
			       this->_specular[kChannelGreen],
			       this->_specular[kChannelBlue]);
	}

	inline void setSpecularRed(float v)   { this->_specular[kChannelRed] = v; }
	inline void setSpecularGreen(float v) { this->_specular[kChannelGreen] = v; }
	inline void setSpecularBlue(float v)  { this->_specular[kChannelBlue] = v; }
	inline void setSpecularAlpha(float v) { this->_specular[kChannelAlpha] = v; }

	inline void setSpecularRGB(float r, float g, float b)
	{
		this->_specular[kChannelRed] = r;
		this->_specular[kChannelGreen] = g;
		this->_specular[kChannelBlue] = b;
	}

	inline void setSpecularRGB(CGPoint p) {
		this->setSpecularRGB(p[kChannelRed], p[kChannelGreen], p[kChannelBlue]);
	}

	inline void setSpecularRGBA(float r, float g, float b, float a)
	{
		this->_specular[kChannelRed] = r;
		this->_specular[kChannelGreen] = g;
		this->_specular[kChannelBlue] = b;
		this->_specular[kChannelAlpha] = a;
	}

	inline void setSpecularWhite(float v) { this->setSpecularRGB(v, v, v); }

	/** POSITION */
	inline float getPositionX(void) const { return this->_position[kCoordX]; }
	inline float getPositionY(void) const { return this->_position[kCoordY]; }
	inline float getPositionZ(void) const { return this->_position[kCoordZ]; }
	inline float getPositionW(void) const { return this->_position[kCoordW]; }
	inline CGPoint getPositionXYZ(void) const
	{
		return CGPoint(this->_position[kCoordX], this->_position[kCoordY], this->_position[kCoordZ]);
	}

	inline void setPositionX(float v) { this->_position[kCoordX] = v; }
	inline void setPositionY(float v) { this->_position[kCoordY] = v; }
	inline void setPositionZ(float v) { this->_position[kCoordZ] = v; }
	inline void setPositionW(float v) { this->_position[kCoordW] = v; }

	inline void setPositionXYZ(float x, float y, float z)
	{
		this->_position[kCoordX] = x;
		this->_position[kCoordY] = y;
		this->_position[kCoordZ] = z;
	}

	inline void setPositionXYZ(CGPoint p) { this->setPositionXYZ(p[kCoordX], p[kCoordY], p[kCoordZ]); }

	inline void setPositionXYZW(float x, float y, float z, float w)
	{
		this->_position[kCoordX] = x;
		this->_position[kCoordY] = y;
		this->_position[kCoordZ] = z;
		this->_position[kCoordW] = w;
	}

	/** SPOT DIRECTION */
	inline float getDirectionX(void) const { return this->_direction[kCoordX]; }
	inline float getDirectionY(void) const { return this->_direction[kCoordY]; }
	inline float getDirectionZ(void) const { return this->_direction[kCoordZ]; }
	inline CGPoint getDirectionXYZ(void) const
	{
		return CGPoint(this->_direction[kCoordX], this->_direction[kCoordY], this->_direction[kCoordZ]);
	}

	inline void setDirectionX(float v) { this->_direction[kCoordX] = v; }
	inline void setDirectionY(float v) { this->_direction[kCoordY] = v; }
	inline void setDirectionZ(float v) { this->_direction[kCoordZ] = v; }
	inline void setDirectionXYZ(float x, float y, float z)
	{
		this->_direction[kCoordX] = x;
		this->_direction[kCoordY] = y;
		this->_direction[kCoordZ] = z;
	}
	inline void setDirectionXYZ(CGPoint p) { this->setDirectionXYZ(p[kCoordX], p[kCoordY], p[kCoordZ]); }

	/** SPOT EXPONENT */
	inline float getExponent(void) const { return this->_exponent[0]; }
	inline void setExponent(float v) { this->_exponent[0] = v; }

	/** SPOT CUTOFF */
	inline float getCutOff(void) const { return this->_cutoff[0]; }
	inline void setCutOff(float v) { this->_cutoff[0] = v; }

	/** CONSTANT ATTENUATION */
	inline float getConstantAttenuation(void) const { return this->_att_const[0]; }
	inline void setConstantAttenuation(float v) { this->_att_const[0] = v; }

	/** LINEAR ATTENUATION */
	inline float getLinearAttenuation(void) const { return this->_att_lin[0]; }
	inline void setLinearAttenuation(float v) { this->_att_lin[0] = v; }

	/** QUADRATIC ATTENUATION */
	inline float getQuadraticAttenuation(void) const { return this->_att_quad[0]; }
	inline void setQuadraticAttenuation(float v) { this->_att_quad[0] = v; }

	/** RESET */
	void reset( void );

private:
	bool _on;

	float _ambient[kChannelsRGBA];
	float _diffuse[kChannelsRGBA];
	float _specular[kChannelsRGBA];
	float _position[kCoordsXYZW];
	float _direction[kCoordsXYZ];
	float _exponent[1];
	float _cutoff[1];
	float _att_const[1];
	float _att_lin[1];
	float _att_quad[1];
};

#endif // CGVIEW_OPENGL_SCENE_LIGHT_GLLIGHT_H
