/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: mainwindow.cpp                                                   *
 * Description: Application's MainWindow class                                *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "mainwindow.h"

#include <QtGlobal> // Q_OS_*
#include <QtGui> // QScrollArea
#include <QElapsedTimer> // class QElapsedTimer

#include "engine.h" // class Engine
#include "opengl/intro/glintro.h" // class GLIntro
#include "opengl/glwindow.h" // class GLWindow
#include "statusbar.h" // class StatusBar
#include "interfaces.h" // class PluginTransformInterface
#include "pluginmanager.h" // class PluginManager

/** Costruttore
 * Crea la viewport, l'engine, i menu, e attiva il keyboard listener della viewport
 */
MainWindow::MainWindow()
{
	this->_engine = new Engine(NULL);

#ifdef Q_OS_MAC
	// Use the Unifed Toolbar style on Mac OS X
	this->setUnifiedTitleAndToolBarOnMac(true);
#endif // Q_OS_MAC
	this->setToolButtonStyle(Qt::ToolButtonFollowStyle);

	// Setting the title of the main windows
	this->setWindowTitle(QString("CGView"));

	// Setting the minimum height and width and the initial height and width
	this->setMinimumSize(300, 300);
	this->setWindowState(Qt::WindowMaximized);

	this->setContentsMargins(0, 0, 0, 0);

	// Creating the central widget
	this->_mainWidget = new QWidget;
	this->setCentralWidget(this->_mainWidget);

	this->createIntro();
	this->createStatus();
	this->createViewer();
	this->createPalette();

	this->_area[kAreaIntro]->setVisible(true);
	this->_area[kAreaViewer]->setVisible(false);
	this->_statusBar->setVisible(false);
	this->_area[kAreaPalette]->setVisible(false);

	// Creating the layout
	this->_layout = new QGridLayout();
	this->_layout->setSpacing(0);

	this->_layout->addWidget(this->_area[kAreaIntro], 0, 0);
	this->_layout->addWidget(this->_area[kAreaViewer], 1, 0);
	this->_layout->addWidget(this->_area[kAreaPalette], 1, 1);

	this->_mainWidget->setLayout(this->_layout);

	// Creazione dei menu e delle azioni
	this->createActions();
	this->createMenus();
	this->createToolBars();

	// Connessioni
	this->createConnections();

	PluginManager::sharedInstance()->loadPlugins();
}

