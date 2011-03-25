#include "glwindow.h"

#include <QtGui>
#include <QtOpenGL/QtOpenGL>

//Costruttore
//Inizializza tutte le variabili.
GLWindow::GLWindow(QWidget *parent) : QGLWidget(parent)
{
    _load = false;
    _anaglyph = false;

    _camera = GLCamera();
    _camera.setAspect((float)this->width() / (float)this->height());

    _mouseSens = 0.5f;
}

//Inizializza i parametri che non cambieranno durante la visualizzazione delle mesh
void GLWindow::initializeGL()
{
    static const GLfloat lightPos[4] = { 2.0f, 2.0f, 2.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//Disegna il gradiente come un quadrato colorato
void GLWindow::drawGradient()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glBegin(GL_TRIANGLE_STRIP);
    glColor4f(0.196f, 0.423f, 0.384f, 1.0f);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glColor4f(0.254f, 0.086f, 0.333f, 1.0f);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);
    glColor4f(0.196f, 0.423f, 0.384f, 1.0f);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glColor4f(0.254f, 0.086f, 0.333f, 1.0f);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();

    glPopAttrib();
    glPopMatrix(); // restore modelview
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

//Disegna fisicamente la scena
void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(_load)
    {
        if(!_anaglyph)
        {
            drawGradient();
            _camera.camProjection();
            _camera.camPosition(GLCamera::EYE_CENTER);

            glPushMatrix();
            for(unsigned int i = 0; i < _mesh.size(); i++)
            {
                _mesh[i].drawMesh();
            }
            glPopMatrix();
        }
        else
        {
            glDrawBuffer(GL_BACK);
            glReadBuffer(GL_BACK);

            glClear(GL_ACCUM_BUFFER_BIT);

            /* Left eye */
            glColorMask(GL_TRUE,GL_FALSE,GL_FALSE,GL_TRUE);
            _camera.camProjection();
            _camera.camPosition(GLCamera::EYE_LEFT);

            for(unsigned int i = 0; i < _mesh.size(); i++)
            {
                _mesh[i].drawMesh();
            }

            glFlush();
            glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

            glAccum(GL_LOAD,1.0); /* Could also use glAccum(GL_ACCUM,1.0); */

            glDrawBuffer(GL_BACK);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /* Right eye */
            glColorMask(GL_FALSE,GL_TRUE,GL_TRUE,GL_TRUE);
            _camera.camProjection();
            _camera.camPosition(GLCamera::EYE_CENTER);

            for(unsigned int i = 0; i < _mesh.size(); i++)
            {
                _mesh[i].drawMesh();
            }

            glFlush();
            glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

            glAccum(GL_ACCUM,1.0);
            glAccum(GL_RETURN,1.0);
        }
    }
    else
    {
        //Si può inserire qui il CGView cube
    }

}

//Gestisce il ridimensionamento della viewport
void GLWindow::resizeGL(int width, int height)
{
    _camera.setAspect((float)width / (float)height);
    glViewport(0, 0, width, height);
    _camera.camProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateGL();
}

//Keyboard listener
void GLWindow::keyPressEvent(QKeyEvent *event)
{
    if(_load)
    {
        switch(event->key())
        {
            case Qt::Key_Up:
            {
                _camera.liftCam(0.2f * _box.Diag());
            }
            break;

            case Qt::Key_Down:
            {
                _camera.liftCam(-0.2f * _box.Diag());
            }
            break;

            case Qt::Key_Left:
            {
                _camera.strafeCam(0.2f * _box.Diag());
            }
            break;

            case Qt::Key_Right:
            {
                _camera.strafeCam(-0.2f * _box.Diag());
            }
            break;

            case Qt::Key_Z:
            {
                _camera.changeDistance(0.2f * _box.Diag());
            }
            break;

            case Qt::Key_X:
            {
                _camera.changeDistance(-0.2f * _box.Diag());
            }
            break;

            case Qt::Key_C:
            {
                _camera.fitWidth(_box.Diag());
            }
            break;

            default: break;
        }

        updateGL();
    }
}

//Mouse listener
void GLWindow::mousePressEvent( QMouseEvent *event )
{
    if( event->buttons() & Qt::MidButton )
    {
        _camera.fitWidth(_box.Diag());
        updateGL();
    }
    else
    {
        _lastPos = event->pos();
    }
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - _lastPos.x();
    int dy = event->y() - _lastPos.y();

    if(_load)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            _camera.rotateVR(vcg::math::ToRad((float)-dy * _mouseSens));
            _camera.rotateVUp(vcg::math::ToRad((float)-dx * _mouseSens));
        }

        if (event->buttons() & Qt::RightButton)
        {
            _camera.rotateVR(vcg::math::ToRad((float)-dy * _mouseSens));
            _camera.rotateDir(vcg::math::ToRad((float)dx * _mouseSens));
        }

        _lastPos = event->pos();

        updateGL();
    }
}

void GLWindow::wheelEvent(QWheelEvent *event)
{
    if(_load)
    {
        float rot = event->delta() / 8;
        _camera.changeDistance(vcg::math::ToRad(rot * _mouseSens * _box.Diag()));
        //_lastPos = event->pos();
        updateGL();
    }
}

//Reset the GLWindows
void GLWindow::Reset()
{
    _load = false;
    _anaglyph = false;

    _camera.Reset();
    _camera.setAspect((float)this->width() / (float)this->height());

    for(unsigned int i = 0; i < _mesh.size(); i++)
    {
        _mesh[i].~GLMesh();
    }
    _mesh.clear();
    _box.SetNull();

    updateGL();
}


void GLWindow::addMesh(CGMesh* m)
{
    //If there is already a mesh, reset
    if(_load)
    {
        Reset();
    }
    _load = true;

    _mesh.push_back(GLMesh(m));
    _box.Add(m->bbox);


    //Set the scene camera
    _camera.fitWidth(_box.Diag());
    _camera.setClipNear(0.01f);
    _camera.setClipFar(_box.Diag() * 1000);

    UpdateWindow();
    UpdateWindow();
}


