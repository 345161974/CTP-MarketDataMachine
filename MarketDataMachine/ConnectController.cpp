#include "ConnectController.h"
using std::shared_ptr;
using std::make_shared;

ConnectController::ConnectController() = default;

//���ӿ�������ʼ���Լ�
void ConnectController::reset(){
	receiver = nullptr;
}

//�������ӿ������жԶ�����������
shared_ptr<Receiver> ConnectController::getReceiver(){
	return receiver;
}

/*************************************�ۺ���***********************************************/

void ConnectController::connectServer(){
	receiver = make_shared<Receiver>();
	//���������źţ��ﵽת��Receiver���źŸ������Ŀ��
	connect(receiver.get(), SIGNAL(connectFailed()), this, SIGNAL(connectFailed()));
	connect(receiver.get(), SIGNAL(loginSuccess()), this, SIGNAL(loginSuccess()));
	receiver->connectServer();
	emit connecting();		//֪ͨ���ڲ��������ڵ�״̬Ϊ��������
}