/** Create the main menus **/
void MainWindow::createMenus(void)
{
	/// FILE ----------------------------------------------
	this->_menu[kMenuFile] = menuBar()->addMenu(tr("&File"));

	// FILE SUBMENU
	this->_menu[kMenuFileNew] = new QMenu("&New", this);

	// Adding submenus and action
	this->_menu[kMenuFile]->addMenu(this->_menu[kMenuFileNew]);

	this->_menu[kMenuFileNew]->addAction(this->_action[kActionFileNewCloud]);
	this->_menu[kMenuFile]->addSeparator();
	this->_menu[kMenuFile]->addAction(this->_action[kActionFileOpen]);
	this->_menu[kMenuFile]->addAction(this->_action[kActionFileAdd]);
	this->_menu[kMenuFile]->addAction(this->_action[kActionFileSaveas]);
	this->_menu[kMenuFile]->addAction(this->_action[kActionFileSave]);
	this->_menu[kMenuFile]->addSeparator();
	this->_menu[kMenuFile]->addAction(this->_action[kActionFileClose]);
	this->_menu[kMenuFile]->addAction(this->_action[kActionFileReset]);
	this->_menu[kMenuFile]->addSeparator();
	this->_menu[kMenuFile]->addAction(this->_action[kActionFileExit]);

#if 0
	/// EDIT ----------------------------------------------
	this->_menu[kMenuEdit] = menuBar()->addMenu(tr("&Edit"));

	// EDIT SUBMENU
	this->_menu[kMenuEditNormal]  = new QMenu("&Normals", this);
	this->_menu[kMenuEditQuality] = new QMenu("&Quality", this);
	this->_menu[kMenuEditColor]   = new QMenu("&Colors", this);
	this->_menu[kMenuEditBox]     = new QMenu("&Bounding Box", this);

	// Adding submenus and action
	this->_menu[kMenuEdit]->addMenu(this->_menu[kMenuEditNormal]);
	this->_menu[kMenuEdit]->addMenu(this->_menu[kMenuEditQuality]);
	this->_menu[kMenuEdit]->addMenu(this->_menu[kMenuEditColor]);
	this->_menu[kMenuEdit]->addMenu(this->_menu[kMenuEditBox]);

	this->_menu[kMenuEditNormal]->addAction(this->_action[kActionEditUpdateVertNormal]);
	this->_menu[kMenuEditNormal]->addAction(this->_action[kActionEditUpdateFaceNormal]);
	this->_menu[kMenuEditNormal]->addAction(this->_action[kActionEditUpdateAllNormal]);
	this->_menu[kMenuEditNormal]->addAction(this->_action[kActionEditInvertVertNormal]);
	this->_menu[kMenuEditNormal]->addAction(this->_action[kActionEditInvertFaceNormal]);
	this->_menu[kMenuEditNormal]->addAction(this->_action[kActionEditInvertAllNormal]);
	this->_menu[kMenuEditQuality]->addAction(this->_action[kActionEditResetQuality]);
	this->_menu[kMenuEditQuality]->addAction(this->_action[kActionEditRandomVertQuality]);
	this->_menu[kMenuEditQuality]->addAction(this->_action[kActionEditRandomFaceQuality]);
	this->_menu[kMenuEditQuality]->addAction(this->_action[kActionEditTransferQualityVerttoface]);
	this->_menu[kMenuEditQuality]->addAction(this->_action[kActionEditTransferQualityFacetovert]);
	this->_menu[kMenuEditColor]->addAction(this->_action[kActionEditRandomVertColor]);
	this->_menu[kMenuEditColor]->addAction(this->_action[kActionEditRandomFaceColor]);
	this->_menu[kMenuEditColor]->addAction(this->_action[kActionEditTransferColorVerttoface]);
	this->_menu[kMenuEditColor]->addAction(this->_action[kActionEditTransferColorFacetovert]);
	this->_menu[kMenuEditBox]->addAction(this->_action[kActionEditUpdateBox]);
#endif // 0

	/// VIEW ----------------------------------------------
	this->_menu[kMenuView] = menuBar()->addMenu(tr("&View"));

	// VIEW SUBMENU
	this->_menu[kMenuViewBox]    = new QMenu("&Bounding Box", this);
	this->_menu[kMenuViewMesh]   = new QMenu("&Mesh", this);
	this->_menu[kMenuViewColor]  = new QMenu("&Colors", this);
	this->_menu[kMenuViewMisc]   = new QMenu("&Miscellaneous", this);

	// Adding submenus and action
	this->_menu[kMenuView]->addMenu(this->_menu[kMenuViewBox]);
	this->_menu[kMenuView]->addMenu(this->_menu[kMenuViewMesh]);
	this->_menu[kMenuView]->addMenu(this->_menu[kMenuViewColor]);
	this->_menu[kMenuView]->addMenu(this->_menu[kMenuViewMisc]);

	this->_menu[kMenuViewBox]->addAction(this->_action[kActionViewBoxDisable]);
	this->_menu[kMenuViewBox]->addSeparator();
	this->_menu[kMenuViewBox]->addAction(this->_action[kActionViewBoxWired]);
	this->_menu[kMenuViewBox]->addAction(this->_action[kActionViewBoxTrans]);
	this->_menu[kMenuViewBox]->addAction(this->_action[kActionViewBoxSolid]);
	this->_menu[kMenuViewMesh]->addAction(this->_action[kActionViewMeshDisable]);
	this->_menu[kMenuViewMesh]->addSeparator();
	this->_menu[kMenuViewMesh]->addAction(this->_action[kActionViewMeshPoint]);
	this->_menu[kMenuViewMesh]->addAction(this->_action[kActionViewMeshFlat]);
	this->_menu[kMenuViewMesh]->addAction(this->_action[kActionViewMeshSmooth]);
	this->_menu[kMenuViewMesh]->addAction(this->_action[kActionViewMeshVoxel]);
	this->_menu[kMenuViewColor]->addAction(this->_action[kActionViewColorDisable]);
	this->_menu[kMenuViewColor]->addSeparator();
	this->_menu[kMenuViewColor]->addAction(this->_action[kActionViewColorVertex]);
	this->_menu[kMenuViewColor]->addAction(this->_action[kActionViewColorFace]);
	this->_menu[kMenuViewColor]->addAction(this->_action[kActionViewColorTexture]);
	this->_menu[kMenuViewColor]->addSeparator();
	this->_menu[kMenuViewColor]->addAction(this->_action[kActionViewColorVertQuality]);
	this->_menu[kMenuViewColor]->addAction(this->_action[kActionViewColorFaceQuality]);
	this->_menu[kMenuViewColor]->addSeparator();
	this->_menu[kMenuViewColor]->addAction(this->_action[kActionViewColorMaterial]);
	this->_menu[kMenuViewMisc]->addAction(this->_action[kActionViewMiscWire]);
	this->_menu[kMenuView]->addSeparator();

	/// TOOL ----------------------------------------------
	this->_menu[kMenuTool] = menuBar()->addMenu(tr("&Tool"));

	// TOOL SUBMENU
	//this->_menu[kMenuToolChaos] = new QMenu("&Chaotic Maps", this);
	//this->_menu[kMenuToolVoxel] = new QMenu("&Voxelize", this);
	this->_menu[kMenuToolInput] = new QMenu("&Input methods", this);

	// Adding submenus and action
	this->_menu[kMenuTool]->addAction(this->_action[kActionToolConvexhull]);

	this->_menu[kMenuTool]->addMenu(this->_menu[kMenuToolInput]);
#if 0
	this->_menu[kMenuTool]->addMenu(this->_menu[kMenuToolChaos]);
	this->_menu[kMenuTool]->addMenu(this->_menu[kMenuToolVoxel]);

	this->_menu[kMenuToolVoxel]->addAction(this->_action[kActionToolVoxelDisable]);
	this->_menu[kMenuToolVoxel]->addSeparator();
	this->_menu[kMenuToolVoxel]->addAction(this->_action[kActionToolVoxelExtern]);
	this->_menu[kMenuToolVoxel]->addAction(this->_action[kActionToolVoxelAll]);
#endif // 0

	/// WINDOW --------------------------------------------
	this->_menu[kMenuWindow] = menuBar()->addMenu(tr("&Window"));

	// OPTION SUBMENU
	this->_menu[kMenuWindowBar] = new QMenu("&Bars", this);

	// Adding submenus and action
	this->_menu[kMenuWindow]->addMenu(this->_menu[kMenuWindowBar]);

	this->_menu[kMenuWindowBar]->addAction(this->_action[kActionWindowBarStatus]);
	this->_menu[kMenuWindowBar]->addAction(this->_action[kActionWindowBarPalette]);

	/// HELP ----------------------------------------------
	this->_menu[kMenuHelp] = menuBar()->addMenu(tr("&?"));

	// ABOUT SUBMENU

	// Adding submenus and action
	this->_menu[kMenuHelp]->addAction(this->_action[kActionHelpAbout]);
}

