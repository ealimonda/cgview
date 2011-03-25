/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glintro.cpp                                                      *
 * Description: Fancy CGView intro screen                                     *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "glintro.h"

#include <QtOpenGL/QtOpenGL> // QGLWidget
QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

GLIntro::GLIntro(QWidget *parent) : QGLWidget(parent)
{
	this->_cube = 0;

	this->_dx = 0;
	this->_dy = 100;
	this->_border = 2.0f;
	this->_inertia = kInertia;

	this->_camera = GLCamera();
	this->_camera.reset();
	this->_camera.setAspect(this->width() / this->height());
	this->_camera.setClipFar(5000);
	this->_camera.setClipNear(0.1);
	this->_camera.setObserverXYZ(0,0,-60);
	this->_camera.rotateDir(vcg::math::ToRad(180.0f));

	this->_timer = new QTimer(this);
	connect(this->_timer, SIGNAL(timeout()), this, SLOT(inertia()));
	this->_timer->start(20);
}

GLIntro::~GLIntro()
{
	this->makeCurrent();
	glDeleteLists(this->_cube, 1);

	this->stopCube();
}

void GLIntro::initializeGL(void)
{
	static const GLfloat lightPos[4] = { 5.0f, 5.0f, 10.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	this->_cube = this->makeCube();

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void GLIntro::paintGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->_camera.camProjection();
	this->_camera.camPosition(GLCamera::kEyePositionCenter);

	glPushMatrix();

	this->drawCube(this->_cube);

	glPopMatrix();
}

void GLIntro::resizeGL(int width, int height)
{
	this->_camera.setAspect((float)width / (float)height);

	glViewport(0, 0, width, height);

	this->_camera.camProjection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	this->updateGL();
}

void GLIntro::mousePressEvent(QMouseEvent *event)
{
	this->_lastPos = event->pos();
}

void GLIntro::mouseMoveEvent(QMouseEvent *event)
{
	this->_dx = event->x() - this->_lastPos.x();
	this->_dy = event->y() - this->_lastPos.y();

	if (event->buttons() & Qt::LeftButton)
	{
		this->_camera.rotateVUp(vcg::math::ToRad((float)-this->_dx * this->kMouseSensibility));
		this->_camera.rotateVR(vcg::math::ToRad((float)this->_dy * this->kMouseSensibility));
	}
	this->_lastPos = event->pos();
}

#if 0
GLuint GLIntro::makeCube(void)
{
	GLuint list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	for (int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			for(int k = 0; k < 3; ++k)
			{
				glColor3f(1, 0, 0);
				glBegin(GL_QUADS);
				glNormal3f( 0.0f, 0.0f, 1.0f);
				glVertex3f(-0.525f + i, -0.525f + j, -0.525f + k); glVertex3f(-1.475f + i, -0.525f + j, -0.525f + k);
				glVertex3f(-1.475f + i, -1.475f + j, -0.525f + k); glVertex3f(-0.525f + i, -1.475f + j, -0.525f + k);
				glEnd();
				glColor3f(1, 0, 0);
				glBegin(GL_QUADS);
				glNormal3f( 0.0f, 0.0f,-1.0f);
				glVertex3f(-1.475f + i, -1.475f + j, -1.475f + k); glVertex3f(-1.475f + i, -0.525f + j, -1.475f + k);
				glVertex3f(-0.525f + i, -0.525f + j, -1.475f + k); glVertex3f(-0.525f + i, -1.475f + j, -1.475f + k);
				glEnd();
				glColor3f(0, 0, 1);
				glBegin(GL_QUADS);
				glNormal3f( 0.0f, 1.0f, 0.0f);
				glVertex3f(-0.525f + i, -0.525f + j, -0.525f + k); glVertex3f(-0.525f + i, -0.525f + j, -1.475f + k);
				glVertex3f(-1.475f + i, -0.525f + j, -1.475f + k); glVertex3f(-1.475f + i, -0.525f + j, -0.525f + k);
				glEnd();
				glColor3f(0, 0, 1);
				glBegin(GL_QUADS);
				glNormal3f( 0.0f,-1.0f, 0.0f);
				glVertex3f(-1.475f + i, -1.475f + j, -1.475f + k); glVertex3f(-0.525f + i, -1.475f + j, -1.475f + k);
				glVertex3f(-0.525f + i, -1.475f + j, -0.525f + k); glVertex3f(-1.475f + i, -1.475f + j, -0.525f + k);
				glEnd();
				glColor3f(0, 1, 0);
				glBegin(GL_QUADS);
				glNormal3f( 1.0f, 0.0f, 0.0f);
				glVertex3f(-0.525f + i, -0.525f + j, -0.525f + k); glVertex3f(-0.525f + i, -1.475f + j, -0.525f + k);
				glVertex3f(-0.525f + i, -1.475f + j, -1.475f + k); glVertex3f(-0.525f + i, -0.525f + j, -1.475f + k);
				glEnd();
				glColor3f(0, 1, 0);
				glBegin(GL_QUADS);
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glVertex3f(-1.475f + i, -1.475f + j, -1.475f + k); glVertex3f(-1.475f + i, -1.475f + j, -0.525f + k);
				glVertex3f(-1.475f + i, -0.525f + j, -0.525f + k); glVertex3f(-1.475f + i, -0.525f + j, -1.475f + k);
				glEnd();
			}
		}
	}

	glEndList();

	return list;
}
#endif // 0

