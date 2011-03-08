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


/*
  La classe GLCamera è ancora in fase di costruzione

  La classe definisce un oggetto GLCamera che altro non è che
  il metodo di proiezione all'interno di OpenGL.
  Serve per snellire il codice, e poter gestire meglio e in maniera
  più semplice la visuale della scena.


  Per ora fa solo la vista in prospettiva, ma con qualche modifica è possibile avere tutte le viste

  Le rotazioni sono solo attorno all'origine. Si potrebbe cambiare e farle anche attorno al centro
  oppure attorno a un punto qualsiasi.
*/


#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <QtOpenGL/QtOpenGL>
#include "mesh_definition.h"


class GLCamera
{
    public:

            enum EyePosition { EYE_CENTER, EYE_LEFT, EYE_RIGHT };

            GLCamera();
            GLCamera(float width);

            //Esegue il codice OpenGL per la proiezione
            void camProjection();
            //Esegue il codice OpenGL per la camera
            void camPosition(EyePosition e);
            

            //----------- CENTER -----------//
            inline float getCenterX() { return center[0]; }
            inline float getCenterY() { return center[1]; }
            inline float getCenterZ() { return center[2]; }
            inline CGPoint getCenter() { return center; }

            inline void setCenterX(float x) { center[0] = x; computeDistance(); }
            inline void setCenterY(float y) { center[1] = y; computeDistance(); }
            inline void setCenterZ(float z) { center[2] = z; computeDistance(); }
            inline void setCenter(CGPoint p) { center = p; computeDistance();  }
            inline void setCenterXYZ(float x, float y, float z) { center[0] = x;
                                                                  center[1] = y;
                                                                  center[2] = z;
                                                                  computeDistance();
                                                                  computeDirection(); }

            //----------- OBSERVER -----------//
            inline float getObserverX() { return eye[0]; }
            inline float getObserverY() { return eye[1]; }
            inline float getObserverZ() { return eye[2]; }
            inline CGPoint getObserver() { return eye; }

            inline void setObserverX(float x) { eye[0] = x; computeDistance(); }
            inline void setObserverY(float y) { eye[1] = y; computeDistance(); }
            inline void setObserverZ(float z) { eye[2] = z; computeDistance(); }
            inline void setObserver(CGPoint p) { eye = p; computeDistance();  }
            inline void setObserverXYZ(float x, float y, float z) { eye[0] = x;
                                                                    eye[1] = y;
                                                                    eye[2] = z;
                                                                    computeDistance();
                                                                    computeDirection(); }

            //----------- DIRECTION -----------//
            inline float getDirectionX() { return eye[0]; }
            inline float getDirectionY() { return eye[1]; }
            inline float getDirectionZ() { return eye[2]; }
            inline CGPoint getDirection() { return eye; }

            inline void setDirectionX(float x) { dir[0] = x; }
            inline void setDirectionY(float y) { dir[1] = y; }
            inline void setDirectionZ(float z) { dir[2] = z; }
            inline void setDirection(CGPoint p) { dir = p; }
            inline void setDirectionXYZ(float x, float y, float z) { dir[0] = x;
                                                                     dir[1] = y;
                                                                     dir[2] = z; }

            inline void computeDirection() { dir = eye - center; dir.Normalize(); }

            //----------- VUP -----------//
            inline float getVUpX() { return vup[0]; }
            inline float getVUpY() { return vup[1]; }
            inline float getVUpZ() { return vup[2]; }
            inline CGPoint getVUp() { return vup; }

            inline void setVUpX(float x) { vup[0] = x; }
            inline void setVUpY(float y) { vup[1] = y; }
            inline void setVUpZ(float z) { vup[2] = z; }
            inline void setVUp(CGPoint p) { vup = p; }
            inline void setVUpXYZ(float x, float y, float z) { vup[0] = x;
                                                               vup[1] = y;
                                                               vup[2] = z; }

            //----------- VR -----------//
            inline float getVRX() { return vr[0]; }
            inline float getVRY() { return vr[1]; }
            inline float getVRZ() { return vr[2]; }
            inline CGPoint getVR() { return vr; }

            inline void setVRX(float x) { vr[0] = x; }
            inline void setVRY(float y) { vr[1] = y; }
            inline void setVRZ(float z) { vr[2] = z; }
            inline void setVR(CGPoint p) { vr = p; }
            inline void setVRXYZ(float x, float y, float z) { vr[0] = x;
                                                              vr[1] = y;
                                                              vr[2] = z; }

            //----------- FOV -----------//
            inline float getFOV() { return fov; }
            inline void setFOV(float alpha) { fov = alpha; }

            //----------- ASPECT -----------//
            inline float getAspect() { return aspect; }
            inline void setAspect(float ratio) { aspect = ratio; }

            //----------- Z NEAR -----------//
            inline float getClipNear() { return zNear; }
            inline void setClipNear(float v) { if(v >= 0.0f) zNear = v; }

            //----------- Z FAR -----------//
            inline float getClipFar() { return zFar; }
            inline void setClipFar(float v) { if(v >= 0.0f) zFar = v; }

            //----------- DISTANCE -----------//
            inline float getDistance() { return distance; }
            inline void computeDistance() { distance = vcg::Distance(eye, center);
                                            dir = eye - center;
                                            dir.Normalize(); }


            //########### TRASFORMATIONS ###########//

            //----------- TRANSLATIONS -----------//
            void changeDistance(float d);
            void strafeCam(float d);
            void liftCam(float d);
            void fitWidth(float d);

            //----------- ROTATIONS -----------//
            void rotateVUp(float angle);
            void rotateVR(float angle);
            void rotateDir(float angle);






            //----------- RESET -----------//
            void Reset();

     private:

            CGPoint center;
            CGPoint eye;
            CGPoint vup;
            CGPoint vr;
            CGPoint dir;
            float distance;

            float fov;
            float aspect;
            float zNear;
            float zFar;

};

#endif // GLCAMERA_H
