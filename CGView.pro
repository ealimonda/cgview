TEMPLATE = app

CONFIG += \
          opengl \
          thread \
          debug \
console

QT += opengl

INCLUDEPATH += . \
               ../../vcglib

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
          statusbar.h \
    mesh_handler.h \
    subwindows/psi_dialog.h \
    sidebar.h

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
          ../../vcglib/wrap/ply/plylib.cpp \
    mesh_handler.cpp \
    subwindows/psi_dialog.cpp \
    sidebar.cpp
