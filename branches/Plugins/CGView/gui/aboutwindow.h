#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
class GLIntro;

class AboutWindow : public QDialog
{
	Q_OBJECT
public:
	explicit AboutWindow(QWidget *parent = 0);

protected:
	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	GLIntro *_glIntro;
};

#endif // ABOUTWINDOW_H
