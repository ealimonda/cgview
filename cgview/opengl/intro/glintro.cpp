#include <QtGui>
#include <QtOpenGL/QtOpenGL>

//#include <math.h>

#include "glintro.h"

GLIntro::GLIntro(QWidget *parent) : QGLWidget(parent)
{
    _cube = 0;

    _dx = 0;
    _dy = 100;
    _border = 2.0f;
    _inertia = INERTIA;

    _camera = GLCamera();
    _camera.Reset();
    _camera.setAspect(this->width() / this->height());
    _camera.setClipFar(5000);
    _camera.setClipNear(0.1);
    _camera.setObserverXYZ(0,0,-60);
    _camera.rotateDir(vcg::math::ToRad(180.0f));

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(Inertia()));
    _timer->start(20);
}

GLIntro::~GLIntro()
{
    makeCurrent();
    glDeleteLists(_cube, 1);

    stopCube();
}

void GLIntro::initializeGL()
{
    static const GLfloat lightPos[4] = { 5.0f, 5.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    _cube = makeCube();

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void GLIntro::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _camera.camProjection();
    _camera.camPosition(GLCamera::EYE_CENTER);

    glPushMatrix();

    drawCube(_cube);

    glPopMatrix();
}

void GLIntro::resizeGL(int width, int height)
{
    _camera.setAspect((float)width / (float)height);

    glViewport(0, 0, width, height);

    _camera.camProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    updateGL();

}

void GLIntro::mousePressEvent(QMouseEvent *event)
{
    _lastPos = event->pos();
}

void GLIntro::mouseMoveEvent(QMouseEvent *event)
{
    _dx = event->x() - _lastPos.x();
    _dy = event->y() - _lastPos.y();
    

    if (event->buttons() & Qt::LeftButton)
    {
        _camera.rotateVUp(vcg::math::ToRad((float)-_dx * _mouseSens));
        _camera.rotateVR(vcg::math::ToRad((float)_dy * _mouseSens));
    }
    _lastPos = event->pos();
}

/*GLuint GLIntro::makeCube()
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
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
}*/

GLuint GLIntro::makeCube()
{
//    short cgview[DIMY][DIMX] =
//    {
//        {1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//        {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1},
//        {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1},
//        {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1},
//        {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
//        {1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,0},
//    };
    short cgview[DIMY][DIMX] =
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
    float _startx = 0.0f - ((DIMX * _side) / 2.0f);
    float _starty = 0.0f - ((DIMY * _side) / 2.0f);
    float _startz = 0.0f - ((DIMZ * _side) / 2.0f);

    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    for(int i = (DIMX - 1); i > -1; i--)
    {
        for(int j = (DIMY - 1); j > -1; j--)
        {
            if(cgview[j][i])
            {
                float side = _side - _border;

                float px = _startx + (_side * i) + _border;
                float py = _starty + (_side * j) + _border;


                for(int k = 0; k < DIMZ; k++)
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

void GLIntro::Inertia()
{
    if(_dx > 0)
    {
        if((_dx - _inertia) > 0)
        {
            _dx = _dx - _inertia;
        }
        else _dx = 0;
    }
    else
    {
        if(_dx < 0)
        {
            if((_dx + _inertia) < 0)
            {
                _dx = _dx + _inertia;
            }
            else _dx = 0;
        }
        else
        {
            _dx = 0;
        }
    }

    if(_dy > 0)
    {
        if((_dy - _inertia) > 0)
        {
            _dy = _dy - _inertia;
        }
        else _dy = 0;
    }
    else
    {
        if(_dy < 0)
        {
            if((_dy + _inertia) < 0)
            {
                _dy = _dy + _inertia;
            }
            else _dy = 0;
        }
        else
        {
            _dy = 0;
        }
    }

    if((_dx == 0) && (_dy == 0))
    {
        _inertia = INERTIA;
    }
    else
    {
        _inertia += _inertia * 8 / 1000;
    }

    _camera.rotateVUp(vcg::math::ToRad((float)-_dx * _mouseSens));
    _camera.rotateVR(vcg::math::ToRad((float)_dy * _mouseSens));

    if(_border > 0.0f)
    {
        _border -= 0.01f;
        remakeCube();
    }

    updateGL();
}

