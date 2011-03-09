#include "mainwindow.h"

#include <QtGui>
#include <QtOpenGL/QtOpenGL>
#include "opengl/intro/glintro.h"
#include "opengl/glwindow.h"
#include "statusbar.h"

MainWindow::MainWindow()
{
    _engine = new Engine(NULL);

    //Setting the title of the main windows
    this->setWindowTitle(QString("CGView - PSI version 0.1 beta"));

    //Setting the minimum height and width and the initial height and width
    //this->setMinimumSize(500, 500);
    this->setWindowState(Qt::WindowMaximized);

    this->setContentsMargins(0, 0, 0, 0);

    //Creating the central widget
    _mainWidget = new QWidget;
    this->setCentralWidget(_mainWidget);

    createIntro();
    createStatus();
    createViewer();

    _area[INTRO]->setVisible(true);
    _area[STATUS]->setVisible(false);
    _area[VIEWER]->setVisible(false);

    //Creating the layout
    _layout = new QGridLayout;
    _layout->setSpacing(0);

    _layout->addWidget(_area[INTRO], 0, 0);
    _layout->addWidget(_area[VIEWER], 1, 0);
    _layout->addWidget(_area[STATUS], 2, 0);

    _mainWidget->setLayout(_layout);

    //Creazione dei menu e delle azioni
    createActions();
    createMenus();

    //Connessioni
    createConnections();
}

