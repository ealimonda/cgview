/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glmaterial.h                                                     *
 * Description: OpenGL material definitions                                   *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_OPENGL_MESH_MATERIAL_GLMATERIAL_H
#define CGVIEW_OPENGL_MESH_MATERIAL_GLMATERIAL_H

#include <QtOpenGL> // GL_*
#include "mesh_definition.h" // CGPoint
#include "opengl/scene/light/gllight.h" // GLLight

class GLMaterial
{
public:
	enum MaterialType
	{
		kMaterialDefault,
		kMaterialEmerald,
		kMaterialJade,
		kMaterialObsidian,
		kMaterialPearl,
		kMaterialRuby,
		kMaterialTurquoise,
		kMaterialBrass,
		kMaterialBronze,
		kMaterialPolishedBronze,
		kMaterialChrome,
		kMaterialCopper,
		kMaterialPolishedCopper,
		kkMaterialGold,
		kMaterialPolishedGold,
		kMaterialSilver,
		kMaterialPolishedSilver,
		kMaterialPewter,
		kMaterialBlackPlastic,
		//kMaterialCyanPlastic,
		//kMaterialGreenPlastic,
		//kMaterialRedPlastic,
		//kMaterialWhitePlastic,
		//kMaterialYellowPlastic,
		kMaterialBlackRubber,
		//kMaterialCyanRubber,
		//kMaterialGreenRubber,
		//kMaterialRedRubber,
		//kMaterialWhiteRubber,
		//kMaterialYellowRubber,
		kMaterialsMax
	};
	struct GLMaterialData
	{
		float ambient[GLLight::kChannelsMax];
		float diffuse[GLLight::kChannelsMax];
		float specular[GLLight::kChannelsMax];
		float emission[GLLight::kChannelsMax];
		float shininess[1]; // in the range 0.0f - 1.0f
	};

	/**
	 * Constructor
	 */
	inline GLMaterial(void) { this->reset(); }

