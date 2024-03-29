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
#include "prefcontroller.h" // PrefController
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
	this->_loaded = true;

	this->_mesh.push_back(GLMesh(m));
	this->_box.Add(m->bbox);

	// Set the scene camera
	this->_camera.fitWidth(this->_box.Diag());
	this->_camera.setClipNear(0.01f);
	this->_camera.setClipFar(this->_box.Diag() * 1000);

	this->updateWindow();
	this->updateWindow();

	_meshlist.push_back(m);

	//This can be revised in order to move those instruction to a different part of the code
	QString name(m->getName().data());
	//create item for the menus
	MeshListItem *item = new MeshListItem(name, _mesh, _mesh.size()-1);
	//connect the item to the window for updating view
	connect(item, SIGNAL(updateMesh()), this, SLOT(updateGL()));
	//send information
	emit sendMeshInfo(item);
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
 * Mouse listener
 */
void GLWindow::mousePressEvent(QMouseEvent *event)
{
	if (!InputEvents::DispatchEvent((QEvent *)event))
		event->accept();
	else
		event->ignore();
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (!InputEvents::DispatchEvent((QEvent *)event))
		event->accept();
	else
		event->ignore();
}

void GLWindow::wheelEvent(QWheelEvent *event)
{
	if (!InputEvents::DispatchEvent((QEvent *)event))
		event->accept();
	else
		event->ignore();
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
	glColor4fv(PrefController::sharedInstance()->gradientColors(0));
	glVertex2f(-1.0f, 1.0f);
	glColor4fv(PrefController::sharedInstance()->gradientColors(1));
	glVertex2f(-1.0f, -1.0f);
	glColor4fv(PrefController::sharedInstance()->gradientColors(2));
	glVertex2f(1.0f, 1.0f);
	glColor4fv(PrefController::sharedInstance()->gradientColors(3));
	glVertex2f(1.0f, -1.0f);
	glEnd();

	glPopAttrib();
	glPopMatrix(); // restore modelview
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void GLWindow::uiInputEvent(InputEvents::EventType type,float value)
{
	if (!this->_loaded)
		return;

	switch (type)
	{
	case InputEvents::kLiftCam:
	  {
		this->_camera.liftCam(value * this->_box.Diag());
	  }
		break;
	case InputEvents::kStrafeCam:
	  {
		this->_camera.strafeCam(value * this->_box.Diag());
	  }
		break;
	case InputEvents::kDistanceCam:
	  {
		this->_camera.changeDistance(value * this->_box.Diag());
	  }
		break;
	case InputEvents::kFitCam:
	  {
		this->_camera.fitWidth(this->_box.Diag());
	  }
		break;
	case InputEvents::kRotateVRCam:
	  {
		this->_camera.rotateVR(value);
		break;
	  }
	case InputEvents::kRotateVUpCam:
	  {
		this->_camera.rotateVUp(value);
		break;
	  }
	case InputEvents::kRotateDirCam:
	  {
		this->_camera.rotateDir(value);
		break;
	  }
	case InputEvents::kEventNoop:
		break;
	}
	this->updateGL();
}

void GLWindow::getSnapshot() {
	updateGL();

    QImage snapshot( this->width(), this->height(), QImage::Format_RGB32);
    snapshot.fill(0);

	int w = snapshot.width();
	int h = snapshot.height();

    //read data from framebuffer
    uchar* red = (uchar*) calloc (snapshot.width() * snapshot.height(), sizeof(uchar));
    uchar* green = (uchar*) calloc (snapshot.width() * snapshot.height(), sizeof(uchar));
    uchar* blue = (uchar*) calloc (snapshot.width() * snapshot.height(), sizeof(uchar));
    glReadPixels( (GLint) 0, (GLint) 0, (GLint) snapshot.width(), (GLint) snapshot.height(), GL_RED, GL_UNSIGNED_BYTE, red );
    glReadPixels( (GLint) 0, (GLint) 0, (GLint) snapshot.width(), (GLint) snapshot.height(), GL_GREEN, GL_UNSIGNED_BYTE, green );
    glReadPixels( (GLint) 0, (GLint) 0, (GLint) snapshot.width(), (GLint) snapshot.height(), GL_BLUE, GL_UNSIGNED_BYTE, blue );

    //save data in QImage
    for(int x = 0; x < snapshot.width(); x++)   {      //col
       for(int y = 0; y < snapshot.height(); y++)  {   //row
           //save image
           snapshot.setPixel(x, snapshot.height()-y-1, qRgb(red[y*snapshot.width()+x], green[y*snapshot.width()+x], blue[y*snapshot.width()+x]));
       }
    }

    //save QImage on disk
    QString filename = QFileDialog::getSaveFileName( NULL, "Save shapshot", "", "Image files (*.png *.jpg *.bmp);;png (*.png);;jpg (*.jpg);;bmp (*.bmp)");
    if ( !filename.isNull() ) snapshot.save(filename);
}