GLuint GLIntro::makeCube(void)
{
	short cgview[kDimensionY][kDimensionX] =
	{
		{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,1,0,0,0,1,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,0},
	};

	float _side = 2.0f;
	//float _border = 0.5f;
	float _startx = 0.0f - ((kDimensionX * _side) / 2.0f);
	float _starty = 0.0f - ((kDimensionY * _side) / 2.0f);
	float _startz = 0.0f - ((kDimensionZ * _side) / 2.0f);

	GLuint list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	for (int i = (kDimensionX - 1); i > -1; --i)
	{
		for (int j = (kDimensionY - 1); j > -1; --j)
		{
			if (!cgview[j][i])
				continue;

			float side = _side - _border;

			float px = _startx + (_side * i) + _border;
			float py = _starty + (_side * j) + _border;

			for (unsigned int k = 0; k < kDimensionZ; ++k)
			{
				float pz = _startz + (_side * k) + _border;

				glColor3f(1, 0, 0);
				glBegin(GL_QUADS);
				glNormal3f( 0.0f, 0.0f, 1.0f);
				glVertex3f(       px,        py, pz + side);
				glVertex3f(       px, py + side, pz + side);
				glVertex3f(px + side, py + side, pz + side);
				glVertex3f(px + side,        py, pz + side);
				glEnd();
				glBegin(GL_QUADS);
				glNormal3f( 0.0f, 0.0f,-1.0f);
				glVertex3f(       px,        py, pz);
				glVertex3f(       px, py + side, pz);
				glVertex3f(px + side, py + side, pz);
				glVertex3f(px + side,        py, pz);
				glEnd();
				glColor3f(0, 0, 1);
				glBegin(GL_QUADS);
				glNormal3f( 0.0f, 1.0f, 0.0f);
				glVertex3f(       px, py + side,        pz);
				glVertex3f(       px, py + side, pz + side);
				glVertex3f(px + side, py + side, pz + side);
				glVertex3f(px + side, py + side,        pz);
				glEnd();
				glBegin(GL_QUADS);
				glNormal3f( 0.0f,-1.0f, 0.0f);
				glVertex3f(       px,    py,        pz);
				glVertex3f(       px,    py, pz + side);
				glVertex3f(px + side,    py, pz + side);
				glVertex3f(px + side,    py,        pz);
				glEnd();
				glColor3f(0, 1, 0);
				glBegin(GL_QUADS);
				glNormal3f( 1.0f, 0.0f, 0.0f);
				glVertex3f(px + side,        py,        pz);
				glVertex3f(px + side,        py, pz + side);
				glVertex3f(px + side, py + side, pz + side);
				glVertex3f(px + side, py + side,        pz);
				glEnd();
				glBegin(GL_QUADS);
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glVertex3f(   px,        py,        pz);
				glVertex3f(   px,        py, pz + side);
				glVertex3f(   px, py + side, pz + side);
				glVertex3f(   px, py + side,        pz);
				glEnd();
			}
		}
	}

	glEndList();

	return list;
}

void GLIntro::drawCube(GLuint list)
{
	glPushMatrix();
	glCallList(list);
	glPopMatrix();
}

void GLIntro::inertia(void)
{
	if (this->_dx > 0 && this->_dx > this->_inertia)
	{
		this->_dx -= this->_inertia;
	}
	else if (this->_dx < 0 && this->_dx < -this->_inertia)
	{
		this->_dx += this->_inertia;
	}
	else
	{
		this->_dx = 0;
	}

	if (this->_dy > 0 && this->_dy > this->_inertia)
	{
		this->_dy -= this->_inertia;
	}
	else if (this->_dy < 0 && this->_dy < -this->_inertia)
	{
		this->_dy += this->_inertia;
	}
	else
	{
		this->_dy = 0;
	}

	if (this->_dx == 0 && this->_dy == 0)
	{
		this->_inertia = kInertia;
	}
	else
	{
		this->_inertia += this->_inertia * 8 / 1000;
	}

	this->_camera.rotateVUp(vcg::math::ToRad((float)-this->_dx * this->kMouseSensibility));
	this->_camera.rotateVR(vcg::math::ToRad((float)this->_dy * this->kMouseSensibility));

	if (this->_border > 0.0f)
	{
		this->_border -= 0.01f;
		this->remakeCube();
	}

	updateGL();
}