//Create the main menus
void MainWindow::createMenus()
{
    /// FILE ----------------------------------------------
    _menu[MENU_FILE] = menuBar()->addMenu(tr("&File"));

    //FILE SUBMENU
    _menu[MENU_FILE_NEW] = new QMenu("&New", this);

    //Adding submenus and action
    _menu[MENU_FILE]->addMenu(_menu[MENU_FILE_NEW]);

    _menu[MENU_FILE_NEW]->addAction(_action[ACTION_FILE_NEW_CLOUD]);
    _menu[MENU_FILE]->addSeparator();
    _menu[MENU_FILE]->addAction(_action[ACTION_FILE_OPEN]);
    _menu[MENU_FILE]->addAction(_action[ACTION_FILE_ADD]);
    _menu[MENU_FILE]->addAction(_action[ACTION_FILE_SAVEAS]);
    _menu[MENU_FILE]->addAction(_action[ACTION_FILE_SAVE]);
    _menu[MENU_FILE]->addAction(_action[ACTION_FILE_CLOSE]);
    _menu[MENU_FILE]->addAction(_action[ACTION_FILE_RESET]);
    _menu[MENU_FILE]->addSeparator();
    _menu[MENU_FILE]->addAction(_action[ACTION_FILE_EXIT]);



    /// EDIT ----------------------------------------------
    /*_menu[MENU_EDIT] = menuBar()->addMenu(tr("&Edit"));

    //EDIT SUBMENU
    _menu[MENU_EDIT_NORMAL]  = new QMenu("&Normals", this);
    _menu[MENU_EDIT_QUALITY] = new QMenu("&Quality", this);
    _menu[MENU_EDIT_COLOR]   = new QMenu("&Colors", this);
    _menu[MENU_EDIT_BOX]     = new QMenu("&Bounding Box", this);

    //Adding submenus and action
    _menu[MENU_EDIT]->addMenu(_menu[MENU_EDIT_NORMAL]);
    _menu[MENU_EDIT]->addMenu(_menu[MENU_EDIT_QUALITY]);
    _menu[MENU_EDIT]->addMenu(_menu[MENU_EDIT_COLOR]);
    _menu[MENU_EDIT]->addMenu(_menu[MENU_EDIT_BOX]);

    _menu[MENU_EDIT_NORMAL]->addAction(_action[ACTION_EDIT_UPDATE_VERT_NORMAL]);
    _menu[MENU_EDIT_NORMAL]->addAction(_action[ACTION_EDIT_UPDATE_FACE_NORMAL]);
    _menu[MENU_EDIT_NORMAL]->addAction(_action[ACTION_EDIT_UPDATE_ALL_NORMAL]);
    _menu[MENU_EDIT_NORMAL]->addAction(_action[ACTION_EDIT_INVERT_VERT_NORMAL]);
    _menu[MENU_EDIT_NORMAL]->addAction(_action[ACTION_EDIT_INVERT_FACE_NORMAL]);
    _menu[MENU_EDIT_NORMAL]->addAction(_action[ACTION_EDIT_INVERT_ALL_NORMAL]);
    _menu[MENU_EDIT_QUALITY]->addAction(_action[ACTION_EDIT_RESET_QUALITY]);
    _menu[MENU_EDIT_QUALITY]->addAction(_action[ACTION_EDIT_RANDOM_VERT_QUALITY]);
    _menu[MENU_EDIT_QUALITY]->addAction(_action[ACTION_EDIT_RANDOM_FACE_QUALITY]);
    _menu[MENU_EDIT_QUALITY]->addAction(_action[ACTION_EDIT_TRANSFER_QUALITY_VERTTOFACE]);
    _menu[MENU_EDIT_QUALITY]->addAction(_action[ACTION_EDIT_TRANSFER_QUALITY_FACETOVERT]);
    _menu[MENU_EDIT_COLOR]->addAction(_action[ACTION_EDIT_RANDOM_VERT_COLOR]);
    _menu[MENU_EDIT_COLOR]->addAction(_action[ACTION_EDIT_RANDOM_FACE_COLOR]);
    _menu[MENU_EDIT_COLOR]->addAction(_action[ACTION_EDIT_TRANSFER_COLOR_VERTTOFACE]);
    _menu[MENU_EDIT_COLOR]->addAction(_action[ACTION_EDIT_TRANSFER_COLOR_FACETOVERT]);
    _menu[MENU_EDIT_BOX]->addAction(_action[ACTION_EDIT_UPDATE_BOX]);*/



    /// VIEW ----------------------------------------------
    _menu[MENU_VIEW] = menuBar()->addMenu(tr("&View"));

    //VIEW SUBMENU
    _menu[MENU_VIEW_BOX]    = new QMenu("&Bounding Box", this);
    _menu[MENU_VIEW_MESH]   = new QMenu("&Mesh", this);
    _menu[MENU_VIEW_COLOR]  = new QMenu("&Colors", this);
    _menu[MENU_VIEW_NORMAL] = new QMenu("&Normals", this);
    _menu[MENU_VIEW_MISC]   = new QMenu("&Miscellaneous", this);

    //Adding submenus and action
    _menu[MENU_VIEW]->addMenu(_menu[MENU_VIEW_BOX]);
    _menu[MENU_VIEW]->addMenu(_menu[MENU_VIEW_MESH]);
    _menu[MENU_VIEW]->addMenu(_menu[MENU_VIEW_COLOR]);
    _menu[MENU_VIEW]->addMenu(_menu[MENU_VIEW_NORMAL]);
    _menu[MENU_VIEW]->addMenu(_menu[MENU_VIEW_MISC]);

    _menu[MENU_VIEW_BOX]->addAction(_action[ACTION_VIEW_BOX_DISABLE]);
    _menu[MENU_VIEW_BOX]->addSeparator();
    _menu[MENU_VIEW_BOX]->addAction(_action[ACTION_VIEW_BOX_WIRED]);
    _menu[MENU_VIEW_BOX]->addAction(_action[ACTION_VIEW_BOX_TRANS]);
    _menu[MENU_VIEW_BOX]->addAction(_action[ACTION_VIEW_BOX_SOLID]);
    _menu[MENU_VIEW_MESH]->addAction(_action[ACTION_VIEW_MESH_DISABLE]);
    _menu[MENU_VIEW_MESH]->addSeparator();
    _menu[MENU_VIEW_MESH]->addAction(_action[ACTION_VIEW_MESH_POINT]);
    _menu[MENU_VIEW_MESH]->addAction(_action[ACTION_VIEW_MESH_FLAT]);
    _menu[MENU_VIEW_MESH]->addAction(_action[ACTION_VIEW_MESH_SMOOTH]);
    _menu[MENU_VIEW_MESH]->addAction(_action[ACTION_VIEW_MESH_VOXEL]);
    _menu[MENU_VIEW_COLOR]->addAction(_action[ACTION_VIEW_COLOR_DISABLE]);
    _menu[MENU_VIEW_COLOR]->addSeparator();
    _menu[MENU_VIEW_COLOR]->addAction(_action[ACTION_VIEW_COLOR_VERTEX]);
    _menu[MENU_VIEW_COLOR]->addAction(_action[ACTION_VIEW_COLOR_FACE]);
    _menu[MENU_VIEW_COLOR]->addAction(_action[ACTION_VIEW_COLOR_TEXTURE]);
    _menu[MENU_VIEW_COLOR]->addSeparator();
    _menu[MENU_VIEW_COLOR]->addAction(_action[ACTION_VIEW_COLOR_VERT_QUALITY]);
    _menu[MENU_VIEW_COLOR]->addAction(_action[ACTION_VIEW_COLOR_FACE_QUALITY]);
    _menu[MENU_VIEW_COLOR]->addSeparator();
    _menu[MENU_VIEW_COLOR]->addAction(_action[ACTION_VIEW_COLOR_MATERIAL]);
    _menu[MENU_VIEW_NORMAL]->addAction(_action[ACTION_VIEW_NORMAL_DISABLE]);
    _menu[MENU_VIEW_NORMAL]->addSeparator();
    _menu[MENU_VIEW_NORMAL]->addAction(_action[ACTION_VIEW_NORMAL_VERT]);
    _menu[MENU_VIEW_NORMAL]->addAction(_action[ACTION_VIEW_NORMAL_FACE]);
    _menu[MENU_VIEW_MISC]->addAction(_action[ACTION_VIEW_MISC_WIRE]);
    _menu[MENU_VIEW_MISC]->addAction(_action[ACTION_VIEW_MISC_GRID]);
    _menu[MENU_VIEW_MISC]->addAction(_action[ACTION_VIEW_MISC_AXIS]);
    _menu[MENU_VIEW]->addSeparator();
    _menu[MENU_VIEW]->addAction(_action[ACTION_VIEW_ANAGLYPH]);



    /// TOOL ----------------------------------------------
    _menu[MENU_TOOL] = menuBar()->addMenu(tr("&Tool"));

    //TOOL SUBMENU
    _menu[MENU_TOOL_CHAOS] = new QMenu("&Chaotic Maps", this);
    //_menu[MENU_TOOL_VOXEL] = new QMenu("&Voxelize", this);

    //Adding submenus and action
    _menu[MENU_TOOL]->addAction(_action[ACTION_TOOL_CONVEXHULL]);

    /*_menu[MENU_TOOL]->addMenu(_menu[MENU_TOOL_VOXEL]);

    _menu[MENU_TOOL_VOXEL]->addAction(_action[ACTION_TOOL_VOXEL_DISABLE]);
    _menu[MENU_TOOL_VOXEL]->addSeparator();
    _menu[MENU_TOOL_VOXEL]->addAction(_action[ACTION_TOOL_VOXEL_EXTERN]);
    _menu[MENU_TOOL_VOXEL]->addAction(_action[ACTION_TOOL_VOXEL_ALL]);*/



    /// WINDOW --------------------------------------------
    _menu[MENU_WINDOW] = menuBar()->addMenu(tr("&Window"));

    //OPTION SUBMENU
    _menu[MENU_WINDOW_BAR] = new QMenu("&Bars", this);

    //Adding submenus and action
    _menu[MENU_WINDOW]->addMenu(_menu[MENU_WINDOW_BAR]);

    _menu[MENU_WINDOW_BAR]->addAction(_action[ACTION_WINDOW_BAR_STATUS]);



    /// HELP ----------------------------------------------
    _menu[MENU_HELP] = menuBar()->addMenu(tr("&About"));

    //ABOUT SUBMENU

    //Adding submenus and action
    _menu[MENU_HELP]->addAction(_action[ACTION_HELP_ABOUT]);
}