/** Create the toolbars **/
void MainWindow::createToolBars(void)
{
	/// FILE ----------------------------------------------
	this->_toolbar[kToolbarFile] = this->addToolBar(tr("File"));
	this->_toolbar[kToolbarFile]->addAction(this->_action[kActionFileOpen]);
	this->_toolbar[kToolbarFile]->addAction(this->_action[kActionFileAdd]);
	this->_toolbar[kToolbarFile]->addAction(this->_action[kActionFileSave]);
	this->_toolbar[kToolbarFile]->addAction(this->_action[kActionFileClose]);
	this->_toolbar[kToolbarFile]->addAction(this->_action[kActionFileReset]);
#ifdef Q_WS_MAC
	this->_toolbar[kToolbarFile]->addSeparator();
#endif

	/// VIEW ----------------------------------------------
	this->_toolbar[kToolbarView] = this->addToolBar(tr("View"));
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewBoxDisable]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewBoxWired]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewBoxTrans]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewBoxSolid]);
	this->_toolbar[kToolbarView]->addSeparator();
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewMeshDisable]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewMeshPoint]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewMeshFlat]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewMeshSmooth]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewMeshVoxel]);
	this->_toolbar[kToolbarView]->addSeparator();
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewColorDisable]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewColorVertex]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewColorFace]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewColorTexture]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewColorVertQuality]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewColorFaceQuality]);
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewColorMaterial]);
	this->_toolbar[kToolbarView]->addSeparator();
	this->_toolbar[kToolbarView]->addAction(this->_action[kActionViewMiscWire]);
}

