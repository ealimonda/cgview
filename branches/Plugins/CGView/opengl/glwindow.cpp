/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glwindow.cpp                                                     *
 * Description: OpenGL window for CGView                                      *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/

#include "glwindow.h"

#include <QtOpenGL> // QGLWidget
#include "pluginmanager.h" // PluginManager
#include "interfaces.h" // PluginTransformInterface
QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

/**
 * Costruttore
 */
GLWindow::GLWindow(QWidget *parent) : QGLWidget(parent)
{
	this->_loaded = false;

	this->_camera = GLCamera();
	this->_camera.setAspect((float)this->width() / (float)this->height());

	this->_mouseSens = 0.5f;
	connect(PluginManager::sharedInstance(), SIGNAL(renderPluginToggled()), this, SLOT(updateGL()));
	connect(PluginManager::sharedInstance(), SIGNAL(visualizationPluginToggled()), this, SLOT(updateWindow()));
}

void GLWindow::runTransformPlugin(PluginTransformInterface *plugin)
{
	for (unsigned int i = 0; i < this->_mesh.size(); ++i)
	{
		plugin->runTransform( this->_mesh[i].mesh() );
	}
	this->updateWindow();
}

void GLWindow::addMesh(CGMesh* m)
{
	// If there is already a mesh, reset
	if (this->_loaded)
	{
		this->reset();
	}
	this->_loaded = true;

	this->_mesh.push_back(GLMesh(m));
	this->_box.Add(m->bbox);

	// Set the scene camera
	this->_camera.fitWidth(this->_box.Diag());
	this->_camera.setClipNear(0.01f);
	this->_camera.setClipFar(this->_box.Diag() * 1000);

	this->updateWindow();
	this->updateWindow();
}

/**
 * Inizializza i parametri che non cambieranno durante la visualizzazione delle
 * mesh
 */
void GLWindow::initializeGL(void)
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

/** Reset the GLWindows **/
void GLWindow::reset(void)
{
	this->_loaded = false;

	this->_camera.reset();
	this->_camera.setAspect((float)this->width() / (float)this->height());

	for( unsigned int i = 0; i < this->_mesh.size(); ++i ) {
		this->_mesh[i].~GLMesh();
	}
	this->_mesh.clear();
	this->_box.SetNull();

	this->updateGL();
}

/**
 * Disegna fisicamente la scena
 */
void GLWindow::paintGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!this->_loaded)
	{
		// Si può inserire qui il CGView cube
		return;
	}
	std::vector<PluginRenderInterface *> renderPlugins = PluginManager::sharedInstance()->renderPlugins();
	for (unsigned int i = 0; i < renderPlugins.size(); ++i)
	{
		if (renderPlugins[i]->isEnabled())
		{
			renderPlugins[i]->doRender(this->_mesh, this);
			return;
		}
	}

	drawGradient();
	this->_camera.camProjection();
	this->_camera.camPosition(GLCamera::kEyePositionCenter);
	glPushMatrix();

	for (unsigned int i = 0; i < this->_mesh.size(); ++i)
	{
		this->_mesh[i].drawMesh();
	}
	glPopMatrix();
}

/**
 * Gestisce il ridimensionamento della viewport
 */
void GLWindow::resizeGL(int width, int height)
{
	this->_camera.setAspect((float)width / (float)height);
	glViewport(0, 0, width, height);
	this->_camera.camProjection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	this->updateGL();
}

/**
 * Keyboard listener
 */
void GLWindow::keyPressEvent(QKeyEvent *event)
{
	if (!this->_loaded)
		return;

	switch (event->key())
	{
	case Qt::Key_Up:
	  {
		this->_camera.liftCam(0.2f * this->_box.Diag());
	  }
		break;
	case Qt::Key_Down:
	  {
		this->_camera.liftCam(-0.2f * this->_box.Diag());
	  }
		break;
	case Qt::Key_Left:
	  {
		this->_camera.strafeCam(0.2f * this->_box.Diag());
	  }
		break;
	case Qt::Key_Right:
	  {
		this->_camera.strafeCam(-0.2f * this->_box.Diag());
	  }
		break;
	case Qt::Key_Z:
	  {
		this->_camera.changeDistance(0.2f * this->_box.Diag());
	  }
		break;
	case Qt::Key_X:
	  {
		this->_camera.changeDistance(-0.2f * this->_box.Diag());
	  }
		break;
	case Qt::Key_C:
	  {
		this->_camera.fitWidth(this->_box.Diag());
	  }
		break;
	default:
		break;
	}
	this->updateGL();
}

/**
 * Mouse listener
 */
void GLWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::MidButton)
	{
		this->_camera.fitWidth(this->_box.Diag());
		this->updateGL();
	}
	else
	{
		this->_lastPos = event->pos();
	}
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (!this->_loaded)
		return;

	int dx = event->x() - this->_lastPos.x();
	int dy = event->y() - this->_lastPos.y();

	if (event->modifiers() & Qt::ShiftModifier)
	{
		this->_camera.rotateVR(vcg::math::ToRad((float)-dy * this->_mouseSens));
	}
	else if (event->modifiers() & Qt::ControlModifier)
	{
		this->_camera.changeDistance(vcg::math::ToRad((float)-dy * this->_mouseSens * this->_box.Diag()));
	}
	else if (event->modifiers() & Qt::AltModifier)
	{
		this->_camera.rotateVUp(vcg::math::ToRad((float)-dx * this->_mouseSens));
	}
	else if (event->modifiers() & Qt::MetaModifier)
	{
		this->_camera.rotateDir(vcg::math::ToRad((float)dx * this->_mouseSens));
	}
	else if (event->buttons() & Qt::LeftButton)
	{
		this->_camera.rotateVR(vcg::math::ToRad((float)-dy * this->_mouseSens));
		this->_camera.rotateVUp(vcg::math::ToRad((float)-dx * this->_mouseSens));
	}
	else if (event->buttons() & Qt::RightButton)
	{
		this->_camera.rotateVR(vcg::math::ToRad((float)-dy * this->_mouseSens));
		this->_camera.rotateDir(vcg::math::ToRad((float)dx * this->_mouseSens));
	}
	else
		return;

	this->_lastPos = event->pos();
	this->updateGL();
}

void GLWindow::wheelEvent(QWheelEvent *event)
{
	if (!this->_loaded)
		return;

	float rot = event->delta() / 8;
	this->_camera.changeDistance(vcg::math::ToRad(rot * this->_mouseSens * this->_box.Diag()));
	//this->_lastPos = event->pos();
	this->updateGL();
}

/**
 * Disegna il gradiente come un quadrato colorato
 */
void GLWindow::drawGradient(void)
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