//Create the actions for the menus
void MainWindow::createActions()
{
    /// FILE ----------------------------------------------
    _action[ACTION_FILE_OPEN]   = new QAction(tr("Open..."), this);
    _action[ACTION_FILE_ADD]   = new QAction(tr("Add..."), this);
    _action[ACTION_FILE_SAVE]   = new QAction(tr("Save"), this);
    _action[ACTION_FILE_SAVEAS] = new QAction(tr("Save as..."), this);
    _action[ACTION_FILE_CLOSE]  = new QAction(tr("Close"), this);
    _action[ACTION_FILE_RESET]  = new QAction(tr("Reset"), this);
    _action[ACTION_FILE_EXIT]   = new QAction(tr("Exit"), this);

    //FILE SUBMENU
    _action[ACTION_FILE_NEW_CLOUD] = new QAction(tr("Points Cloud"), this);


    /// EDIT ----------------------------------------------

    //EDIT SUBMENU
    /*_action[ACTION_EDIT_UPDATE_VERT_NORMAL]          = new QAction(tr("Update Vertex Normals"), this);
    _action[ACTION_EDIT_UPDATE_FACE_NORMAL]          = new QAction(tr("Update Face Normals"), this);
    _action[ACTION_EDIT_UPDATE_ALL_NORMAL]           = new QAction(tr("Update All Normals"), this);
    _action[ACTION_EDIT_INVERT_VERT_NORMAL]          = new QAction(tr("Invert Vertex Normals"), this);
    _action[ACTION_EDIT_INVERT_FACE_NORMAL]          = new QAction(tr("Invert Face Normals"), this);
    _action[ACTION_EDIT_INVERT_ALL_NORMAL]           = new QAction(tr("Invert All Normals"), this);
    _action[ACTION_EDIT_RESET_QUALITY]               = new QAction(tr("Reset Quality"), this);
    _action[ACTION_EDIT_RANDOM_VERT_QUALITY]         = new QAction(tr("Random Vertex Quality"), this);
    _action[ACTION_EDIT_RANDOM_FACE_QUALITY]         = new QAction(tr("Random Face Quality"), this);
    _action[ACTION_EDIT_TRANSFER_QUALITY_VERTTOFACE] = new QAction(tr("Vertex Quality To Face"), this);
    _action[ACTION_EDIT_TRANSFER_QUALITY_FACETOVERT] = new QAction(tr("Face Quality To Vertex"), this);
    _action[ACTION_EDIT_RANDOM_VERT_COLOR]           = new QAction(tr("Random Vertex Color"), this);
    _action[ACTION_EDIT_RANDOM_FACE_COLOR]           = new QAction(tr("Random Face Color"), this);
    _action[ACTION_EDIT_TRANSFER_COLOR_VERTTOFACE]   = new QAction(tr("Vertex Color To Face"), this);
    _action[ACTION_EDIT_TRANSFER_COLOR_FACETOVERT]   = new QAction(tr("Face Color To Vertex"), this);
    _action[ACTION_EDIT_UPDATE_BOX]                  = new QAction(tr("Update Box"), this);*/



    /// VIEW ----------------------------------------------
    _action[ACTION_VIEW_ANAGLYPH] = new QAction(tr("Toggle 3D Anaglyph"), this);
    _action[ACTION_VIEW_ANAGLYPH]->setCheckable(true);
    _action[ACTION_VIEW_ANAGLYPH]->setChecked(false);

    //VIEW SUBMENU
    _action[ACTION_VIEW_BOX_DISABLE]        = new QAction(tr("Disable Bounding Box"), this);
    _action[ACTION_VIEW_BOX_WIRED]          = new QAction(tr("Wireframe Bounding Box"), this);
    _action[ACTION_VIEW_BOX_TRANS]          = new QAction(tr("Transparent Bounding Box"), this);
    _action[ACTION_VIEW_BOX_SOLID]          = new QAction(tr("Solid Bounding Box"), this);
    _action[ACTION_VIEW_MESH_DISABLE]       = new QAction(tr("Disable Mesh"), this);
    _action[ACTION_VIEW_MESH_POINT]         = new QAction(tr("Points Cloud"), this);
    _action[ACTION_VIEW_MESH_FLAT]          = new QAction(tr("Flat Shading"), this);
    _action[ACTION_VIEW_MESH_SMOOTH]        = new QAction(tr("Smooth Shading"), this);
    _action[ACTION_VIEW_MESH_VOXEL]         = new QAction(tr("Voxels"), this);
    _action[ACTION_VIEW_COLOR_DISABLE]      = new QAction(tr("Disable Colors"), this);
    _action[ACTION_VIEW_COLOR_VERTEX]       = new QAction(tr("Vertex Colors"), this);
    _action[ACTION_VIEW_COLOR_FACE]         = new QAction(tr("Face Colors"), this);
    _action[ACTION_VIEW_COLOR_TEXTURE]      = new QAction(tr("Texture"), this);
    _action[ACTION_VIEW_COLOR_VERT_QUALITY] = new QAction(tr("Vertex Quality Color"), this);
    _action[ACTION_VIEW_COLOR_FACE_QUALITY] = new QAction(tr("Face Quality Color"), this);
    _action[ACTION_VIEW_COLOR_MATERIAL]     = new QAction(tr("Material"), this);
    _action[ACTION_VIEW_NORMAL_DISABLE]     = new QAction(tr("Disable Normals"), this);
    _action[ACTION_VIEW_NORMAL_VERT]        = new QAction(tr("Vertex Normals"), this);
    _action[ACTION_VIEW_NORMAL_FACE]        = new QAction(tr("Face Normals"), this);
    _action[ACTION_VIEW_MISC_WIRE]          = new QAction(tr("Toggle Wireframe"), this);
    _action[ACTION_VIEW_MISC_GRID]          = new QAction(tr("Toggle Grid"), this);
    _action[ACTION_VIEW_MISC_AXIS]          = new QAction(tr("Toggle Axis"), this);
    _action[ACTION_VIEW_NORMAL_VERT]->setCheckable(true);
    _action[ACTION_VIEW_NORMAL_FACE]->setCheckable(true);
    _action[ACTION_VIEW_MISC_WIRE]->setCheckable(true);
    _action[ACTION_VIEW_MISC_GRID]->setCheckable(true);
    _action[ACTION_VIEW_MISC_AXIS]->setCheckable(true);
    _action[ACTION_VIEW_NORMAL_VERT]->setChecked(false);
    _action[ACTION_VIEW_NORMAL_FACE]->setChecked(false);
    _action[ACTION_VIEW_MISC_WIRE]->setChecked(false);
    _action[ACTION_VIEW_MISC_GRID]->setChecked(false);
    _action[ACTION_VIEW_MISC_AXIS]->setChecked(false);



    /// TOOL ----------------------------------------------
    _action[ACTION_TOOL_CONVEXHULL] = new QAction(tr("Convex Hull"), this);

    //TOOL SUBMENU
    /*_action[ACTION_TOOL_VOXEL_DISABLE]     = new QAction(tr("Delete Voxels"), this);
    _action[ACTION_TOOL_VOXEL_EXTERN]      = new QAction(tr("Voxelize Surface"), this);
    _action[ACTION_TOOL_VOXEL_ALL]         = new QAction(tr("Voxelize All"), this);*/



    /// WINDOW --------------------------------------------

    //WINDOW SUBMENU
    _action[ACTION_WINDOW_BAR_STATUS]  = new QAction(tr("Status Bar"), this);
    _action[ACTION_WINDOW_BAR_STATUS]->setCheckable(true);
    _action[ACTION_WINDOW_BAR_STATUS]->setChecked(true);



    /// HELP ----------------------------------------------
    _action[ACTION_HELP_ABOUT] = new QAction(tr("About CGView..."), this);

    //HELP SUBMENU
}

