#pragma once

#include <qobject.h>
#include <memory>
#include <qpushbutton.h>
#include "Receiver.h"

class ConnectController :public QObject{
	Q_OBJECT
public:
	ConnectController();
	//���ӿ�������ʼ���Լ�:�����������1.����ʧ�ܣ�2.�Ͽ�����
	void reset();
	std::shared_ptr<Receiver> getReceiver();
	bool isConnect();
private:
	std::shared_ptr<Receiver> receiver;
public slots:
	void connectServer();
signals:
	//֪ͨ���ڲ������ź�
	void connecting();		//��������
	void connectFailed();	//����ʧ��
	void loginSuccess();	//��½�ɹ�
};
