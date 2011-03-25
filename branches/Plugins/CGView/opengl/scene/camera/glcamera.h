/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glcamera.h                                                       *
 * Description: OpenGL Camera                                                 *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_OPENGL_SCENE_CAMERA_GLCAMERA_H
#define CGVIEW_OPENGL_SCENE_CAMERA_GLCAMERA_H

/**
 * La classe GLCamera è ancora in fase di costruzione
 *
 * La classe definisce un oggetto GLCamera che altro non è che
 * il metodo di proiezione all'interno di OpenGL.
 * Serve per snellire il codice, e poter gestire meglio e in maniera
 * più semplice la visuale della scena.
 *
 * Per ora fa solo la vista in prospettiva, ma con qualche modifica è possibile avere tutte le viste
 *
 * Le rotazioni sono solo attorno all'origine. Si potrebbe cambiare e farle anche attorno al centro
 * oppure attorno a un punto qualsiasi.
 */

#include <QtOpenGL>
#include "mesh_definition.h"

class GLCamera
{
public:
	enum EyePosition
	{
		kEyePositionCenter,
		kEyePositionLeft,
		kEyePositionRight,
	};

	GLCamera();
	explicit GLCamera(float width);

	/// Esegue il codice OpenGL per la proiezione
	void camProjection(void);
	/// Esegue il codice OpenGL per la camera
	void camPosition(EyePosition e);

	/** CENTER */
	inline float getCenterX(void) const { return this->_center[kCoordX]; }
	inline float getCenterY(void) const { return this->_center[kCoordY]; }
	inline float getCenterZ(void) const { return this->_center[kCoordZ]; }
	inline CGPoint getCenter(void) const { return this->_center; }

	inline void setCenterX(float x) { this->_center[kCoordX] = x; this->computeDistance(); }
	inline void setCenterY(float y) { this->_center[kCoordY] = y; this->computeDistance(); }
	inline void setCenterZ(float z) { this->_center[kCoordZ] = z; this->computeDistance(); }
	inline void setCenter(CGPoint p) { this->_center = p; this->computeDistance();  }
	inline void setCenterXYZ(float x, float y, float z)
	{
		this->_center[kCoordX] = x;
		this->_center[kCoordY] = y;
		this->_center[kCoordZ] = z;
		this->computeDistance();
		this->computeDirection();
	}

	/** OBSERVER */
	inline float getObserverX(void) const { return this->_eye[kCoordX]; }
	inline float getObserverY(void) const { return this->_eye[kCoordY]; }
	inline float getObserverZ(void) const { return this->_eye[kCoordZ]; }
	inline CGPoint getObserver(void) const { return this->_eye; }

	inline void setObserverX(float x) { this->_eye[kCoordX] = x; this->computeDistance(); }
	inline void setObserverY(float y) { this->_eye[kCoordY] = y; this->computeDistance(); }
	inline void setObserverZ(float z) { this->_eye[kCoordZ] = z; this->computeDistance(); }
	inline void setObserver(CGPoint p) { this->_eye = p; this->computeDistance(); }
	inline void setObserverXYZ(float x, float y, float z)
	{
		this->_eye[kCoordX] = x;
		this->_eye[kCoordY] = y;
		this->_eye[kCoordZ] = z;
		this->computeDistance();
		this->computeDirection();
	}

	/** DIRECTION */
	inline float getDirectionX(void) const { return this->_eye[kCoordX]; }
	inline float getDirectionY(void) const { return this->_eye[kCoordY]; }
	inline float getDirectionZ(void) const { return this->_eye[kCoordZ]; }
	inline CGPoint getDirection(void) const { return this->_eye; }

	inline void setDirectionX(float x) { this->_dir[kCoordX] = x; }
	inline void setDirectionY(float y) { this->_dir[kCoordY] = y; }
	inline void setDirectionZ(float z) { this->_dir[kCoordZ] = z; }
	inline void setDirection(CGPoint p) { this->_dir = p; }
	inline void setDirectionXYZ(float x, float y, float z)
	{
		this->_dir[kCoordX] = x;
		this->_dir[kCoordY] = y;
		this->_dir[kCoordZ] = z;
	}

	inline void computeDirection(void) { this->_dir = this->_eye - this->_center; this->_dir.Normalize(); }

	/** VUP */
	inline float getVUpX(void) const { return this->_vup[kCoordX]; }
	inline float getVUpY(void) const { return this->_vup[kCoordY]; }
	inline float getVUpZ(void) const { return this->_vup[kCoordZ]; }
	inline CGPoint getVUp(void) const { return this->_vup; }

	inline void setVUpX(float x) { this->_vup[kCoordX] = x; }
	inline void setVUpY(float y) { this->_vup[kCoordY] = y; }
	inline void setVUpZ(float z) { this->_vup[kCoordZ] = z; }
	inline void setVUp(CGPoint p) { this->_vup = p; }
	inline void setVUpXYZ(float x, float y, float z)
	{
		this->_vup[kCoordX] = x;
		this->_vup[kCoordY] = y;
		this->_vup[kCoordZ] = z;
	}

	/** VR */
	inline float getVRX(void) const { return this->_vr[kCoordX]; }
	inline float getVRY(void) const { return this->_vr[kCoordY]; }
	inline float getVRZ(void) const { return this->_vr[kCoordZ]; }
	inline CGPoint getVR(void) const { return this->_vr; }

	inline void setVRX(float x) { this->_vr[kCoordX] = x; }
	inline void setVRY(float y) { this->_vr[kCoordY] = y; }
	inline void setVRZ(float z) { this->_vr[kCoordZ] = z; }
	inline void setVR(CGPoint p) { this->_vr = p; }
	inline void setVRXYZ(float x, float y, float z)
	{
		this->_vr[kCoordX] = x;
		this->_vr[kCoordY] = y;
		this->_vr[kCoordZ] = z;
	}

	/** FOV */
	inline float getFOV(void) const { return this->_fov; }
	inline void setFOV(float alpha) { this->_fov = alpha; }

	/** ASPECT */
	inline float getAspect(void) const { return this->_aspect; }
	inline void setAspect(float ratio) { this->_aspect = ratio; }

	/** Z NEAR */
	inline float getClipNear(void) const { return this->_zNear; }
	inline void setClipNear(float v) { if (v >= 0.0f) this->_zNear = v; }

	/** Z FAR **/
	inline float getClipFar(void) const { return this->_zFar; }
	inline void setClipFar(float v) { if (v >= 0.0f) this->_zFar = v; }

	/** DISTANCE **/
	inline float getDistance(void) const { return this->_distance; }
	inline void computeDistance(void)
	{
		this->_distance = vcg::Distance(this->_eye, this->_center);
		this->_dir = this->_eye - this->_center;
		this->_dir.Normalize();
	}

	/** ## TRASFORMATIONS ## */

	/** TRANSLATIONS */
	void changeDistance(float d);
	void strafeCam(float d);
	void liftCam(float d);
	void fitWidth(float d);

	/** ROTATIONS */
	void rotateVUp(float angle);
	void rotateVR(float angle);
	void rotateDir(float angle);

	/** RESET */
	void reset(void);

private:
	CGPoint _center;
	CGPoint _eye;
	CGPoint _vup;
	CGPoint _vr;
	CGPoint _dir;
	float _distance;

	float _fov;
	float _aspect;
	float _zNear;
	float _zFar;
};

#endif // CGVIEW_OPENGL_SCENE_CAMERA_GLCAMERA_H
