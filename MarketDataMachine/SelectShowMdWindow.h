#pragma once

//�û��ڸöԻ�����ѡ��Ҫ��ʾ��������ĺ�Լ
#include <qobject.h>
#include <qdialog.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <set>
#include <vector>

class SelectShowMdWindow :public QDialog{
	Q_OBJECT
public:
	SelectShowMdWindow();
	void showDialog();
private:
	std::set<QString> showedInstru;				//�ڱ����չʾ�ĺ�Լ���뼯��
	std::vector<QCheckBox*>  instruCheckBox;	//ȫ����Լ�ĸ�ѡ��
	QPushButton *okButton;
	QPushButton *cancelButton;
private slots:
	void pushOkButton();
signals:
	void showChange(std::set<QString>& newInstru);
};