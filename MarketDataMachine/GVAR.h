#pragma once

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <qstring.h>
#include <map>
#include <set>
#include "Instrument.h"

//ǰ�û���ַ
extern QString FRONT_ADDRESS;

//�����״̬
extern const QString OFFLINE;
extern const QString CONNECTING;
extern const QString ONLINE;

//�������������ļ�*.dat��ǰ׺��ַ
extern const QString DAT_PREDIR;

//ȫ����Լ���б�(��Լ����)
extern std::map<QString, Instrument*> instruList;

//���ڶ��ĵĺ�Լ����(��Լ����)
extern std::set<QString> instruSet;

//������
extern QString tradeDate;