/** Create the actions for the menus and toolbars **/
void MainWindow::createActions(void)
{
	/// FILE ----------------------------------------------
	this->_action[kActionFileOpen]   = new QAction(tr("&Open"), this);
	this->_action[kActionFileOpen]->setShortcut(QKeySequence::Open);
	this->_action[kActionFileAdd]    = new QAction(tr("&Add..."), this);
	this->_action[kActionFileSave]   = new QAction(tr("&Save"), this);
	this->_action[kActionFileSave]->setShortcut(QKeySequence::Save);
	this->_action[kActionFileSaveas] = new QAction(tr("Sa&ve as..."), this);
	this->_action[kActionFileSaveas]->setShortcut(QKeySequence::SaveAs);
	this->_action[kActionFileClose]  = new QAction(tr("&Close"), this);
	this->_action[kActionFileClose]->setShortcut(QKeySequence::Close);
	this->_action[kActionFileReset]  = new QAction(tr("&Reset"), this);
	this->_action[kActionFileReset]->setShortcut(tr("Ctrl+Shift+R"));
	this->_action[kActionFileExit]   = new QAction(tr("E&xit"), this);
	this->_action[kActionFileExit]->setShortcut(QKeySequence::Quit);

	// FILE SUBMENU
	this->_action[kActionFileNewCloud] = new QAction(tr("Points Cloud"), this);

	/// EDIT ----------------------------------------------

	// EDIT SUBMENU
#if 0
	this->_action[kActionEditUpdateVertNormal]          = new QAction(tr("Update Vertex Normals"), this);
	this->_action[kActionEditUpdateFaceNormal]          = new QAction(tr("Update Face Normals"), this);
	this->_action[kActionEditUpdateAllNormal]           = new QAction(tr("Update All Normals"), this);
	this->_action[kActionEditInvertVertNormal]          = new QAction(tr("Invert Vertex Normals"), this);
	this->_action[kActionEditInvertFaceNormal]          = new QAction(tr("Invert Face Normals"), this);
	this->_action[kActionEditInvertAllNormal]           = new QAction(tr("Invert All Normals"), this);
	this->_action[kActionEditResetQuality]              = new QAction(tr("Reset Quality"), this);
	this->_action[kActionEditRandomVertQuality]         = new QAction(tr("Random Vertex Quality"), this);
	this->_action[kActionEditRandomFaceQuality]         = new QAction(tr("Random Face Quality"), this);
	this->_action[kActionEditTransferQualityVerttoface] = new QAction(tr("Vertex Quality To Face"), this);
	this->_action[kActionEditTransferQualityFacetovert] = new QAction(tr("Face Quality To Vertex"), this);
	this->_action[kActionEditRandomVertColor]           = new QAction(tr("Random Vertex Color"), this);
	this->_action[kActionEditRandomFaceColor]           = new QAction(tr("Random Face Color"), this);
	this->_action[kActionEditTransferColorVerttoface]   = new QAction(tr("Vertex Color To Face"), this);
	this->_action[kActionEditTransferColorFacetovert]   = new QAction(tr("Face Color To Vertex"), this);
	this->_action[kActionEditUpdateBox]                 = new QAction(tr("Update Box"), this);
#endif // 0

	/// VIEW ----------------------------------------------

	// VIEW SUBMENU
	this->_actiongroup[kActiongroupViewBox] = new QActionGroup(this);
	this->_action[kActionViewBoxDisable]    = new QAction(tr("Disable Bounding Box"), this);
	this->_action[kActionViewBoxDisable]->setIconText(tr("No B.Box"));
	this->_action[kActionViewBoxDisable]->setCheckable(true);
	this->_actiongroup[kActiongroupViewBox]->addAction(this->_action[kActionViewBoxDisable]);
	this->_action[kActionViewBoxWired]      = new QAction(tr("Wireframe Bounding Box"), this);
	this->_action[kActionViewBoxWired]->setIconText(tr("WF B.Box"));
	this->_action[kActionViewBoxWired]->setCheckable(true);
	this->_actiongroup[kActiongroupViewBox]->addAction(this->_action[kActionViewBoxWired]);
	this->_action[kActionViewBoxTrans]      = new QAction(tr("Transparent Bounding Box"), this);
	this->_action[kActionViewBoxTrans]->setIconText(tr("Transp B.Box"));
	this->_action[kActionViewBoxTrans]->setCheckable(true);
	this->_actiongroup[kActiongroupViewBox]->addAction(this->_action[kActionViewBoxTrans]);
	this->_action[kActionViewBoxSolid]      = new QAction(tr("Solid Bounding Box"), this);
	this->_action[kActionViewBoxSolid]->setIconText(tr("Solid B.Box"));
	this->_action[kActionViewBoxSolid]->setCheckable(true);
	this->_actiongroup[kActiongroupViewBox]->addAction(this->_action[kActionViewBoxSolid]);
	this->_actiongroup[kActiongroupViewBox]->setExclusive(true);
	this->_action[kActionViewBoxDisable]->setChecked(true);

	this->_actiongroup[kActiongroupViewMesh] = new QActionGroup(this);
	this->_action[kActionViewMeshDisable]    = new QAction(tr("Disable Mesh"), this);
	this->_action[kActionViewMeshDisable]->setIconText(tr("No Mesh"));
	this->_action[kActionViewMeshDisable]->setCheckable(true);
	this->_actiongroup[kActiongroupViewMesh]->addAction(this->_action[kActionViewMeshDisable]);
	this->_action[kActionViewMeshPoint]      = new QAction(tr("Points Cloud"), this);
	this->_action[kActionViewMeshPoint]->setIconText(tr("P.Cloud"));
	this->_action[kActionViewMeshPoint]->setCheckable(true);
	this->_actiongroup[kActiongroupViewMesh]->addAction(this->_action[kActionViewMeshPoint]);
	this->_action[kActionViewMeshFlat]       = new QAction(tr("Flat Shading"), this);
	this->_action[kActionViewMeshFlat]->setIconText(tr("Flat Sh."));
	this->_action[kActionViewMeshFlat]->setCheckable(true);
	this->_actiongroup[kActiongroupViewMesh]->addAction(this->_action[kActionViewMeshFlat]);
	this->_action[kActionViewMeshSmooth]     = new QAction(tr("Smooth Shading"), this);
	this->_action[kActionViewMeshSmooth]->setIconText(tr("Smooth Sh."));
	this->_action[kActionViewMeshSmooth]->setCheckable(true);
	this->_actiongroup[kActiongroupViewMesh]->addAction(this->_action[kActionViewMeshSmooth]);
	this->_action[kActionViewMeshVoxel]      = new QAction(tr("Voxels"), this);
	this->_action[kActionViewMeshVoxel]->setIconText(tr("Vox"));
	this->_action[kActionViewMeshVoxel]->setCheckable(true);
	this->_actiongroup[kActiongroupViewMesh]->addAction(this->_action[kActionViewMeshVoxel]);
	this->_actiongroup[kActiongroupViewMesh]->setExclusive(true);
	this->_action[kActionViewMeshDisable]->setChecked(true);

	this->_actiongroup[kActiongroupViewColor]  = new QActionGroup(this);
	this->_action[kActionViewColorDisable]     = new QAction(tr("Disable Colors"), this);
	this->_action[kActionViewColorDisable]->setIconText(tr("No Color"));
	this->_action[kActionViewColorDisable]->setCheckable(true);
	this->_actiongroup[kActiongroupViewColor]->addAction(this->_action[kActionViewColorDisable]);
	this->_action[kActionViewColorVertex]      = new QAction(tr("Vertex Colors"), this);
	this->_action[kActionViewColorVertex]->setIconText(tr("Vert. Col."));
	this->_action[kActionViewColorVertex]->setCheckable(true);
	this->_actiongroup[kActiongroupViewColor]->addAction(this->_action[kActionViewColorVertex]);
	this->_action[kActionViewColorFace]        = new QAction(tr("Face Colors"), this);
	this->_action[kActionViewColorFace]->setIconText(tr("Face Col."));
	this->_action[kActionViewColorFace]->setCheckable(true);
	this->_actiongroup[kActiongroupViewColor]->addAction(this->_action[kActionViewColorFace]);
	this->_action[kActionViewColorTexture]     = new QAction(tr("Texture"), this);
	this->_action[kActionViewColorTexture]->setIconText(tr("Txtr"));
	this->_action[kActionViewColorTexture]->setCheckable(true);
	this->_actiongroup[kActiongroupViewColor]->addAction(this->_action[kActionViewColorTexture]);
	this->_action[kActionViewColorVertQuality] = new QAction(tr("Vertex Quality Color"), this);
	this->_action[kActionViewColorVertQuality]->setIconText(tr("Vert. Qlt. Col."));
	this->_action[kActionViewColorVertQuality]->setCheckable(true);
	this->_actiongroup[kActiongroupViewColor]->addAction(this->_action[kActionViewColorVertQuality]);
	this->_action[kActionViewColorFaceQuality] = new QAction(tr("Face Quality Color"), this);
	this->_action[kActionViewColorFaceQuality]->setIconText(tr("Face Qlt. Col."));
	this->_action[kActionViewColorFaceQuality]->setCheckable(true);
	this->_actiongroup[kActiongroupViewColor]->addAction(this->_action[kActionViewColorFaceQuality]);
	this->_action[kActionViewColorMaterial]    = new QAction(tr("Material"), this);
	this->_action[kActionViewColorMaterial]->setIconText(tr("Mat."));
	this->_action[kActionViewColorMaterial]->setCheckable(true);
	this->_actiongroup[kActiongroupViewColor]->addAction(this->_action[kActionViewColorMaterial]);
	this->_actiongroup[kActiongroupViewColor]->setExclusive(true);
	this->_action[kActionViewColorDisable]->setChecked(true);

	this->_actiongroup[kActiongroupViewMisc] = new QActionGroup(this);
	this->_action[kActionViewMiscWire]       = new QAction(tr("Toggle Wireframe"), this);
	this->_action[kActionViewMiscWire]->setIconText(tr("WF"));
	this->_action[kActionViewMiscWire]->setCheckable(true);
	this->_actiongroup[kActiongroupViewMisc]->addAction(this->_action[kActionViewMiscWire]);
	this->_actiongroup[kActiongroupViewMisc]->setExclusive(false);

	/// TOOL ----------------------------------------------
	this->_action[kActionToolConvexhull] = new QAction(tr("Convex Hull"), this);

#if 0
	this->_action[kActionToolVoxelDisable] = new QAction(tr("Delete Voxels"), this);
	this->_action[kActionToolVoxelExtern]  = new QAction(tr("Voxelize Surface"), this);
	this->_action[kActionToolVoxelAll]     = new QAction(tr("Voxelize All"), this);
#endif // 0

	/// WINDOW --------------------------------------------

	// WINDOW SUBMENU
	this->_actiongroup[kActiongroupWindowBar] = new QActionGroup(this);
	this->_action[kActionWindowBarStatus]     = new QAction(tr("Status Bar"), this);
	this->_action[kActionWindowBarStatus]->setCheckable(true);
	this->_action[kActionWindowBarStatus]->setChecked(true);
	this->_actiongroup[kActiongroupWindowBar]->addAction(this->_action[kActionWindowBarStatus]);
	this->_action[kActionWindowBarPalette]    = new QAction(tr("Palette"), this);
	this->_action[kActionWindowBarPalette]->setCheckable(true);
	this->_action[kActionWindowBarPalette]->setChecked(false);
	this->_actiongroup[kActiongroupWindowBar]->addAction(this->_action[kActionWindowBarPalette]);
	this->_actiongroup[kActiongroupWindowBar]->setExclusive(false);

	/// HELP ----------------------------------------------
	this->_action[kActionHelpAbout] = new QAction(tr("&About CGView..."), this);

	// HELP SUBMENU
}

