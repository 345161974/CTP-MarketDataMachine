#include "EditOnekeyDialog.h"
#include <qboxlayout.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qdebug.h>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

EditOnekeyDialog::EditOnekeyDialog(){
	//��ʼ������
	textArea = new QTextEdit(this);
	textArea->setFixedWidth(400);
	okButton = new QPushButton("ȷ��");
	cancelButton = new QPushButton("ȡ��");
	connect(okButton, SIGNAL(clicked()), this, SLOT(updateIni()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
	okButton->setFixedSize(okButton->sizeHint().width(), okButton->sizeHint().height());
	cancelButton->setFixedSize(cancelButton->sizeHint().width(), cancelButton->sizeHint().height());
	//��ȡ�ļ�����
	QFile onekeyFile("ini/onekeySub.ini");
	if (!onekeyFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		QMessageBox::information(this, "����", "��onekeySub.ini��������");
		abort();
	}
	QTextStream in(&onekeyFile);
	in >> text;
	textArea->setPlainText(text);
	onekeyFile.close();
	//��ť����
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	//���岼��
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(textArea);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
	//����
	setWindowTitle("һ�������б�");
	setModal(true);
	hide();
}

//չʾ����
void EditOnekeyDialog::showDialog(){
	textArea->setPlainText(text);
	update();
	show();
}

//����������������ļ�
void EditOnekeyDialog::updateIni(){
	//���¸�������
	text = textArea->toPlainText().trimmed();
	//�����ⲿ�ļ�
	QFile onekeyFile("ini/onekeySub.ini");
	if (!onekeyFile.open(QIODevice::WriteOnly | QIODevice::Text)){
		QMessageBox::information(this, "����", "��onekeySub.ini��������");
		abort();
	}
	QTextStream out(&onekeyFile);
	out << text;
	out.flush();
	onekeyFile.close();
	//���û���������
	QMessageBox::information(this, "����", "������������Ч");
	hide();
}