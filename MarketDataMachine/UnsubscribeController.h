#pragma once

#include <qobject.h>
#include <memory>
#include <qlineedit.h>
#include "Receiver.h"

class UnsubscribeController :public QObject{
	Q_OBJECT
public:
	UnsubscribeController();
	//������֮��ص��ı��ı������
	void setTextLine(QLineEdit* s);
	//���ý�����
	void setReceiver(std::shared_ptr<Receiver> r);
	//�ָ���ʼ״̬
	void reset();
public slots:
	void unsubscribe();
private:
	std::shared_ptr<Receiver> receiver;
	QLineEdit* source;
};