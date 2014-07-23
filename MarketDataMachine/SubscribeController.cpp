#include "SubscribeController.h"
#include <qstringlist.h>
#include <qdebug.h>
#include <vector>
using std::vector;
using std::shared_ptr;

SubscribeController::SubscribeController() = default;

void SubscribeController::setTextLine(QLineEdit* s){
	source = s;
}

void SubscribeController::setReceiver(shared_ptr<Receiver> r){
	receiver = r;
}

void SubscribeController::reset(){
	receiver = nullptr;
	source = nullptr;
}

void SubscribeController::subscribe(){
	//���ı����ȡ����
	QString &instruments = source->text();
	//���ݷֺŽ��зָ�õ�ÿһ����Լ����
	QStringList list = instruments.split(";", QString::SkipEmptyParts);
	vector<QString> v;
	//��һЩ������˵����յ����룬���ַ�������ĸ�����룬���볤�ȴ���6������
	for (int i = 0; i < list.size(); i++){
		QString item = list.at(i).trimmed();
		if (item != "" && item[0].isLetter()&&item.length()<=6){
			v.push_back(item);
		}
	}
	//����ԭʼ�����飬�����ݴ�vector��ת��������
	int count = v.size();
	char **ppInstrumentID = new char *[count];
	for (int i = 0; i < count; i++){
		ppInstrumentID[i] = new char[7];
		strcpy(ppInstrumentID[i], v[i].toStdString().c_str());
	}
	receiver->subscribeData(ppInstrumentID, count);
	//��������
	source->clear();
}