/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: prefwindow.h                                                     *
 * Description: Preferences Dialog                                            *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "prefwindow.h"

#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPalette>
#include <QColorDialog>
#include <QDir>
#include "prefcontroller.h"
#include "interfaces.h"
#include "pluginmanager.h"

PrefWindow::PrefWindow(QWidget *parent) : QDialog(parent)
{
	this->setBaseSize(720, 500);
	this->setMinimumSize(720, 500);
	this->resize(720, 500);
	this->setModal(true);
	connect(this, SIGNAL(accepted()), PrefController::sharedInstance(), SLOT(save()));
	connect(this, SIGNAL(rejected()), PrefController::sharedInstance(), SLOT(load()));

	// Create widgets
	QTabWidget *tabWidget = new QTabWidget(this);
	QWidget *generalTab = new QWidget(tabWidget);
	QScrollArea *pluginsTab = new QScrollArea(tabWidget);
	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	QVBoxLayout *layout = new QVBoxLayout;

	// Fill General Tab
	QGridLayout *generalLayout = new QGridLayout(generalTab);
	QLabel *generalBackgroundGradientTopLeftLabel     = new QLabel(QString("Background Gradient (top left):"),
			generalTab);
	QLabel *generalBackgroundGradientBottomLeftLabel  = new QLabel(QString("Background Gradient (bottom left):"),
			generalTab);
	QLabel *generalBackgroundGradientTopRightLabel    = new QLabel(QString("Background Gradient (top right):"),
			generalTab);
	QLabel *generalBackgroundGradientBottomRightLabel = new QLabel(QString("Background Gradient (bottom right):"),
			generalTab);
	QLabel *generalDefaultDirectoryLabel              = new QLabel(QString("Default directory:"), generalTab);
	generalLayout->addWidget(generalBackgroundGradientTopLeftLabel,     0, 0, 1, 1, Qt::AlignRight);
	generalLayout->addWidget(generalBackgroundGradientBottomLeftLabel,  1, 0, 1, 1, Qt::AlignRight);
	generalLayout->addWidget(generalBackgroundGradientTopRightLabel,    2, 0, 1, 1, Qt::AlignRight);
	generalLayout->addWidget(generalBackgroundGradientBottomRightLabel, 3, 0, 1, 1, Qt::AlignRight);
	generalLayout->addWidget(generalDefaultDirectoryLabel,              4, 0, 1, 1, Qt::AlignRight);

	this->_generalBGGradientTopLeftLine     = new QLineEdit;
	this->_generalBGGradientTopLeftLine->setEnabled(false);
	this->_generalBGGradientTopLeftLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->_generalBGGradientBottomLeftLine  = new QLineEdit;
	this->_generalBGGradientBottomLeftLine->setEnabled(false);
	this->_generalBGGradientBottomLeftLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->_generalBGGradientTopRightLine    = new QLineEdit;
	this->_generalBGGradientTopRightLine->setEnabled(false);
	this->_generalBGGradientTopRightLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->_generalBGGradientBottomRightLine = new QLineEdit;
	this->_generalBGGradientBottomRightLine->setEnabled(false);
	this->_generalBGGradientBottomRightLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->_generalDefaultDirectoryLine      = new QLineEdit;
	this->_generalDefaultDirectoryLine->setEnabled(false);
	this->_generalDefaultDirectoryLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	generalLayout->addWidget(this->_generalBGGradientTopLeftLine,     0, 1);
	generalLayout->addWidget(this->_generalBGGradientBottomLeftLine,  1, 1);
	generalLayout->addWidget(this->_generalBGGradientTopRightLine,    2, 1);
	generalLayout->addWidget(this->_generalBGGradientBottomRightLine, 3, 1);
	generalLayout->addWidget(this->_generalDefaultDirectoryLine,      4, 1);

	QPushButton *generalBGGradientTopLeftButton     = new QPushButton(QString("Choose..."), generalTab);
	QPushButton *generalBGGradientBottomLeftButton  = new QPushButton(QString("Choose..."), generalTab);
	QPushButton *generalBGGradientTopRightButton    = new QPushButton(QString("Choose..."), generalTab);
	QPushButton *generalBGGradientBottomRightButton = new QPushButton(QString("Choose..."), generalTab);
	QPushButton *generalDefaultDirectoryButton      = new QPushButton(QString("Browse..."), generalTab);
	generalLayout->addWidget(generalBGGradientTopLeftButton,     0, 2);
	generalLayout->addWidget(generalBGGradientBottomLeftButton,  1, 2);
	generalLayout->addWidget(generalBGGradientTopRightButton,    2, 2);
	generalLayout->addWidget(generalBGGradientBottomRightButton, 3, 2);
	generalLayout->addWidget(generalDefaultDirectoryButton,      4, 2);

	generalLayout->setColumnStretch(0, 2);
	generalLayout->setColumnStretch(1, 3);
	generalLayout->setColumnStretch(2, 1);

	generalTab->setLayout(generalLayout);

	// Fill Plugins Tab
	QWidget *pluginsWidget = new QWidget;
	QVBoxLayout *pluginsLayout = new QVBoxLayout;
	this->_pluginsRenderingLayout = new QGridLayout;
	this->_pluginsVisualizationLayout = new QGridLayout;
	this->_pluginsTransformationLayout = new QGridLayout;
	this->_pluginsUIInputLayout = new QGridLayout;

	QLabel *pluginsRenderingLabel = new QLabel(QString("Rendering plugins:"));
	QLabel *pluginsVisualizationLabel = new QLabel(QString("Visualization plugins:"));
	QLabel *pluginsTransformationLabel = new QLabel(QString("Transformation plugins:"));
	QLabel *pluginsUIInputLabel = new QLabel(QString("UI Input plugins:"));

	QWidget *pluginsRenderingBox = new QWidget;
	pluginsRenderingBox->setLayout(this->_pluginsRenderingLayout);
	QWidget *pluginsVisualizationBox = new QWidget;
	pluginsVisualizationBox->setLayout(this->_pluginsVisualizationLayout);
	QWidget *pluginsTransformationBox = new QWidget;
	pluginsTransformationBox->setLayout(this->_pluginsTransformationLayout);
	QWidget *pluginsUIInputBox = new QWidget;
	pluginsUIInputBox->setLayout(this->_pluginsUIInputLayout);

	pluginsLayout->addWidget(pluginsRenderingLabel);
	pluginsLayout->addWidget(pluginsRenderingBox);
	pluginsLayout->addWidget(pluginsVisualizationLabel);
	pluginsLayout->addWidget(pluginsVisualizationBox);
	pluginsLayout->addWidget(pluginsTransformationLabel);
	pluginsLayout->addWidget(pluginsTransformationBox);
	pluginsLayout->addWidget(pluginsUIInputLabel);
	pluginsLayout->addWidget(pluginsUIInputBox);

	pluginsWidget->setLayout(pluginsLayout);
	pluginsTab->setWidget(pluginsWidget);
	pluginsTab->setWidgetResizable(true);

	// Fill Tab Widget
	tabWidget->addTab(generalTab, QString("General"));
	tabWidget->addTab(pluginsTab, QString("Plugins"));

	// Set layout
	layout->addWidget(tabWidget);
	layout->addWidget(buttonBox);
	this->setLayout(layout);

	// Set window name
	this->setUI();
	this->setWindowTitle(tr("Preferences"));

	connect(generalBGGradientTopLeftButton,     SIGNAL(clicked()), this, SLOT(showGeneralBGGradientTopLeftLinePicker()));
	connect(generalBGGradientBottomLeftButton,  SIGNAL(clicked()), this, SLOT(showGeneralBGGradientBottomLeftLinePicker()));
	connect(generalBGGradientTopRightButton,    SIGNAL(clicked()), this, SLOT(showGeneralBGGradientTopRightLinePicker()));
	connect(generalBGGradientBottomRightButton, SIGNAL(clicked()), this, SLOT(showGeneralBGGradientBottomRightLinePicker()));
	connect(generalDefaultDirectoryButton,      SIGNAL(clicked()), this, SLOT(showGeneralDefaultDirectoryLineChooser()));
}

