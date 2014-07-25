#include "SubscribingDialog.h"
#include "GVAR.h"
#include <qlayout.h>
#include <qdebug.h>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

SubscribingDialog::SubscribingDialog(){
	setWindowTitle("���ڶ��ĵ�����");
	textArea = new QTextEdit(this);
	textArea->setFixedWidth(350);
	textArea->setReadOnly(true);
	okButton = new QPushButton("ȷ��");
	okButton->setFixedSize(okButton->sizeHint().width(), okButton->sizeHint().height());
	connect(okButton, SIGNAL(clicked()), this, SLOT(hide()));
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(textArea);
	layout->addWidget(okButton);
	layout->setAlignment(Qt::AlignHCenter);
	setLayout(layout);
	setModal(true);
	update();
	hide();
}

//չʾ�Ի���
void SubscribingDialog::showDialog(){
	QString text;
	int count = 0;
	for (auto iter = instruSet.begin(); iter != instruSet.end(); iter++){
		text.append((*iter));
		text.append(" ");
		text.append(instruList[(*iter)]->name);
		text.append("   ");
		count++;
		if (count == 3){		//������Ϊһ��
			text.append("\n");
		}
	}
	//����ǰ����������ٷ����µ���������
	textArea->clear();
	textArea->setPlainText(text);
	update();
	show();
}