//Create connections between actions and objects
void MainWindow::createConnections()
{
    /// GENERAL -------------------------------------------
    connect(_engine, SIGNAL(sendDcel(CGMesh*)), _glWindow, SLOT(addMesh(CGMesh*)));
    connect(_engine, SIGNAL(sendDcel(CGMesh*)), _statusBar, SLOT(Reset()));
    connect(_engine, SIGNAL(sendInfo(const unsigned int, const unsigned int, const unsigned int)), _statusBar, SLOT(setInfo(const unsigned int, const unsigned int, const unsigned int)));
    connect(_engine, SIGNAL(sendDcel(CGMesh*)), this, SLOT(endIntro()));
    connect(_engine, SIGNAL(UpdateWindow()),    _glWindow, SLOT(UpdateWindow()));



    /// FILE ----------------------------------------------
    connect(_action[ACTION_FILE_OPEN],   SIGNAL(triggered()), _engine, SLOT(open_file()));
    //connect(_action[ACTION_FILE_ADD],   SIGNAL(triggered()), _engine, SLOT(open_file()));
    connect(_action[ACTION_FILE_SAVEAS], SIGNAL(triggered()), _engine, SLOT(save_file()));
    //connect(_action[ACTION_FILE_SAVE],   SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_FILE_CLOSE],  SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_FILE_CLOSE],  SIGNAL(triggered()), this, SLOT(endIntro()));
    connect(_action[ACTION_FILE_RESET],  SIGNAL(triggered()), _engine,   SLOT(reset()));
    connect(_action[ACTION_FILE_RESET],  SIGNAL(triggered()), _glWindow, SLOT(Reset()));
    connect(_action[ACTION_FILE_EXIT],   SIGNAL(triggered()), this,   SLOT(close()));

    //FILE SUBMENU
    connect( _action[ACTION_FILE_NEW_CLOUD], SIGNAL(triggered()), _engine, SLOT(newObject()));



    /// EDIT ----------------------------------------------

    //EDIT SUBMENU
    //connect(_action[ACTION_EDIT_UPDATE_VERT_NORMAL], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_UPDATE_FACE_NORMAL], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_UPDATE_ALL_NORMAL], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_INVERT_VERT_NORMAL], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_INVERT_FACE_NORMAL], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_INVERT_ALL_NORMAL],         SIGNAL(triggered()), _glWindow, SLOT(invertNormals()));
    //connect(_action[ACTION_EDIT_RESET_QUALITY], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_RANDOM_VERT_QUALITY], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_RANDOM_FACE_QUALITY], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_TRANSFER_QUALITY_VERTTOFACE], SIGNAL(triggered()), , SLOT());
    /*connect(_action[ACTION_EDIT_TRANSFER_QUALITY_FACETOVERT], SIGNAL(triggered()), _engine, SLOT(facetovert_q()));*/

    //connect(_action[ACTION_EDIT_RANDOM_VERT_COLOR],         SIGNAL(triggered()), _glWindow, SLOT(randColor()));
    //connect(_action[ACTION_EDIT_RANDOM_FACE_COLOR], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_TRANSFER_COLOR_VERTTOFACE], SIGNAL(triggered()), _glWindow, SLOT(colorVF()));
    //connect(_action[ACTION_EDIT_TRANSFER_COLOR_FACETOVERT], SIGNAL(triggered()), , SLOT());
    //connect(_action[ACTION_EDIT_UPDATE_BOX], SIGNAL(triggered()), , SLOT());



    /// VIEW ----------------------------------------------
    connect(_action[ACTION_VIEW_ANAGLYPH], SIGNAL(triggered()), _glWindow, SLOT(useAnaglyph()));

    //VIEW SUBMENU
    connect(_action[ACTION_VIEW_BOX_DISABLE],        SIGNAL(triggered()), _glWindow, SLOT(DisableBoundingBox()));
    connect(_action[ACTION_VIEW_BOX_WIRED],          SIGNAL(triggered()), _glWindow, SLOT(EnableWiredBoundingBox()));
    connect(_action[ACTION_VIEW_BOX_TRANS],          SIGNAL(triggered()), _glWindow, SLOT(EnableTransBoundingBox()));
    connect(_action[ACTION_VIEW_BOX_SOLID],          SIGNAL(triggered()), _glWindow, SLOT(EnableSolidBoundingBox()));
    connect(_action[ACTION_VIEW_MESH_DISABLE],       SIGNAL(triggered()), _glWindow, SLOT(DisableMesh()));
    connect(_action[ACTION_VIEW_MESH_POINT],         SIGNAL(triggered()), _glWindow, SLOT(EnablePointMesh()));
    connect(_action[ACTION_VIEW_MESH_FLAT],          SIGNAL(triggered()), _glWindow, SLOT(EnableFlatMesh()));
    connect(_action[ACTION_VIEW_MESH_SMOOTH],        SIGNAL(triggered()), _glWindow, SLOT(EnableSmoothMesh()));
    //connect(_action[ACTION_VIEW_MESH_VOXEL],         SIGNAL(triggered()), , SLOT());
    connect(_action[ACTION_VIEW_COLOR_DISABLE],      SIGNAL(triggered()), _glWindow, SLOT(DisableColor()));
    connect(_action[ACTION_VIEW_COLOR_VERTEX],       SIGNAL(triggered()), _glWindow, SLOT(EnableVertexColor()));
    connect(_action[ACTION_VIEW_COLOR_FACE],         SIGNAL(triggered()), _glWindow, SLOT(EnableFaceColor()));
    connect(_action[ACTION_VIEW_COLOR_TEXTURE],      SIGNAL(triggered()), _glWindow, SLOT(EnableTexture()));
    connect(_action[ACTION_VIEW_COLOR_VERT_QUALITY], SIGNAL(triggered()), _glWindow, SLOT(EnableQualityVertex()));
    connect(_action[ACTION_VIEW_COLOR_FACE_QUALITY], SIGNAL(triggered()), _glWindow, SLOT(EnableQualityFace()));
    connect(_action[ACTION_VIEW_COLOR_MATERIAL],     SIGNAL(triggered()), _glWindow, SLOT(EnableMaterial()));
    connect(_action[ACTION_VIEW_NORMAL_DISABLE],     SIGNAL(triggered()), _glWindow, SLOT(DisableNormal()));
    connect(_action[ACTION_VIEW_NORMAL_DISABLE],     SIGNAL(triggered()), this, SLOT(Normals()));
    connect(_action[ACTION_VIEW_NORMAL_VERT],        SIGNAL(triggered()), _glWindow, SLOT(ToggleNormalVertex()));
    connect(_action[ACTION_VIEW_NORMAL_FACE],        SIGNAL(triggered()), _glWindow, SLOT(ToggleNormalFace()));
    connect(_action[ACTION_VIEW_MISC_WIRE],          SIGNAL(triggered()), _glWindow, SLOT(ToggleWireframe()));
    connect(_action[ACTION_VIEW_MISC_GRID],          SIGNAL(triggered()), _glWindow, SLOT(ToggleGrid()));
    connect(_action[ACTION_VIEW_MISC_AXIS],          SIGNAL(triggered()), _glWindow, SLOT(ToggleAxis()));




    /// TOOL ----------------------------------------------
    connect(_action[ACTION_TOOL_CONVEXHULL], SIGNAL(triggered()), _engine, SLOT(calculate_ch()));

    //TOOL SUBMENU



    /// WINDOW --------------------------------------------

    //WINDOW SUBMENU
    connect(_action[ACTION_WINDOW_BAR_STATUS],  SIGNAL(triggered()), this, SLOT(ToggleStatus()));



    /// HELP ----------------------------------------------
    //connect(_action[ACTION_ABOUT_HELP], SIGNAL(triggered()), , SLOT());

    //ABOUT SUBMENU
}

