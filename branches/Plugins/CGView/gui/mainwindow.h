/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: mainwindow.h                                                     *
 * Description: Application's MainWindow definition                           *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_GUI_MAINWINDOW_H
#define CGVIEW_GUI_MAINWINDOW_H

/**
 * La classe MainWindow si occupa di creare la finestra del nostro programma
 * gestendo il menu e le azioni corrispondenti a ogni elemento del menu
 */

#include <QMainWindow> // class QMainWindow
#include "pluginmanager.h" // PluginManager

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
class QScrollArea;
class QGridLayout;
class QString;
class QObject;
class QKeyEvent;
class QWidget;
class QToolBar;
QT_END_NAMESPACE
class GLIntro;
class GLWindow;
class StatusBar;
class AboutWindow;
class PrefWindow;
class Engine;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private:
	/** Type of area in the main window */
	enum AreaType
	{
		kAreaIntro = 0,
		kAreaViewer,
		kAreaPalette,
		// Number of areas
		kAreasMax
	};

	/** Type of menu in the main menu */
	enum MenuType
	{
		/// Menu
		kMenuFile = 0,
		kMenuEdit,
		kMenuView,
		kMenuTool,
		kMenuWindow,
		kMenuHelp,

		/// File submenu
		kMenuFileNew,

		/// Edit submenu
//		kMenuEditNormal,
//		kMenuEditQuality,
//		kMenuEditColor,
//		kMenuEditBox,

		/// View submenu
		kMenuViewBox,
		kMenuViewMesh,
		kMenuViewColor,
		kMenuViewMisc,

		/// Tool submenu
//		kMenuToolChaos,
//		kMenuToolVoxel,
		kMenuToolInput,

		/// Window submenu
		kMenuWindowBar,
		
		/// Number of menus and submenus
		kMenusMax
	};

	/** Type of action in the main menu **/
	enum ActionType
	{
		/// File actions
		kActionFileNewCloud = 0,
		kActionFileOpen,
		kActionFileAdd,
		kActionFileSave,
		kActionFileSaveas,
		kActionFileClose,
		kActionFileReset,
		kActionFileExit,

		/// Edit actions
		kActionEditPreferences,
//		kActionEditUpdateVertNormal,
//		kActionEditUpdateFaceNormal,
//		kActionEditUpdateAllNormal,
//		kActionEditInvertVertNormal,
//		kActionEditInvertFaceNormal,
//		kActionEditInvertAllNormal,
//		kActionEditResetQuality,
//		kActionEditRandomVertQuality,
//		kActionEditRandomFaceQuality,
//		kActionEditTransferQualityVerttoface,
//		kActionEditTransferQualityFacetovert,
//		kActionEditRandomVertColor,
//		kActionEditRandomFaceColor,
//		kActionEditTransferColorVerttoface,
//		kActionEditTransferColorFacetovert,
//		kActionEditUpdateBox,

		/// View actions
		kActionViewBoxDisable,
		kActionViewBoxWired,
		kActionViewBoxTrans,
		kActionViewBoxSolid,
		kActionViewMeshDisable,
		kActionViewMeshPoint,
		kActionViewMeshFlat,
		kActionViewMeshSmooth,
//		kActionViewMeshVoxel,
		kActionViewColorDisable,
		kActionViewColorVertex,
		kActionViewColorFace,
//		kActionViewColorTexture,
		kActionViewColorVertQuality,
		kActionViewColorFaceQuality,
		kActionViewColorMaterial,
		kActionViewMiscWire,

		/// Tool actions
		kActionToolConvexhull,
//		kActionToolChaosArnoldcat,
//		kActionToolChaosIkeda,
//		kActionToolChaosDuffing,
//		kActionToolChaosHenon,
//		kActionToolChaosGingerbread,
//		kActionToolChaosTinkerbell,
//		kActionToolChaosZaslavskii,
//		kActionToolVoxelDisable,
//		kActionToolVoxelExtern,
//		kActionToolVoxelAll,

		/// Window actions
		kActionWindowBarStatus,
		kActionWindowBarPalette,

		/// About
		kActionHelpAbout,

		/// Number of actions
		kActionsMax
	};

	/** Action Groups **/
	enum ActionGroupType
	{
		kActiongroupViewBox,
		kActiongroupViewMesh,
		kActiongroupViewColor,
		kActiongroupViewMisc,

//		kActiongroupToolChaos,

		kActiongroupWindowBar,

		/// Number of action groups
		kActiongroupsMax
	};

	/** Toolbars **/
	enum ToolBarType
	{
		kToolbarFile,
		kToolbarView,
		kToolbarMesh,
		kToolbarColor,
		/// Number of toolbars
		kToolbarsMax
	};

	/** Create the main menus **/
	void createMenus(void);
	/** Create the toolbars **/
	void createToolBars(void);
	/** Create the actions for the menus **/
	void createActions(void);
	/** Create connections between actions and objects **/
	void createConnections(void);

	/** Create the intro area **/
	void createIntro(void);
	/** Create the viewer area **/
	void createViewer(void);
	/** create the status bar **/
	void createStatus(void);
	/** Create the palette **/
	void createPalette(void);
	void addToMenu(QObject *plugin, const QString &name, QMenu *menu, const char *signal, QObject *target,
			const char *member, QActionGroup *actionGroup, bool checkable);

	/** Keyboard listener */
	void keyPressEvent(QKeyEvent *event);

	/// Main widget
	QWidget *_mainWidget;
	/// Main menu
	QMenu *_menu[kMenusMax];
	/// Actions of the menu
	QAction *_action[kActionsMax];
	/// Action groups
	QActionGroup *_actiongroup[kActiongroupsMax];
	/// Toolbars
	QToolBar *_toolbar[kToolbarsMax];

	/// Layout of the main window
	QGridLayout *_layout;

	/// The areas present in the window
	QScrollArea *_area[kAreasMax];

	/// Areas
	GLIntro *_glIntro;
	GLWindow *_glWindow;

	StatusBar *_statusBar;

	// Windows
	AboutWindow *_aboutWindow;
	PrefWindow *_prefWindow;

	/// Engine
	Engine *_engine;

private slots:
	/** Enable/Disable the status bar */
	void toggleStatus(void);

	/** Enable/Disable the palette bar */
	void togglePalette(void);

	void endIntro(void);

	void setupPlugin(QObject *plugin, PluginManager::PluginType type);

	void runTransformPlugin(void);

	void uiInputPluginToggled(void);
};

#endif // CGVIEW_GUI_MAINWINDOW_H
