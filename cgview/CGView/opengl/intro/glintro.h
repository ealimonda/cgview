/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glintro.h                                                        *
 * Description: Fancy CGView intro screen                                     *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_OPENGL_INTRO_GLINTRO_H
#define CGVIEW_OPENGL_INTRO_GLINTRO_H

#include <QtOpenGL> // QGLWidget
#include "opengl/scene/scene.h" // GLCamera

class GLIntro : public QGLWidget
{
	Q_OBJECT

public:
	GLIntro(QWidget *parent = 0, bool start = true);
	~GLIntro();

public slots:
	inline void stopCube(void) { this->_timer->stop(); }
	inline void startCube(void) { this->_timer->start(20); }

private:
	float kMouseSensibility;
	float kInertia;

	static const unsigned int kDimensionX = 55;
	static const unsigned int kDimensionY = 6;
	static const unsigned int kDimensionZ = 3;

	inline void remakeCube(void)
	{
		glDeleteLists(this->_cube, 1);
		this->_cube = 0;
		this->_cube = this->makeCube();
	}

	void initializeGL(void);
	void paintGL(void);
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	GLuint makeCube(void);
	void drawCube(GLuint gear);
	void normalizeAngle(int *angle);

	GLuint _cube;
	float _dx, _dy;
	float _border;
	float _inertia;
	GLCamera _camera;
	QPoint _lastPos;
	QTimer *_timer;

private slots:
	void inertia(void);
};

#endif // CGVIEW_OPENGL_INTRO_GLINTRO_H
