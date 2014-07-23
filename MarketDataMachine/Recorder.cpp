#include "Recorder.h"
#include "GVAR.h"
#include <qdebug.h>

//��¼�������־��Ǻ�Լ�����֣��ļ���������ʽΪ���ڼ��Ϻ�Լ���֣���20140718cu1408
Recorder::Recorder(QString name){
	recorderName = tradeDate + name;
	file.setFileName(DAT_PREDIR + recorderName + ".csv");
	//������׷�ӵķ�ʽ���ļ�
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)){
		qDebug() << file.fileName() << " open fail";
		abort();
	}
	recorder.setDevice(&file);
}

Recorder::~Recorder(){
	qDebug() << "~Recorder";
}

//��¼����
void Recorder::record(CThostFtdcDepthMarketDataField *data){
	if (recorder.status() == QTextStream::Ok){
		recorder << data->UpdateTime << ","			//����޸�ʱ��
			<< data->UpdateMillisec << ","			//����޸ĺ���
			<< data->LastPrice << ","				//���¼�
			<< data->HighestPrice << ","				//��߼�
			<< data->LowestPrice << ","				//��ͼ�
			<< data->BidPrice1 << ","				//�����һ
			<< data->BidVolume1 << ","				//������һ
			<< data->AskPrice1 << ","				//������һ
			<< data->AskVolume1 << ","				//������һ
			<< data->OpenPrice << ","				//���տ��̼�
			<< data->UpperLimitPrice << ","			//��ͣ��
			<< data->LowerLimitPrice << ","			//��ͣ��
			<< data->Volume << ","					//��ǰ�ɽ���
			<< data->OpenInterest << ","				//�ֲ���
			<< data->Turnover << ","					//�ɽ����
			<< data->SettlementPrice << ","			//���ν����
			<< data->PreSettlementPrice << ","		//�ϴν����
			<< data->PreClosePrice << ","			//�����̼�
			<< data->PreOpenInterest << ","			//��ֲ���
			<< data->ClosePrice << ","				//�������̼�
			<< data->AveragePrice << "\n";			//���վ���
		recorder.flush();
	}
	else{
		qDebug() << file.fileName() << " recorder error!!";
	}
}

//�ͷ���Դ
void Recorder::release(){
	file.close();
}