/** Create connections between actions and objects */
void MainWindow::createConnections(void)
{
	/// GENERAL -------------------------------------------
	connect(this->_engine, SIGNAL(sendDcel(CGMesh*)), this->_glWindow, SLOT(addMesh(CGMesh*)));
	connect(this->_engine, SIGNAL(sendDcel(CGMesh*)), this->_statusBar, SLOT(reset()));
	connect(this->_engine, SIGNAL(sendInfo(const unsigned int, const unsigned int, const unsigned int)),
			this->_statusBar, SLOT(setInfo(const unsigned int, const unsigned int, const unsigned int)));
	connect(this->_engine, SIGNAL(sendDcel(CGMesh*)), this, SLOT(endIntro()));
	connect(this->_engine, SIGNAL(updateWindow()),	this->_glWindow, SLOT(updateWindow()));

	connect(PluginManager::sharedInstance(), SIGNAL(loadedPlugin(QObject*, PluginManager::PluginType)),
			this, SLOT(setupPlugin(QObject*, PluginManager::PluginType)));
	connect(PluginManager::sharedInstance(), SIGNAL(loadedPlugin(QObject*, PluginManager::PluginType)),
			PluginManager::sharedInstance(), SLOT(setupPlugin(QObject*, PluginManager::PluginType)));

	/// FILE ----------------------------------------------
	connect(this->_action[kActionFileOpen],    SIGNAL(triggered()), this->_engine,   SLOT(openFile()));
	//connect(this->_action[kActionFileAdd],   SIGNAL(triggered()), this->_engine,   SLOT(openFile()));
	connect(this->_action[kActionFileSaveas],  SIGNAL(triggered()), this->_engine,   SLOT(saveFile()));
	//connect(this->_action[kActionFileSave],  SIGNAL(triggered()), ,                SLOT());
	//connect(this->_action[kActionFileClose], SIGNAL(triggered()), ,                SLOT());
	//connect(this->_action[kActionFileClose], SIGNAL(triggered()), this,            SLOT(prova()));
	connect(this->_action[kActionFileReset],   SIGNAL(triggered()), this->_engine,   SLOT(reset()));
	connect(this->_action[kActionFileReset],   SIGNAL(triggered()), this->_glWindow, SLOT(reset()));
	connect(this->_action[kActionFileExit],    SIGNAL(triggered()), this,            SLOT(close()));

	// FILE SUBMENU
	connect(this->_action[kActionFileNewCloud], SIGNAL(triggered()), this->_engine, SLOT(newObject()));

	/// EDIT ----------------------------------------------

	// EDIT SUBMENU
	//connect(this->_action[kActionEditUpdateVertNormal],          SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditUpdateFaceNormal],          SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditUpdateAllNormal],           SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditInvertVertNormal],          SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditInvertFaceNormal],          SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditInvertAllNormal],           SIGNAL(triggered()),
	//		this->_glWindow, SLOT(invertNormals()));
	//connect(this->_action[kActionEditResetQuality],              SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditRandomVertQuality],         SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditRandomFaceQuality],         SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditTransferQualityVerttoface], SIGNAL(triggered()), , SLOT());
	/*connect(this->_action[kActionEditTransferQualityFacetovert],   SIGNAL(triggered()),
			this->_engine, SLOT(faceToVertQ()));*/

	//connect(this->_action[kActionEditRandomVertColor],         SIGNAL(triggered()),
	//		this->_glWindow, SLOT(randColor()));
	//connect(this->_action[kActionEditRandomFaceColor],         SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditTransferColorVerttoface], SIGNAL(triggered()),
	//		this->_glWindow, SLOT(colorVF()));
	//connect(this->_action[kActionEditTransferColorFacetovert], SIGNAL(triggered()), , SLOT());
	//connect(this->_action[kActionEditUpdateBox],               SIGNAL(triggered()), , SLOT());

	/// VIEW ----------------------------------------------

	// VIEW SUBMENU
	connect(this->_action[kActionViewBoxDisable],       SIGNAL(triggered()), this->_glWindow, SLOT(disableBoundingBox()));
	connect(this->_action[kActionViewBoxWired],         SIGNAL(triggered()), this->_glWindow, SLOT(enableWiredBoundingBox()));
	connect(this->_action[kActionViewBoxTrans],         SIGNAL(triggered()), this->_glWindow, SLOT(enableTransBoundingBox()));
	connect(this->_action[kActionViewBoxSolid],         SIGNAL(triggered()), this->_glWindow, SLOT(enableSolidBoundingBox()));
	connect(this->_action[kActionViewMeshDisable],      SIGNAL(triggered()), this->_glWindow, SLOT(disableMesh()));
	connect(this->_action[kActionViewMeshPoint],        SIGNAL(triggered()), this->_glWindow, SLOT(enablePointMesh()));
	connect(this->_action[kActionViewMeshFlat],         SIGNAL(triggered()), this->_glWindow, SLOT(enableFlatMesh()));
	connect(this->_action[kActionViewMeshSmooth],       SIGNAL(triggered()), this->_glWindow, SLOT(enableSmoothMesh()));
	//connect(this->_action[kActionViewMeshVoxel],      SIGNAL(triggered()), ,                SLOT());
	connect(this->_action[kActionViewColorDisable],     SIGNAL(triggered()), this->_glWindow, SLOT(disableColor()));
	connect(this->_action[kActionViewColorVertex],      SIGNAL(triggered()), this->_glWindow, SLOT(enableVertexColor()));
	connect(this->_action[kActionViewColorFace],        SIGNAL(triggered()), this->_glWindow, SLOT(enableFaceColor()));
	connect(this->_action[kActionViewColorTexture],     SIGNAL(triggered()), this->_glWindow, SLOT(enableTexture()));
	connect(this->_action[kActionViewColorVertQuality], SIGNAL(triggered()), this->_glWindow, SLOT(enableQualityVertex()));
	connect(this->_action[kActionViewColorFaceQuality], SIGNAL(triggered()), this->_glWindow, SLOT(enableQualityFace()));
	connect(this->_action[kActionViewColorMaterial],    SIGNAL(triggered()), this->_glWindow, SLOT(enableMaterial()));
	connect(this->_action[kActionViewMiscWire],         SIGNAL(triggered()), this->_glWindow, SLOT(toggleWireframe()));

	/// TOOL ----------------------------------------------
	connect(this->_action[kActionToolConvexhull], SIGNAL(triggered()), this->_engine, SLOT(calculateCH()));

	// TOOL SUBMENU

	/// WINDOW --------------------------------------------

	// WINDOW SUBMENU
	connect(this->_action[kActionWindowBarStatus],  SIGNAL(triggered()), this, SLOT(toggleStatus()));
	connect(this->_action[kActionWindowBarPalette], SIGNAL(triggered()), this, SLOT(togglePalette()));

	/// HELP ----------------------------------------------
	//connect(_action[kActionHelpAbout], SIGNAL(triggered()), , SLOT());
}

