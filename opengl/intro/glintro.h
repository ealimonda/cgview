#ifndef GLINTRO_H
#define GLINTRO_H

#include <QtOpenGL/QGLWidget>
#include "opengl/scene/scene.h"

class GLIntro : public QGLWidget
{
    Q_OBJECT

public:
    GLIntro(QWidget *parent = 0);
    ~GLIntro();

private:

protected:
    inline void remakeCube()
    {
        glDeleteLists(_cube, 1);
        _cube = 0;
        _cube = makeCube();
    }

    static const float _mouseSens = 0.2f;
    static const float INERTIA = 0.2f;

    static const unsigned int DIMX = 55;
    static const unsigned int DIMY = 6;
    static const unsigned int DIMZ = 3;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    GLuint makeCube();
    void drawCube(GLuint gear);
    void normalizeAngle(int *angle);

    GLuint _cube;
    float _dx, _dy;
    float _border;
    float _inertia;
    GLCamera _camera;
    QPoint _lastPos;
    QTimer *_timer;

signals:

public slots:
    inline void stopCube() { _timer->stop(); }

private slots:
    void Inertia();
};

#endif
