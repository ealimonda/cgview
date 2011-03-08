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


#ifndef GLLIGHT_H
#define GLLIGHT_H

#include <QtOpenGL/QtOpenGL>
#include "mesh_definition.h"


class GLLight
{
    public:

            GLLight();

            void getLight();

            //----------- LIT -----------//
            //inline bool isOn() { return on; }
            //inline void TurnLight(bool b) { on = b; }
            inline void TurnLight(bool b) { if(b) glEnable(GL_LIGHT0); else glEnable(GL_LIGHT0); }

            //----------- AMBIENT -----------//
            inline float getAmbientRed()   { return ambient[0]; }
            inline float getAmbientGreen() { return ambient[1]; }
            inline float getAmbientBlue()  { return ambient[2]; }
            inline float getAmbientAlpha() { return ambient[3]; }
            inline CGPoint getAmbientRGB() { return CGPoint(ambient[0], ambient[1], ambient[2]); }

            inline void setAmbientRed(float v)   { ambient[0] = v; }
            inline void setAmbientGreen(float v) { ambient[1] = v; }
            inline void setAmbientBlue(float v)  { ambient[2] = v; }
            inline void setAmbientAlpha(float v) { ambient[3] = v; }

            inline void setAmbientRGB(float r, float g, float b) { ambient[0] = r;
                                                                   ambient[1] = g;
                                                                   ambient[2] = b; }

            inline void setAmbientRGB(CGPoint p) { ambient[0] = p[0];
                                                   ambient[1] = p[1];
                                                   ambient[2] = p[2]; }

            inline void setAmbientRGBA(float r, float g, float b, float a) { ambient[0] = r;
                                                                             ambient[1] = g;
                                                                             ambient[2] = b;
                                                                             ambient[3] = a; }

            inline void setAmbientWhite(float v) { ambient[0] = v;
                                                   ambient[1] = v;
                                                   ambient[2] = v; }

            //----------- DIFFUSE -----------//
            inline float getDiffuseRed()   { return diffuse[0]; }
            inline float getDiffuseGreen() { return diffuse[1]; }
            inline float getDiffuseBlue()  { return diffuse[2]; }
            inline float getDiffuseAlpha() { return diffuse[3]; }
            inline CGPoint getDiffuseRGB() { return CGPoint(diffuse[0], diffuse[1], diffuse[2]); }

            inline void setDiffuseRed(float v)   { diffuse[0] = v; }
            inline void setDiffuseGreen(float v) { diffuse[1] = v; }
            inline void setDiffuseBlue(float v)  { diffuse[2] = v; }
            inline void setDiffuseAlpha(float v) { diffuse[3] = v; }

            inline void setDiffuseRGB(float r, float g, float b) { diffuse[0] = r;
                                                                   diffuse[1] = g;
                                                                   diffuse[2] = b; }
            inline void setDiffuseRGB(CGPoint p) { diffuse[0] = p[0];
                                                   diffuse[1] = p[1];
                                                   diffuse[2] = p[2]; }

            inline void setDiffuseRGBA(float r, float g, float b, float a) { diffuse[0] = r;
                                                                             diffuse[1] = g;
                                                                             diffuse[2] = b;
                                                                             diffuse[3] = a; }

            inline void setDiffuseWhite(float v) { diffuse[0] = v;
                                                   diffuse[1] = v;
                                                   diffuse[2] = v; }

            //----------- SPECULAR -----------//
            inline float getSpecularRed()   { return specular[0]; }
            inline float getSpecularGreen() { return specular[1]; }
            inline float getSpecularBlue()  { return specular[2]; }
            inline float getSpecularAlpha() { return specular[3]; }
            inline CGPoint getSpecularRGB() { return CGPoint(specular[0], specular[1], specular[2]); }

            inline void setSpecularRed(float v)   { specular[0] = v; }
            inline void setSpecularGreen(float v) { specular[1] = v; }
            inline void setSpecularBlue(float v)  { specular[2] = v; }
            inline void setSpecularAlpha(float v) { specular[3] = v; }