void MainWindow::createIntro(void)
{
	// Creating the intro
	this->_glIntro = new GLIntro();
	this->_glIntro->setMinimumSize(500, 500);

	// Creating the intro area
	this->_area[kAreaIntro] = new QScrollArea;
	this->_area[kAreaIntro]->setWidget(this->_glIntro);
	this->_area[kAreaIntro]->setWidgetResizable(true);
	this->_area[kAreaIntro]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->_area[kAreaIntro]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->_area[kAreaIntro]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	this->_area[kAreaIntro]->setMinimumSize(500, 500);
}

void MainWindow::createViewer(void)
{
	// Creating the viewer
	this->_glWindow = new GLWindow();
	this->_glWindow->setMinimumSize(500, 500);

	// Creating the viewer area
	this->_area[kAreaViewer] = new QScrollArea;
	this->_area[kAreaViewer]->setWidget(this->_glWindow);
	this->_area[kAreaViewer]->setWidgetResizable(true);
	this->_area[kAreaViewer]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->_area[kAreaViewer]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->_area[kAreaViewer]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	this->_area[kAreaViewer]->setMinimumSize(500, 500);
}

void MainWindow::createStatus(void)
{
	this->_statusBar = new StatusBar();
	this->setStatusBar(this->_statusBar);
}

