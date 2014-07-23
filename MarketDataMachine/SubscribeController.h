#pragma once

#include <qobject.h>
#include <qstring.h>
#include <qlineedit.h>
#include <memory>
#include "Receiver.h"

class SubscribeController :public QObject{
	Q_OBJECT
public:
	SubscribeController();
	//������֮��ص��ı��ı������
	void setTextLine(QLineEdit* s);
	//���ý�����
	void setReceiver(std::shared_ptr<Receiver> r);
	//�ָ���ʼ״̬
	void reset();
public slots:
	void subscribe();
private:
	std::shared_ptr<Receiver> receiver;
	QLineEdit* source;
};
