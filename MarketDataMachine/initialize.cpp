//��ʼ�������еĸ��ֱ���
#include "GVAR.h"
#include "initialize.h"
#include <qdebug.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qsettings.h>
#include <qmessagebox.h>
#include <map>
using std::make_pair;

//��ȡ�ĵ��ҵ�ǰ�û���ַ
void iniFrontAdress(){
	QFile iniFile("ini/front.ini");
	if (!iniFile.open(QIODevice::ReadOnly|QIODevice::Text)){
		qDebug() << "cannot find front.ini";
		QMessageBox::information(0, "����", "�Ҳ���front.ini");
		abort();
	}
	QTextStream in(&iniFile);
	FRONT_ADDRESS = in.readLine();
	iniFile.close();
}

//��ȡ�ĵ���ʼ����Լ��Ϣ
void iniInstrument(){
	QFile iniFile("ini/instrumentInfo.ini");
	if (!iniFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug() << "cannot find instrumentInfo.ini";
		QMessageBox::information(0, "����", "�Ҳ���instrumentInfo.ini");
		abort();
	}
	QTextStream in(&iniFile);
	QString line; 
	while (!in.atEnd()){
		line = in.readLine();
		QStringList list = line.split("|");
		QString code = list.at(0).trimmed();
		QString name = list.at(1).trimmed();
		instruList.insert(make_pair(code, new Instrument(code, name)));
	}
	iniFile.close();
}

//��ȡ�ĵ���ʼ�����ݿ���Ϣ
void iniDB(){
	QSettings setting("ini/db.ini", QSettings::IniFormat);
	DB_DRIVER_NAME = setting.value("DB_DRIVER_NAME").toString();
	DB_HOST_NAME = setting.value("DB_HOST_NAME").toString();
	DATABASE_NAME = setting.value("DATABASE_NAME").toString();
	USER_NAME = setting.value("USER_NAME").toString();
	PASSWORD = setting.value("PASSWORD").toString();
}