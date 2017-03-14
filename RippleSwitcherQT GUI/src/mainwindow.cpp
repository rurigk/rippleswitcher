#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <pcrecpp.h>
#include <string>
#include <unistd.h> // getuid

QString host_path = "/etc/hosts";

pcrecpp::RE rep("\\\\n");
pcrecpp::RE re("#RippleSectionStart ---- Dont edit this section\\\\n163\\.172\\.71\\.251 osu\\.ppy\\.sh\\\\n163\\.172\\.71\\.251 c\\.ppy\\.sh\\\\n163\\.172\\.71\\.251 c1\\.ppy\\.sh\\\\n163\\.172\\.71\\.251 a\\.ppy\\.sh\\\\n163\\.172\\.71\\.251 i\\.ppy\\.sh\\\\n37\\.187\\.125\\.67 bm6\\.ppy\\.sh\\\\n#RippleSectionEnd",pcrecpp::RE_Options().set_multiline(true));
pcrecpp::RE reo("\\\\n#RippleSectionStart ---- Dont edit this section\\\\n163\\.172\\.71\\.251 osu\\.ppy\\.sh\\\\n163\\.172\\.71\\.251 c\\.ppy\\.sh\\\\n163\\.172\\.71\\.251 c1\\.ppy\\.sh\\\\n163\\.172\\.71\\.251 a\\.ppy\\.sh\\\\n163\\.172\\.71\\.251 i\\.ppy\\.sh\\\\n37\\.187\\.125\\.67 bm6\\.ppy\\.sh\\\\n#RippleSectionEnd\\\\n",pcrecpp::RE_Options().set_multiline(true));
QString ripple_host = "#RippleSectionStart ---- Dont edit this section\n163.172.71.251 osu.ppy.sh\n163.172.71.251 c.ppy.sh\n163.172.71.251 c1.ppy.sh\n163.172.71.251 a.ppy.sh\n163.172.71.251 i.ppy.sh\n37.187.125.67 bm6.ppy.sh\n#RippleSectionEnd";

bool fileExists(QString path) {
	QFileInfo check_file(path);
	// check if file exists and if yes: Is it really a file and no directory?
	if (check_file.exists() && check_file.isFile()) {
		return true;
	} else {
		return false;
	}
}

void saveFile(QString path, QString data){
	string fd = data.toStdString();
	QFile file( path );
	if ( file.open(QIODevice::ReadWrite) )
	{
		QTextStream stream( &file );
		rep.GlobalReplace("\n", &fd);
		stream << QString::fromStdString(fd) << endl;
	}
}
void saveFileNoRipple(QString path, QString data){
	string fd = data.toStdString();
	QFile file( path );
	if ( file.open(QIODevice::ReadWrite | QIODevice::Truncate) )
	{
		QTextStream stream( &file );
		reo.GlobalReplace("", &fd);
		//std::cout << fd << std::endl;
		rep.GlobalReplace("\n", &fd);
		stream << QString::fromStdString(fd) << endl;
	}
}

void saveBackupFile(QString path, QString data){
	if(!fileExists(path)){
		saveFile(path, data);
	}
}

QString readFile(QString path){
	QString data = "";
	QFile inputFile(path);
	if (inputFile.open(QIODevice::ReadOnly))
	{
	   QTextStream in(&inputFile);
	   while ( !in.atEnd() )
	   {
		  data = data+in.readLine()+"\\n";
	   }
	   inputFile.close();
	}
	return data;
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	if(getuid()){
		ui->Switch->setEnabled(false);
		ui->Switch->setStyleSheet("color: #666;");
	}else{
		ui->RootMSG->setVisible(false);
	}
	QString hosts = readFile(host_path);
	if(!re.PartialMatch(pcrecpp::StringPiece(hosts.toStdString())) ){
		ui->OsuText->setVisible(true);
		ui->RippleText->setVisible(false);
	}else{
		ui->OsuText->setVisible(false);
		ui->RippleText->setVisible(true);
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_Switch_clicked()
{
	QString hosts = readFile(host_path);

	if( re.PartialMatch(pcrecpp::StringPiece(hosts.toStdString())) ){
		//std::cout << "Current : Ripple" << std::endl;
		saveFileNoRipple(host_path,hosts);
		ui->OsuText->setVisible(true);
		ui->RippleText->setVisible(false);
	}else{
		//std::cout << "Current : Osu!" << std::endl;
		saveBackupFile(host_path+".rbak", hosts);
		saveFile(host_path,hosts+ripple_host);
		ui->OsuText->setVisible(false);
		ui->RippleText->setVisible(true);
	}
}