void MainWindow::createPalette(void)
{
	// Creating the palette bar
	this->_area[kAreaPalette] = new QScrollArea;
	//this->_area[kAreaPalette]->setWidget(Intro);
	this->_area[kAreaPalette]->setWidgetResizable(true);
	this->_area[kAreaPalette]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->_area[kAreaPalette]->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->_area[kAreaPalette]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	this->_area[kAreaPalette]->setMinimumWidth(200);
	this->_area[kAreaPalette]->setMaximumWidth(200);
}

/** Enable/Disable the status bar **/
void MainWindow::toggleStatus(void)
{
	this->_statusBar->setVisible(this->_action[kActionWindowBarStatus]->isChecked());
}

/** Enable/Disable the palette bar **/
void MainWindow::togglePalette(void)
{
	this->_area[kAreaPalette]->setVisible(this->_action[kActionWindowBarPalette]->isChecked());
}

void MainWindow::endIntro(void)
{
	this->_area[kAreaIntro]->setVisible(false);
	this->_glIntro->stopCube();
	this->_area[kAreaViewer]->setVisible(true);
	this->_statusBar->show();
	//this->_area[kAreaPalette]->setVisible(true);
}

void MainWindow::setupPlugin(QObject *plugin, PluginManager::PluginType type)
{
	switch (type)
	{
	case PluginManager::kTypeInvalid:
	case PluginManager::kTypeCollection:
		return;
	case PluginManager::kTypeTransform:
	  {
		PluginTransformInterface *thisPlugin = qobject_cast<PluginTransformInterface *>(plugin);
		if (thisPlugin)
			addToMenu(plugin, thisPlugin->menuName(), this->_menu[MainWindow::kMenuTool/*Chaos*/],
					SIGNAL(triggered()), this, SLOT(runTransformPlugin()),
					NULL/*this->_actiongroup[MainWindow::kActiongroupToolChaos]*/, false);
		thisPlugin->loaded();
	  }
		break;
	case PluginManager::kTypeRender:
	  {
		PluginRenderInterface *thisPlugin = qobject_cast<PluginRenderInterface *>(plugin);
		if (thisPlugin)
			addToMenu(plugin, thisPlugin->menuName(), this->_menu[MainWindow::kMenuView],
					SIGNAL(triggered(bool)), plugin, SLOT(enable(bool)),
					NULL, true);
		connect(thisPlugin, SIGNAL(toggled()), PluginManager::sharedInstance(), SIGNAL(renderPluginToggled()));
		thisPlugin->loaded();
	}
		break;
	case PluginManager::kTypeVisualization:
	  {
		PluginVisualizationInterface *thisPlugin = qobject_cast<PluginVisualizationInterface *>(plugin);
		if (thisPlugin)
			addToMenu(plugin, thisPlugin->menuName(), this->_menu[MainWindow::kMenuViewMisc],
					SIGNAL(triggered(bool)), plugin, SLOT(enable(bool)),
					NULL, true);
		connect(thisPlugin, SIGNAL(toggled()), PluginManager::sharedInstance(), SIGNAL(visualizationPluginToggled()));
		thisPlugin->loaded();
	  }
		break;
	case PluginManager::kTypeUIInput:
	  {
		PluginUIInputInterface *thisPlugin = qobject_cast<PluginUIInputInterface *>(plugin);
		if (thisPlugin)
			addToMenu(plugin, thisPlugin->menuName(), this->_menu[MainWindow::kMenuToolInput],
					SIGNAL(triggered(bool)), plugin, SLOT(enable(bool)),
					NULL, true);
		connect(thisPlugin, SIGNAL(toggled()), this, SLOT(uiInputPluginToggled()));
		thisPlugin->loaded();
	  }
		break;
	}
}

