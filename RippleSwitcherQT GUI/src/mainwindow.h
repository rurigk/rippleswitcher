#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QRegExp>
#include <QRegExpValidator>
#include <QFileInfo>
#include <QStyle>
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_Switch_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