	inline void getMaterial(void) const
	{
		float s[1] = { this->_materialdata.shininess[0] * 128.0f };

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   this->_materialdata.ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   this->_materialdata.diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  this->_materialdata.specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  this->_materialdata.emission);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, s);
	}

	inline void setMaterial(struct GLMaterialData m) { this->_materialdata = m; }

	inline void setMaterial(MaterialType t) { this->setMaterial(kPreset[t]); }
	inline void setMaterial(const int i) { this->setMaterial(kPreset[i]); }

	/** AMBIENT **/
	inline float getAmbientRed(void ) const   { return this->_materialdata.ambient[GLLight::kChannelRed]; }
	inline float getAmbientGreen(void) const { return this->_materialdata.ambient[GLLight::kChannelGreen]; }
	inline float getAmbientBlue(void) const  { return this->_materialdata.ambient[GLLight::kChannelBlue]; }
	inline float getAmbientAlpha(void) const { return this->_materialdata.ambient[GLLight::kChannelAlpha]; }
	inline CGPoint getAmbientRGB(void) const
	{
		return CGPoint(this->_materialdata.ambient[GLLight::kChannelRed],
				this->_materialdata.ambient[GLLight::kChannelGreen],
				this->_materialdata.ambient[GLLight::kChannelBlue]);
	}

	inline void setAmbientRed(float v)   { this->_materialdata.ambient[GLLight::kChannelRed] = v; }
	inline void setAmbientGreen(float v) { this->_materialdata.ambient[GLLight::kChannelGreen] = v; }
	inline void setAmbientBlue(float v)  { this->_materialdata.ambient[GLLight::kChannelBlue] = v; }
	inline void setAmbientAlpha(float v) { this->_materialdata.ambient[GLLight::kChannelAlpha] = v; }
	inline void setAmbientRGB(float r, float g, float b )
	{
		this->_materialdata.ambient[GLLight::kChannelRed] = r;
		this->_materialdata.ambient[GLLight::kChannelGreen] = g;
		this->_materialdata.ambient[GLLight::kChannelBlue] = b;
	}
	inline void setAmbientRGB(CGPoint &p)
	{
		this->setAmbientRGB(p[GLLight::kChannelRed], p[GLLight::kChannelGreen], p[GLLight::kChannelBlue]);
	}
	inline void setAmbientRGBA(float r, float g, float b, float a)
	{
		this->_materialdata.ambient[GLLight::kChannelRed] = r;
		this->_materialdata.ambient[GLLight::kChannelGreen] = g;
		this->_materialdata.ambient[GLLight::kChannelBlue] = b;
		this->_materialdata.ambient[GLLight::kChannelAlpha] = a;
	}
	inline void setAmbientWhite(float v) { this->setAmbientRGB(v, v, v); }

	/** DIFFUSE **/
	inline float getDiffuseRed(void)   const { return this->_materialdata.diffuse[GLLight::kChannelRed]; }
	inline float getDiffuseGreen(void) const { return this->_materialdata.diffuse[GLLight::kChannelGreen]; }
	inline float getDiffuseBlue(void)  const { return this->_materialdata.diffuse[GLLight::kChannelBlue]; }
	inline float getDiffuseAlpha(void) const { return this->_materialdata.diffuse[GLLight::kChannelAlpha]; }
	inline CGPoint getDiffuseRGB(void) const
	{
		return CGPoint(this->_materialdata.diffuse[GLLight::kChannelRed],
				this->_materialdata.diffuse[GLLight::kChannelGreen],
				this->_materialdata.diffuse[GLLight::kChannelBlue]);
	}

	inline void setDiffuseRed(float v)   { this->_materialdata.diffuse[GLLight::kChannelRed] = v; }
	inline void setDiffuseGreen(float v) { this->_materialdata.diffuse[GLLight::kChannelGreen] = v; }
	inline void setDiffuseBlue(float v)  { this->_materialdata.diffuse[GLLight::kChannelBlue] = v; }
	inline void setDiffuseAlpha(float v) { this->_materialdata.diffuse[GLLight::kChannelAlpha] = v; }
	inline void setDiffuseRGB(float r, float g, float b)
	{
		this->_materialdata.diffuse[GLLight::kChannelRed] = r;
		this->_materialdata.diffuse[GLLight::kChannelGreen] = g;
		this->_materialdata.diffuse[GLLight::kChannelBlue] = b;
	}
	inline void setDiffuseRGB(CGPoint &p)
	{
		this->setDiffuseRGB(p[GLLight::kChannelRed], p[GLLight::kChannelGreen], p[GLLight::kChannelBlue]);
	}
	inline void setDiffuseRGBA(float r, float g, float b, float a)
	{
		this->_materialdata.diffuse[GLLight::kChannelRed] = r;
		this->_materialdata.diffuse[GLLight::kChannelGreen] = g;
		this->_materialdata.diffuse[GLLight::kChannelBlue] = b;
		this->_materialdata.diffuse[GLLight::kChannelAlpha] = a;
	}
	inline void setDiffuseWhite(float v) { this->setDiffuseRGB(v, v, v); }

	/** SPECULAR **/
	inline float getSpecularRed(void)   const { return this->_materialdata.specular[GLLight::kChannelRed]; }
	inline float getSpecularGreen(void) const { return this->_materialdata.specular[GLLight::kChannelGreen]; }
	inline float getSpecularBlue(void)  const { return this->_materialdata.specular[GLLight::kChannelBlue]; }
	inline float getSpecularAlpha(void) const { return this->_materialdata.specular[GLLight::kChannelAlpha]; }
	inline CGPoint getSpecularRGB(void) const
	{
		return CGPoint(this->_materialdata.specular[GLLight::kChannelRed],
				this->_materialdata.specular[GLLight::kChannelGreen],
				this->_materialdata.specular[GLLight::kChannelBlue]);
	}

	inline void setSpecularRed(float v)   { this->_materialdata.specular[GLLight::kChannelRed] = v; }
	inline void setSpecularGreen(float v) { this->_materialdata.specular[GLLight::kChannelGreen] = v; }
	inline void setSpecularBlue(float v)  { this->_materialdata.specular[GLLight::kChannelBlue] = v; }
	inline void setSpecularAlpha(float v) { this->_materialdata.specular[GLLight::kChannelAlpha] = v; }
	inline void setSpecularRGB(float r, float g, float b)
	{
		this->_materialdata.specular[GLLight::kChannelRed] = r;
		this->_materialdata.specular[GLLight::kChannelGreen] = g;
		this->_materialdata.specular[GLLight::kChannelBlue] = b;
	}
	inline void setSpecularRGB(CGPoint &p)
	{
		this->setSpecularRGB(p[GLLight::kChannelRed], p[GLLight::kChannelGreen], p[GLLight::kChannelBlue]);
	}
	inline void setSpecularRGBA(float r, float g, float b, float a)
	{
		this->_materialdata.specular[GLLight::kChannelRed] = r;
		this->_materialdata.specular[GLLight::kChannelGreen] = g;
		this->_materialdata.specular[GLLight::kChannelBlue] = b;
		this->_materialdata.specular[GLLight::kChannelAlpha] = a;
	}
	inline void setSpecularWhite(float v) { this->setSpecularRGB(v, v, v); }

	/** EMISSION **/
	inline float getEmissionRed(void)   const { return this->_materialdata.emission[GLLight::kChannelRed]; }
	inline float getEmissionGreen(void) const { return this->_materialdata.emission[GLLight::kChannelGreen]; }
	inline float getEmissionBlue(void)  const { return this->_materialdata.emission[GLLight::kChannelBlue]; }
	inline float getEmissionAlpha(void) const { return this->_materialdata.emission[GLLight::kChannelAlpha]; }
	inline CGPoint getEmissionRGB(void) const
	{
		return CGPoint(this->_materialdata.emission[GLLight::kChannelRed],
				this->_materialdata.emission[GLLight::kChannelGreen],
				this->_materialdata.emission[GLLight::kChannelBlue]);
	}

	inline void setEmissionRed(float v)   { this->_materialdata.emission[GLLight::kChannelRed] = v; }
	inline void setEmissionGreen(float v) { this->_materialdata.emission[GLLight::kChannelGreen] = v; }
	inline void setEmissionBlue(float v)  { this->_materialdata.emission[GLLight::kChannelBlue] = v; }
	inline void setEmissionAlpha(float v) { this->_materialdata.emission[GLLight::kChannelAlpha] = v; }
	inline void setEmissionRGB(float r, float g, float b)
	{
		this->_materialdata.emission[GLLight::kChannelRed] = r;
		this->_materialdata.emission[GLLight::kChannelGreen] = g;
		this->_materialdata.emission[GLLight::kChannelBlue] = b;
	}
	inline void setEmissionRGB(CGPoint &p)
	{
		this->setEmissionRGB(p[GLLight::kChannelRed], p[GLLight::kChannelGreen], p[GLLight::kChannelBlue]);
	}
	inline void setEmissionRGBA(float r, float g, float b, float a)
	{
		this->_materialdata.emission[GLLight::kChannelRed] = r;
		this->_materialdata.emission[GLLight::kChannelGreen] = g;
		this->_materialdata.emission[GLLight::kChannelBlue] = b;
		this->_materialdata.emission[GLLight::kChannelAlpha] = a;
	}
	inline void setEmissionWhite(float v) { this->setEmissionRGB(v, v, v); }

	/** SHININESS **/
	inline float getShininess(void) const { return this->_materialdata.shininess[0]; }
	inline void setShininess(float v) { this->_materialdata.shininess[0] = v * 128.0f; }

	/** RESET **/
	inline void reset(void) { this->setMaterial(GLMaterial::kMaterialDefault); }

private:
	static const GLMaterialData kPreset[];

	struct GLMaterialData _materialdata;
};

#endif // CGVIEW_OPENGL_MESH_MATERIAL_GLMATERIAL_H
