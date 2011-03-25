#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtGui>
#include <QtOpenGL/QtOpenGL>
#include "opengl/intro/glintro.h"
#include "opengl/glwindow.h"
#include "statusbar.h"
#include "sidebar.h"
#include "engine.h"
#include "mesh_handler.h"

#include "subwindows/psi_dialog.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QScrollArea;
class QGridLayout;
QT_END_NAMESPACE
class GLIntro;
class GLWindow;
class StatusBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:

protected:
    //Type of area in the main window
    enum AreaType
    {
        INTRO,
        VIEWER,
        STATUS,
        PALETTE,
        SIDEBAR,

        /// Number of areas --- THIS MUST BE THE LAST ELEMENT
        AREA_NUM
    };
    //Number of area in the main window
    static const int _AreaDim = AREA_NUM;

    // Types of subwindows
    enum DialogType
    {
        PSI,

        /// Number of subwindows -- THIS MUST BE THE LAST
        DIALOG_NUM
    };
    //Number of subwindows
    static const int _DialogDim = DIALOG_NUM;

    //Type of menu in the main menu
    enum MenuType
    {
        /// Menu
        MENU_FILE,
        MENU_EDIT,
        MENU_VIEW,
        MENU_TOOL,
        MENU_WINDOW,
        MENU_HELP,

        /// File submenu
        MENU_FILE_NEW,

        /// Edit submenu
        MENU_EDIT_NORMAL,
        MENU_EDIT_QUALITY,
        MENU_EDIT_COLOR,
        MENU_EDIT_BOX,

        /// View submenu
        MENU_VIEW_BOX,
        MENU_VIEW_MESH,
        MENU_VIEW_COLOR,
        MENU_VIEW_NORMAL,
        MENU_VIEW_MISC,

        /// Tool submenu
        MENU_TOOL_CHAOS,
        MENU_TOOL_VOXEL,

        /// Window submenu
        MENU_WINDOW_BAR,

        /// Number of menus --- THIS MUST BE THE LAST ELEMENT
        MENU_NUM
    };
    //Number of menu and submenu
    static const int _MenuDim = MENU_NUM;

    //Type of action in the main menu
    enum ActionType
    {
        /// File actions
        ACTION_FILE_NEW_CLOUD,
        ACTION_FILE_OPEN,
        ACTION_FILE_SAVEAS,
        ACTION_FILE_SAVE,
        ACTION_FILE_CLOSE,
        ACTION_FILE_RESET,
        ACTION_FILE_EXIT,
        ACTION_FILE_ADD,

        /// Edit actions
        ACTION_EDIT_UPDATE_VERT_NORMAL,
        ACTION_EDIT_UPDATE_FACE_NORMAL,
        ACTION_EDIT_UPDATE_ALL_NORMAL,
        ACTION_EDIT_INVERT_VERT_NORMAL,
        ACTION_EDIT_INVERT_FACE_NORMAL,
        ACTION_EDIT_INVERT_ALL_NORMAL,
        ACTION_EDIT_RESET_QUALITY,
        ACTION_EDIT_RANDOM_VERT_QUALITY,
        ACTION_EDIT_RANDOM_FACE_QUALITY,
        ACTION_EDIT_TRANSFER_QUALITY_VERTTOFACE,
        ACTION_EDIT_TRANSFER_QUALITY_FACETOVERT,
        ACTION_EDIT_RANDOM_VERT_COLOR,
        ACTION_EDIT_RANDOM_FACE_COLOR,
        ACTION_EDIT_TRANSFER_COLOR_VERTTOFACE,
        ACTION_EDIT_TRANSFER_COLOR_FACETOVERT,
        ACTION_EDIT_UPDATE_BOX,

        /// View actions
        ACTION_VIEW_BOX_DISABLE,
        ACTION_VIEW_BOX_WIRED,
        ACTION_VIEW_BOX_TRANS,
        ACTION_VIEW_BOX_SOLID,
        ACTION_VIEW_MESH_DISABLE,
        ACTION_VIEW_MESH_POINT,
        ACTION_VIEW_MESH_FLAT,
        ACTION_VIEW_MESH_SMOOTH,
        ACTION_VIEW_MESH_VOXEL,
        ACTION_VIEW_COLOR_DISABLE,
        ACTION_VIEW_COLOR_VERTEX,
        ACTION_VIEW_COLOR_FACE,
        ACTION_VIEW_COLOR_TEXTURE,
        ACTION_VIEW_COLOR_VERT_QUALITY,
        ACTION_VIEW_COLOR_FACE_QUALITY,
        ACTION_VIEW_COLOR_MATERIAL,
        ACTION_VIEW_NORMAL_DISABLE,
        ACTION_VIEW_NORMAL_VERT,
        ACTION_VIEW_NORMAL_FACE,
        ACTION_VIEW_MISC_WIRE,
        ACTION_VIEW_MISC_GRID,
        ACTION_VIEW_MISC_AXIS,
        ACTION_VIEW_ANAGLYPH,

        /// Tool actions
        ACTION_TOOL_CONVEXHULL,
        ACTION_TOOL_VOXEL_DISABLE,
        ACTION_TOOL_VOXEL_EXTERN,
        ACTION_TOOL_VOXEL_ALL,
        /// Tool per l'interpolazione di poisson
        ACTION_TOOL_SHAPE_INTERPOLATION,

        /// Window actions
        ACTION_WINDOW_BAR_STATUS,

        /// About
        ACTION_HELP_ABOUT,

        /// Number of actions --- THIS MUST BE THE LAST ELEMENT
        ACTION_NUM
    };
    //Number of actions
    static const int _ActionDim = ACTION_NUM;

    //Create the main menus
    void createMenus();
    //Create the actions for the menus
    void createActions();
    //Create connections between actions and objects
    void createConnections();

    //Create the intro area
    void createIntro();
    //Create the viewer area
    void createViewer();
    //create the status bar
    void createStatus();
    //create the side bar
    void createSide();


    //Main widget
    QWidget *_mainWidget;
    //Main menu
    QMenu *_menu[_MenuDim];
    //Actions of the menu
    QAction *_action[_ActionDim];

    //Subwindows
    QDialog *_dialog[_DialogDim];


    //Layout of the main window
    QGridLayout *_layout;

    //The areas present in the window
    QScrollArea *_area[_AreaDim];

    /// areas
    GLIntro   *_glIntro;
    GLWindow  *_glWindow;
    StatusBar *_statusBar;
    SideBar   *_sideBar;

    /// Engine
    Engine *_engine;

    /// Gestore delle mesh
    MeshHandler *_handler;

signals:

public slots:

private slots:
    //Enable/Disable the status bar
    void ToggleStatus();

    void endIntro();

    void Normals();

    //create the PSI subwindow
    void PSI_create_interface();
};

#endif // MAINWINDOW_H
