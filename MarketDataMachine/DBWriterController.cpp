#include "DBWriterController.h"
#include "DBwriter.h"
#include <qmessagebox.h>
#include <qdebug.h>
#include <qfile.h>
#include <qtextstream.h>
#include <QProgressDialog>
#include <set>
using std::set;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

void DBWriterController::readyToWrite(QStringList filenames){
	//�鿴����־�ļ����ѡ����ļ�������û���Ѿ�д������ݿ⵱��
	QFile log("log/persistence.log");
	if (!log.open(QIODevice::ReadOnly | QIODevice::Text)){
		QMessageBox::information(0, "����", "�Ҳ�����־�ļ�");
		abort();
	}
	set<QString> wrote;	//��¼����Щ�ļ��Ѿ�д������ݿ�
	QTextStream in(&log);
	while (!in.atEnd()){
		QString text = in.readLine();
		wrote.insert(text);
	}
	QString warning = "";
	for (int i = 0; i < filenames.size(); i++){
		if (wrote.find(filenames.at(i)) != wrote.end()){
			warning.append(filenames.at(i) + "\n");
		}
	}
	if (warning != ""){
		//���ظ��������ݿ���ļ����ܾ�д�����ݿ⣬Ҫ������ѡ��
		QMessageBox::information(0, "����", warning + "�Ѿ��������ݿ�,����ѡ");
		return;
	}
	//��ʼ����
	DBwriter *writer = DBwriter::getInstance();
	int fileNum = filenames.size();
	for (int i = 0; i < fileNum; i++) {
		writer->processFile(filenames.at(i));
	}
	QMessageBox::information(0, "���", "�Ѵ������ݿ�");
}