void MainWindow::addToMenu(QObject *plugin, const QString &name, QMenu *menu, const char *signal, QObject *target,
		const char *member, QActionGroup *actionGroup, bool checkable)
{
	QAction *action = new QAction(name, plugin);
	connect(action, signal ? signal : SIGNAL(triggered()), target, member);
	menu->addAction(action);

	if (checkable || actionGroup)
	{
		action->setCheckable(true);
	}
	if (actionGroup)
	{
		actionGroup->addAction(action);
	}
}

void MainWindow::runTransformPlugin(void)
{
	QAction *action = qobject_cast<QAction *>(sender());
	PluginTransformInterface *plugin = qobject_cast<PluginTransformInterface *>(action->parent());

	QElapsedTimer timer;
	timer.start();

	this->_glWindow->runTransformPlugin(plugin);

	// Update the status bar
	this->_statusBar->setTime(timer.elapsed());
	timer.invalidate();
}

void MainWindow::uiInputPluginToggled(void)
{
	PluginUIInputInterface *senderPlugin = (PluginUIInputInterface *)sender();
	if (!senderPlugin)
		return;
	if (senderPlugin->isEnabled())
		connect(senderPlugin, SIGNAL(receivedEvent(InputEvents::EventType,float)),
				this->_glWindow, SLOT(uiInputEvent(InputEvents::EventType,float)));
	else
		disconnect(senderPlugin, SIGNAL(receivedEvent(InputEvents::EventType,float)),
				this->_glWindow, SLOT(uiInputEvent(InputEvents::EventType,float)));
}

/**
 * Keyboard listener
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (InputEvents::DispatchEvent((QEvent *)event))
		event->accept();
	else
		event->ignore();
}
