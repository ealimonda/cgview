TEMPLATE = app

CONFIG += \
          opengl \
          thread \
          debug

QT += opengl

INCLUDEPATH += . \
               ../../lib/vcglib

HEADERS = \
          opengl/glwindow.h \
          opengl/scene/camera/glcamera.h \
          opengl/scene/light/gllight.h \
          mainwindow.h \
          engine.h \
          mesh_definition.h \
          opengl/mesh/mode/visualmode.h \
          opengl/mesh/material/glmaterial.h \
          opengl/intro/glintro.h \
          opengl/scene/scene.h \
          opengl/mesh/glmesh.h \
          convex_hull/my_convhull.h \
          statusbar.h

SOURCES = \
          opengl/glwindow.cpp \
          opengl/scene/camera/glcamera.cpp \
          opengl/scene/light/gllight.cpp \
          opengl/intro/glintro.cpp \
          main.cpp \
          mainwindow.cpp \
          engine.cpp \
          opengl/mesh/material/glmaterial.cpp \
          opengl/mesh/glmesh.cpp \
          statusbar.cpp \
          convex_hull/my_convhull.cpp \
          ../../lib/vcglib/wrap/ply/plylib.cpp
