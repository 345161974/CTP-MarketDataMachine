#include "MdTable.h"
#include "GVAR.h"
#include <qdebug.h>
using std::set;
using std::make_pair;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MdTable::MdTable(){
	this->setColumnCount(7);
	//���ñ�ͷ���� 
	QStringList header;
	header << "��Լ����" << "��Լ��" << "���¼�" << "���" << "����" << "����" <<
		"����";
	this->setHorizontalHeaderLabels(header);
	//���ò��ɱ༭
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//���ö�ʱ��
	updateTimer = new QTimer(this);
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(refreshTable()));
	unsubUpdateTimer = new QTimer(this);
	unsubUpdateTimer->setSingleShot(true);
	connect(unsubUpdateTimer, SIGNAL(timeout()), this, SLOT(updateTableForUnsub()));
}

//�Ͽ����Ӻ��ʼ�����
void MdTable::resetTable(){
	updateTimer->stop();
	this->clearContents();	//����������
	//ע������һ����ǰɾ��
	int i = instruInTable.size();
	for (; i >= 0; i--){
		this->removeRow(i);
	}
	instruInTable.clear();
}

//ˢ�±��
void MdTable::refreshTable(){
	int row = 0;
	for (auto iter = instruInTable.begin(); iter != instruInTable.end(); iter++){
		Instrument* i = instruList[(*iter)];
		QTableWidgetItem *third = new QTableWidgetItem();
		third->setText(QString::number(i->lastPrice));
		QTableWidgetItem *forth = new QTableWidgetItem();
		forth->setText(QString::number(i->bidPrice));
		QTableWidgetItem *fifth = new QTableWidgetItem();
		fifth->setText(QString::number(i->bidVolumn));
		QTableWidgetItem *sixth = new QTableWidgetItem();
		sixth->setText(QString::number(i->askPrice));
		QTableWidgetItem *seventh = new QTableWidgetItem();
		seventh->setText(QString::number(i->askVolumn));
		this->setItem(row, 2, third);
		this->setItem(row, 3, forth);
		this->setItem(row, 4, fifth);
		this->setItem(row, 5, sixth);
		this->setItem(row, 6, seventh);
		row++;
	}
}

//��Ϊ�û�ѡ��������б�,����newInstru���û��ڶԻ�����ѡ���Լ�󴫹���
void MdTable::updateTableForSelect(set<QString>& newInstru){
	updateTimer->stop();   //ֹͣ���±��
	for (auto iter = instruInTable.begin(); iter != instruInTable.end();){
		if (newInstru.find(*iter) == newInstru.end()){	//ȥ����Ҫ�ĺ�Լ
			iter = instruInTable.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	for (auto iter = newInstru.begin(); iter != newInstru.end(); iter++){
		auto i = instruInTable.begin();
		for (; i != instruInTable.end(); i++){
			if ((*i) == (*iter)){
				break;
			}
		}
		if (i == instruInTable.end()){ //����½����ĺ�Լ
			instruInTable.push_back((*iter));
		}
	}
	qDebug() << "���ĺ�Լ�б�";
	for (auto iter = newInstru.begin(); iter != newInstru.end(); iter++){
		qDebug() << (*iter);
	}
	qDebug() << "����Լ�б�";
	for (auto iter = instruInTable.begin(); iter != instruInTable.end(); iter++){
		qDebug() << (*iter);
	}
	//������ʾ�ı��
	this->clearContents();
	int rowCount = this->rowCount();
	for (; rowCount >= 0; rowCount--){
		this->removeRow(rowCount);
	}
	int row = 0;
	for (auto iter = instruInTable.begin(); iter != instruInTable.end(); iter++){
		Instrument* i = instruList[(*iter)];
		QTableWidgetItem *first = new QTableWidgetItem();
		first->setText(i->code);
		QTableWidgetItem *second = new QTableWidgetItem();
		second->setText(i->name);
		QTableWidgetItem *third = new QTableWidgetItem();
		third->setText(QString::number(i->lastPrice));
		QTableWidgetItem *forth = new QTableWidgetItem();
		forth->setText(QString::number(i->bidPrice));
		QTableWidgetItem *fifth = new QTableWidgetItem();
		fifth->setText(QString::number(i->bidVolumn));
		QTableWidgetItem *sixth = new QTableWidgetItem();
		sixth->setText(QString::number(i->askPrice));
		QTableWidgetItem *seventh = new QTableWidgetItem();
		seventh->setText(QString::number(i->askVolumn));
		this->insertRow(row);
		this->setItem(row, 0, first);
		this->setItem(row, 1, second);
		this->setItem(row, 2, third);
		this->setItem(row, 3, forth);
		this->setItem(row, 4, fifth);
		this->setItem(row, 5, sixth);
		this->setItem(row, 6, seventh);
		row++;
	}
	this->update();
	updateTimer->start(1000);
}

//�˶����1.5�����
void MdTable::callUnsubUpdateTimer(){
	unsubUpdateTimer->start(1500);
}

//��Ϊ�û��˶��������б�
void MdTable::updateTableForUnsub(){
	for (auto iter = instruInTable.begin(); iter != instruInTable.end(); ){
		if (instruSet.find(*iter) == instruSet.end()){	//�����ڶ����б���û�ҵ���غ�Լ��ȥ��
			int row = std::distance(instruInTable.begin(), iter);
			this->removeRow(row);
			iter = instruInTable.erase(iter);
		}
		else{
			iter++;
		}
	}
}