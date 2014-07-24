#pragma once

#include <qdialog.h>
#include <qtextedit.h>
#include <qpushbutton.h>

class EditOnekeyDialog :public QDialog{
	Q_OBJECT
public:
	EditOnekeyDialog();
	void showDialog();
private:
	QTextEdit *textArea;
	QPushButton *okButton;
	QPushButton *cancelButton;
	QString text;			//��¼ԭ���ļ��е�����
private slots:
	void updateIni();
};