void PrefWindow::setUI(void)
{
	this->setUIGeneral();
	this->setUIPlugins();
}

void PrefWindow::setUIGeneral(void)
{
	PrefController *controller = PrefController::sharedInstance();

	// General
	QPalette palette;
	palette.setColor(QPalette::Base, QColor(controller->gradientColorComponent(0, 0),
			controller->gradientColorComponent(0, 1),
			controller->gradientColorComponent(0, 2)));
	this->_generalBGGradientTopLeftLine->setPalette(palette);
	palette.setColor(QPalette::Base, QColor(controller->gradientColorComponent(1, 0),
			controller->gradientColorComponent(1, 1),
			controller->gradientColorComponent(1, 2)));
	this->_generalBGGradientBottomLeftLine->setPalette(palette);
	palette.setColor(QPalette::Base, QColor(controller->gradientColorComponent(2, 0),
			controller->gradientColorComponent(2, 1),
			controller->gradientColorComponent(2, 2)));
	this->_generalBGGradientTopRightLine->setPalette(palette);
	palette.setColor(QPalette::Base, QColor(controller->gradientColorComponent(3, 0),
			controller->gradientColorComponent(3, 1),
			controller->gradientColorComponent(3, 2)));
	this->_generalBGGradientBottomRightLine->setPalette(palette);
	this->_generalDefaultDirectoryLine->setText(controller->defaultDirectory());
}