            inline void setSpecularRGB(float r, float g, float b) { specular[0] = r;
                                                                    specular[1] = g;
                                                                    specular[2] = b; }

            inline void setSpecularRGB(CGPoint p) { specular[0] = p[0];
                                                    specular[1] = p[1];
                                                    specular[2] = p[2]; }

            inline void setSpecularRGBA(float r, float g, float b, float a) { specular[0] = r;
                                                                              specular[1] = g;
                                                                              specular[2] = b;
                                                                              specular[3] = a; }

            inline void setSpecularWhite(float v) { specular[0] = v;
                                                    specular[1] = v;
                                                    specular[2] = v; }

            //----------- POSITION -----------//
            inline float getPositionX() { return position[0]; }
            inline float getPositionY() { return position[1]; }
            inline float getPositionZ() { return position[2]; }
            inline float getPositionW() { return position[3]; }
            inline CGPoint getPositionXYZ() { return CGPoint(position[0], position[1], position[2]); }

            inline void setPositionX(float v) { position[0] = v; }
            inline void setPositionY(float v) { position[1] = v; }
            inline void setPositionZ(float v) { position[2] = v; }
            inline void setPositionW(float v) { position[3] = v; }

            inline void setPositionXYZ(CGPoint p) { position[0] = p[0];
                                                    position[1] = p[1];
                                                    position[2] = p[2]; }

            inline void setPositionXYZ(float x, float y, float z) { position[0] = x;
                                                                    position[1] = y;
                                                                    position[2] = z; }

            inline void setPositionXYZW(float x, float y, float z, float w) { position[0] = x;
                                                                              position[1] = y;
                                                                              position[2] = z;
                                                                              position[3] = w; }

            //----------- SPOT DIRECTION -----------//
            inline float getDirectionX() { return direction[0]; }
            inline float getDirectionY() { return direction[1]; }
            inline float getDirectionZ() { return direction[2]; }
            inline CGPoint getDirectionXYZ() { return CGPoint(direction[0], direction[1], direction[2]); }

            inline void setDirectionX(float v) { direction[0] = v; }
            inline void setDirectionY(float v) { direction[1] = v; }
            inline void setDirectionZ(float v) { direction[2] = v; }
            inline void setDirectionXYZ(CGPoint p) { direction[0] = p[0];
                                                     direction[1] = p[1];
                                                     direction[2] = p[2]; }
            inline void setDirectionXYZ(float x, float y, float z) { direction[0] = x;
                                                                     direction[1] = y;
                                                                     direction[2] = z; }

            //----------- SPOT EXPONENT -----------//
            inline float getExponent() { return exponent[0]; }
            inline void setExponent(float v) { exponent[0] = v; }

            //----------- SPOT CUTOFF -----------//
            inline float getCutOff() { return cutoff[0]; }
            inline void setCutOff(float v) { cutoff[0] = v; }

            //----------- CONSTANT ATTENUATION -----------//
            inline float getConstantAttenuation() { return att_const[0]; }
            inline void setConstantAttenuation(float v) { att_const[0] = v; }

            //----------- LINEAR ATTENUATION -----------//
            inline float getLinearAttenuation() { return att_lin[0]; }
            inline void setLinearAttenuation(float v) { att_lin[0] = v; }

            //----------- QUADRATIC ATTENUATION -----------//
            inline float getQuadraticAttenuation() { return att_quad[0]; }
            inline void setQuadraticAttenuation(float v) { att_quad[0] = v; }



            //----------- RESET -----------//
            void reset();

     private:

            bool on;

            float ambient[4];
            float diffuse[4];
            float specular[4];
            float position[4];
            float direction[3];
            float exponent[0];
            float cutoff[0];
            float att_const[0];
            float att_lin[0];
            float att_quad[0];
};

#endif // GLLight_H
