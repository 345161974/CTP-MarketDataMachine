#include "GVAR.h"

//ǰ�û���ַ
QString FRONT_ADDRESS("");

//�����״̬
const QString OFFLINE("����");
const QString CONNECTING("��������...");
const QString ONLINE("����");
const QString SUBSCRIBING("���ڽ�������...");
const QString DISCONNECTING("���ڶϿ�����...");

//�������������ļ�*.dat��ǰ׺��ַ
const QString DAT_PREDIR("data/");

//ȫ����Լ���б�(��Լ����)
std::map<QString, Instrument*> instruList;

//���ڶ��ĵĺ�Լ����(��Լ����)
std::set<QString> instruSet;

//������
QString tradeDate;

//���ݿ�����
QString DB_DRIVER_NAME;
QString DB_HOST_NAME;
QString DATABASE_NAME;
QString USER_NAME;
QString PASSWORD;