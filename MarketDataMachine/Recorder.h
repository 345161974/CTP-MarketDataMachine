#pragma once

#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include "ctp\ThostFtdcUserApiStruct.h"

class Recorder{
public:
	Recorder(QString name);
	~Recorder();
	//��¼����
	void record(CThostFtdcDepthMarketDataField *data);
	//�ͷ���Դ
	void release();
private:
	QString recorderName;
	QFile file;
	QTextStream recorder;
};