void PrefWindow::setUIPlugins(void)
{
	// Plugins
	std::vector<PluginRenderInterface *> renderingPlugins = PluginManager::sharedInstance()->renderPlugins();
	for (unsigned int i = 0; i < renderingPlugins.size(); ++i)
	{
		PluginRenderInterface *thisPlugin = renderingPlugins[i];
		QWidget *thisWidget = new QWidget;
		QLabel *label = new QLabel(thisPlugin->menuName());
		QCheckBox *checkBox = new QCheckBox;
		checkBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		checkBox->setCheckState(thisPlugin->isEnabled() ? Qt::Checked : Qt::Unchecked);
		QHBoxLayout *thisLayout = new QHBoxLayout;
		thisLayout->addWidget(label);
		thisLayout->addWidget(checkBox);
		thisWidget->setLayout(thisLayout);
		thisWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		this->_pluginsRenderingLayout->addWidget(thisWidget);
	}
	std::vector<PluginVisualizationInterface *> visualizationPlugins = PluginManager::sharedInstance()->visualizationPlugins();
	for (unsigned int i = 0; i < visualizationPlugins.size(); ++i)
	{
		PluginVisualizationInterface *thisPlugin = visualizationPlugins[i];
		QWidget *thisWidget = new QWidget;
		QLabel *label = new QLabel(thisPlugin->menuName());
		QCheckBox *checkBox = new QCheckBox;
		checkBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		checkBox->setCheckState(thisPlugin->isEnabled() ? Qt::Checked : Qt::Unchecked);
		QHBoxLayout *thisLayout = new QHBoxLayout;
		thisLayout->addWidget(label);
		thisLayout->addWidget(checkBox);
		thisWidget->setLayout(thisLayout);
		thisWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		this->_pluginsVisualizationLayout->addWidget(thisWidget);
	}
	std::vector<PluginTransformInterface *> transformationPlugins = PluginManager::sharedInstance()->transformPlugins();
	for (unsigned int i = 0; i < transformationPlugins.size(); ++i)
	{
		PluginTransformInterface *thisPlugin = transformationPlugins[i];
		QWidget *thisWidget = new QWidget;
		QLabel *label = new QLabel(thisPlugin->menuName());
		QCheckBox *checkBox = new QCheckBox;
		checkBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		checkBox->setCheckState(Qt::Checked);
		checkBox->setEnabled(false);
		QHBoxLayout *thisLayout = new QHBoxLayout;
		thisLayout->addWidget(label);
		thisLayout->addWidget(checkBox);
		thisWidget->setLayout(thisLayout);
		thisWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		this->_pluginsTransformationLayout->addWidget(thisWidget);
	}
	std::vector<PluginUIInputInterface *> uiInputPlugins = PluginManager::sharedInstance()->uiInputPlugins();
	for (unsigned int i = 0; i < uiInputPlugins.size(); ++i)
	{
		PluginUIInputInterface *thisPlugin = uiInputPlugins[i];
		QWidget *thisWidget = new QWidget;
		QLabel *label = new QLabel(thisPlugin->menuName());
		QCheckBox *checkBox = new QCheckBox;
		checkBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		checkBox->setCheckState(thisPlugin->isEnabled() ? Qt::Checked : Qt::Unchecked);
		QHBoxLayout *thisLayout = new QHBoxLayout;
		thisLayout->addWidget(label);
		thisLayout->addWidget(checkBox);
		thisWidget->setLayout(thisLayout);
		thisWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		this->_pluginsUIInputLayout->addWidget(thisWidget);
	}

	this->update();
}

void PrefWindow::showEvent(QShowEvent */*event*/)
{
	PrefController::sharedInstance()->load();
	this->setUI();
}

void PrefWindow::closeEvent(QCloseEvent */*event*/)
{
	PrefController::sharedInstance()->load();
}

void PrefWindow::showGeneralBGGradientTopLeftLinePicker(void)
{
	this->showColorPicker(0);
}

void PrefWindow::showGeneralBGGradientBottomLeftLinePicker(void)
{
	this->showColorPicker(1);
}

void PrefWindow::showGeneralBGGradientTopRightLinePicker(void)
{
	this->showColorPicker(2);
}

void PrefWindow::showGeneralBGGradientBottomRightLinePicker(void)
{
	this->showColorPicker(3);
}

void PrefWindow::showGeneralDefaultDirectoryLineChooser(void)
{
	PrefController *controller = PrefController::sharedInstance();
	QString dirPath = QFileDialog::getExistingDirectory(this, QString(), controller->defaultDirectory());
	if( dirPath.isNull() )
		return;
	QDir dir(dirPath);
	controller->setDefaultDirectory(dir.canonicalPath());
	this->setUIGeneral();
}

void PrefWindow::showColorPicker(int colorID)
{
	PrefController *controller = PrefController::sharedInstance();
	QColor color = QColorDialog::getColor(QColor(controller->gradientColorComponent(colorID, 0),
			controller->gradientColorComponent(colorID, 1),
			controller->gradientColorComponent(colorID, 2)),
			this);
	if( !color.isValid() )
		return;
	controller->setGradientColorComponent(colorID, 0, color.red());
	controller->setGradientColorComponent(colorID, 1, color.green());
	controller->setGradientColorComponent(colorID, 2, color.blue());
	this->setUIGeneral();
}
