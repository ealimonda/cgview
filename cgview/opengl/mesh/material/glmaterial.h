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


#ifndef GLMATERIAL_H
#define GLMATERIAL_H

#include <QtOpenGL/QtOpenGL>
#include <fstream>
#include "mesh_definition.h"


class GLMaterial
{
public:
    enum MaterialType
    {
        DEFAULT,
        EMERALD,
        JADE,
        OBSIDIAN,
        PEARL,
        RUBY,
        TURQUOISE,
        BRASS,
        BRONZE,
        POLISHED_BRONZE,
        CHROME,
        COPPER,
        POLISHED_COPPER,
        GOLD,
        POLISHED_GOLD,
        SILVER,
        POLISHED_SILVER,
        PEWTER,
        BLACK_PLASTIC,
        //CYAN_PLASTIC,
        //GREEN_PLASTIC,
        //RED_PLASTIC,
        //WHITE_PLASTIC,
        //YELLOW_PLASTIC,
        BLACK_RUBBER//,
        //CYAN_RUBBER,
        //GREEN_RUBBER,
        //RED_RUBBER,
        //WHITE_RUBBER,
        //YELLOW_RUBBER,

    };

    //Constructor
    inline GLMaterial() { Reset(); }

    inline void getMaterial()
    {
        float s[1] = { _shininess[0] * 128.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,     _ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,     _diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,    _specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,    _emission);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,   s);
    }

    inline void setMaterial(const float m[])
    {
        _ambient[0] = m[0];
        _ambient[1] = m[1];
        _ambient[2] = m[2];
        _ambient[3] = m[3];

        _diffuse[0] = m[4];
        _diffuse[1] = m[5];
        _diffuse[2] = m[6];
        _diffuse[3] = m[7];

        _specular[0] = m[8];
        _specular[1] = m[9];
        _specular[2] = m[10];
        _specular[3] = m[11];

        _emission[0] = m[12];
        _emission[1] = m[13];
        _emission[2] = m[14];
        _emission[3] = m[15];

        _shininess[0] = m[16];
    }
    inline void setMaterial(MaterialType t)
    {
        setMaterial(PRESET[t]);
    }
    inline void setMaterial(const int i)
    {
        setMaterial(PRESET[i]);
    }

    //----------- AMBIENT -----------//
    inline float getAmbientRed()   { return _ambient[0]; }
    inline float getAmbientGreen() { return _ambient[1]; }
    inline float getAmbientBlue()  { return _ambient[2]; }
    inline float getAmbientAlpha() { return _ambient[3]; }
    inline CGPoint getAmbientRGB() { return CGPoint(_ambient[0], _ambient[1], _ambient[2]); }

    inline void setAmbientRed(float v)   { _ambient[0] = v; }
    inline void setAmbientGreen(float v) { _ambient[1] = v; }
    inline void setAmbientBlue(float v)  { _ambient[2] = v; }
    inline void setAmbientAlpha(float v) { _ambient[3] = v; }

    inline void setAmbientRGB(float r, float g, float b)
    {
        _ambient[0] = r;
        _ambient[1] = g;
        _ambient[2] = b;
    }

    inline void setAmbientRGB(CGPoint &p)
    {
        _ambient[0] = p[0];
        _ambient[1] = p[1];
        _ambient[2] = p[2];
    }

    inline void setAmbientRGBA(float r, float g, float b, float a)
    {
        _ambient[0] = r;
        _ambient[1] = g;
        _ambient[2] = b;
        _ambient[3] = a;
    }

    inline void setAmbientWhite(float v)
    {
        _ambient[0] = v;
        _ambient[1] = v;
        _ambient[2] = v;
    }

    //----------- DIFFUSE -----------//
    inline float getDiffuseRed()   { return _diffuse[0]; }
    inline float getDiffuseGreen() { return _diffuse[1]; }
    inline float getDiffuseBlue()  { return _diffuse[2]; }
    inline float getDiffuseAlpha() { return _diffuse[3]; }
    inline CGPoint getDiffuseRGB() { return CGPoint(_diffuse[0], _diffuse[1], _diffuse[2]); }

    inline void setDiffuseRed(float v)   { _diffuse[0] = v; }
    inline void setDiffuseGreen(float v) { _diffuse[1] = v; }
    inline void setDiffuseBlue(float v)  { _diffuse[2] = v; }
    inline void setDiffuseAlpha(float v) { _diffuse[3] = v; }

    inline void setDiffuseRGB(float r, float g, float b)
    {
        _diffuse[0] = r;
        _diffuse[1] = g;
        _diffuse[2] = b;
    }
    inline void setDiffuseRGB(CGPoint &p)
    {
        _diffuse[0] = p[0];
        _diffuse[1] = p[1];
        _diffuse[2] = p[2];
    }

    inline void setDiffuseRGBA(float r, float g, float b, float a)
    {
        _diffuse[0] = r;
        _diffuse[1] = g;
        _diffuse[2] = b;
        _diffuse[3] = a;
    }

    inline void setDiffuseWhite(float v)
    {
        _diffuse[0] = v;
        _diffuse[1] = v;
        _diffuse[2] = v;
    }

    //----------- SPECULAR -----------//
    inline float getSpecularRed()   { return _specular[0]; }
    inline float getSpecularGreen() { return _specular[1]; }
    inline float getSpecularBlue()  { return _specular[2]; }
    inline float getSpecularAlpha() { return _specular[3]; }
    inline CGPoint getSpecularRGB() { return CGPoint(_specular[0], _specular[1], _specular[2]); }

    inline void setSpecularRed(float v)   { _specular[0] = v; }
    inline void setSpecularGreen(float v) { _specular[1] = v; }
    inline void setSpecularBlue(float v)  { _specular[2] = v; }
    inline void setSpecularAlpha(float v) { _specular[3] = v; }

    inline void setSpecularRGB(float r, float g, float b)
    {
        _specular[0] = r;
        _specular[1] = g;
        _specular[2] = b;
    }

    inline void setSpecularRGB(CGPoint &p)
    {
        _specular[0] = p[0];
        _specular[1] = p[1];
        _specular[2] = p[2];
    }

    inline void setSpecularRGBA(float r, float g, float b, float a)
    {
        _specular[0] = r;
        _specular[1] = g;
        _specular[2] = b;
        _specular[3] = a;
    }

    inline void setSpecularWhite(float v)
    {
        _specular[0] = v;
        _specular[1] = v;
        _specular[2] = v;
    }

    //----------- EMISSION -----------//
    inline float getEmissionRed()   { return _emission[0]; }
    inline float getEmissionGreen() { return _emission[1]; }
    inline float getEmissionBlue()  { return _emission[2]; }
    inline float getEmissionAlpha() { return _emission[3]; }
    inline CGPoint getEmissionRGB() { return CGPoint(_emission[0], _emission[1], _emission[2]); }

    inline void setEmissionRed(float v)   { _emission[0] = v; }
    inline void setEmissionGreen(float v) { _emission[1] = v; }
    inline void setEmissionBlue(float v)  { _emission[2] = v; }
    inline void setEmissionAlpha(float v) { _emission[3] = v; }

    inline void setEmissionRGB(float r, float g, float b)
    {
        _emission[0] = r;
        _emission[1] = g;
        _emission[2] = b;
    }

    inline void setEmissionRGB(CGPoint &p)
    {
        _emission[0] = p[0];
        _emission[1] = p[1];
        _emission[2] = p[2];
    }

    inline void setEmissionRGBA(float r, float g, float b, float a)
    {
        _emission[0] = r;
        _emission[1] = g;
        _emission[2] = b;
        _emission[3] = a;
    }

    inline void setEmissionWhite(float v)
    {
        _emission[0] = v;
        _emission[1] = v;
        _emission[2] = v;
    }

    //----------- SHININESS -----------//
    inline float getShininess() { return _shininess[0]; }
    inline void setShininess(float v) { _shininess[0] = v * 128.0f; }
            
    //----------- RESET -----------//
    inline void Reset()
    {
        setMaterial(DEFAULT);
    }

protected:
    static const float PRESET[][17];
    static const int n_PRESET = 20;

    float _ambient[4];
    float _diffuse[4];
    float _specular[4];
    float _emission[4];
    float _shininess[1];
};

#endif // GLMaterial_H