void MainWindow::createIntro()
{
    //Creating the intro
    _glIntro = new GLIntro();
    _glIntro->setMinimumSize(500, 500);

    //Creating the intro area
    _area[INTRO] = new QScrollArea;
    _area[INTRO]->setWidget(_glIntro);
    _area[INTRO]->setWidgetResizable(true);
    _area[INTRO]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _area[INTRO]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _area[INTRO]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _area[INTRO]->setMinimumSize(500, 500);
}

void MainWindow::createViewer()
{
    //Creating the viewer
    _glWindow = new GLWindow();
    _glWindow->setMinimumSize(500, 500);
    _glWindow->grabKeyboard();

    //Creating the viewer area
    _area[VIEWER] = new QScrollArea;
    _area[VIEWER]->setWidget(_glWindow);
    _area[VIEWER]->setWidgetResizable(true);
    _area[VIEWER]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _area[VIEWER]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _area[VIEWER]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _area[VIEWER]->setMinimumSize(500, 500);
}

void MainWindow::createStatus()
{
    //Creating the viewer
    _statusBar = new StatusBar();

    //Creating the status bar
    _area[STATUS] = new QScrollArea;
    _area[STATUS]->setWidget(_statusBar);
    _area[STATUS]->setWidgetResizable(true);
    _area[STATUS]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _area[STATUS]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _area[STATUS]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _area[STATUS]->setMinimumHeight(20);
    _area[STATUS]->setMaximumHeight(20);
}

//Enable/Disable the status bar
void MainWindow::ToggleStatus()
{
    if(_action[ACTION_WINDOW_BAR_STATUS]->isChecked())
    {
        _area[STATUS]->setVisible(true);
    }
    else
    {
        _area[STATUS]->setVisible(false);
    }
}


void MainWindow::endIntro()
{
    _area[INTRO]->setVisible(false);
    _glIntro->stopCube();
    _area[VIEWER]->setVisible(true);
    _area[STATUS]->setVisible(true);
}

void MainWindow::Normals()
{
    _action[ACTION_VIEW_NORMAL_VERT]->setChecked(false);
    _action[ACTION_VIEW_NORMAL_FACE]->setChecked(false);
}
