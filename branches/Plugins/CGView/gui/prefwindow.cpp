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

	this->_generalBackgroundGradientTopLeftLine     = new QLineEdit;
	this->_generalBackgroundGradientTopLeftLine->setEnabled(false);
	this->_generalBackgroundGradientTopLeftLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->_generalBackgroundGradientBottomLeftLine  = new QLineEdit;
	this->_generalBackgroundGradientBottomLeftLine->setEnabled(false);
	this->_generalBackgroundGradientBottomLeftLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->_generalBackgroundGradientTopRightLine    = new QLineEdit;
	this->_generalBackgroundGradientTopRightLine->setEnabled(false);
	this->_generalBackgroundGradientTopRightLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->_generalBackgroundGradientBottomRightLine = new QLineEdit;
	this->_generalBackgroundGradientBottomRightLine->setEnabled(false);
	this->_generalBackgroundGradientBottomRightLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->_generalDefaultDirectoryLine              = new QLineEdit;
	this->_generalDefaultDirectoryLine->setEnabled(false);
	this->_generalDefaultDirectoryLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	generalLayout->addWidget(this->_generalBackgroundGradientTopLeftLine,     0, 1);
	generalLayout->addWidget(this->_generalBackgroundGradientBottomLeftLine,  1, 1);
	generalLayout->addWidget(this->_generalBackgroundGradientTopRightLine,    2, 1);
	generalLayout->addWidget(this->_generalBackgroundGradientBottomRightLine, 3, 1);
	generalLayout->addWidget(this->_generalDefaultDirectoryLine,              4, 1);

	QPushButton *generalBackgroundGradientTopLeftButton     = new QPushButton(QString("Choose..."), generalTab);
	QPushButton *generalBackgroundGradientBottomLeftButton  = new QPushButton(QString("Choose..."), generalTab);
	QPushButton *generalBackgroundGradientTopRightButton    = new QPushButton(QString("Choose..."), generalTab);
	QPushButton *generalBackgroundGradientBottomRightButton = new QPushButton(QString("Choose..."), generalTab);
	QPushButton *generalDefaultDirectoryButton              = new QPushButton(QString("Browse..."), generalTab);
	generalLayout->addWidget(generalBackgroundGradientTopLeftButton,     0, 2);
	generalLayout->addWidget(generalBackgroundGradientBottomLeftButton,  1, 2);
	generalLayout->addWidget(generalBackgroundGradientTopRightButton,    2, 2);
	generalLayout->addWidget(generalBackgroundGradientBottomRightButton, 3, 2);
	generalLayout->addWidget(generalDefaultDirectoryButton,              4, 2);

	generalLayout->setColumnStretch(0, 2);
	generalLayout->setColumnStretch(1, 3);
	generalLayout->setColumnStretch(2, 1);

	generalTab->setLayout(generalLayout);

	// TODO: Implement color and directory pickers

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
}

void PrefWindow::setUI(void)
{
	PrefController *controller = PrefController::sharedInstance();

	// General
	QPalette palette;
	palette.setColor(QPalette::Base, QColor(controller->gradientColorComponent(0, 0),
			controller->gradientColorComponent(0, 1),
			controller->gradientColorComponent(0, 2)));
	this->_generalBackgroundGradientTopLeftLine->setPalette(palette);
	palette.setColor(QPalette::Base, QColor(controller->gradientColorComponent(1, 0),
			controller->gradientColorComponent(1, 1),
			controller->gradientColorComponent(1, 2)));
	this->_generalBackgroundGradientBottomLeftLine->setPalette(palette);
	palette.setColor(QPalette::Base, QColor(controller->gradientColorComponent(2, 0),
			controller->gradientColorComponent(2, 1),
			controller->gradientColorComponent(2, 2)));
	this->_generalBackgroundGradientTopRightLine->setPalette(palette);
	palette.setColor(QPalette::Base, QColor(controller->gradientColorComponent(3, 0),
			controller->gradientColorComponent(3, 1),
			controller->gradientColorComponent(3, 2)));
	this->_generalBackgroundGradientBottomRightLine->setPalette(palette);
	this->_generalDefaultDirectoryLine->setText(controller->defaultDirectory());

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
	this->setUI();
}

void PrefWindow::closeEvent(QCloseEvent */*event*/)
{
	PrefController::sharedInstance()->load();
}
