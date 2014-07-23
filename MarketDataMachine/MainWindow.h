#pragma once

//��������
#include <qobject.h>
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtimer.h>
#include <qlineedit.h>
#include <memory>
#include <qaction.h>
#include <qmenu.h>
#include "ConnectController.h"
#include "SubscribeController.h"
#include "UnsubscribeController.h"
#include "MdTable.h"
#include "SelectShowMdWindow.h"
#include "DBWriterController.h"

class MainWindow :public QMainWindow{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
private:
	void createStatusBur();
	void createMenu();
	//��ʼ�����ӿ�����
	void initController();
private slots:
	//��timerForUpdateTimeLabel�����Ĳۺ���
	void updateTime();				//ʱ�̸��±���ʱ��

	//��ConnectController�����Ĳۺ���
	void statusConnecting();		//״̬���Ϊ��������,���Ӱ�ť������
	void statusConnectFailed();		//����ʧ��
	void statusConnectSuccess();	//���ӳɹ���״̬���Ϊ���ߣ�ʹ�ö��ĺ��˶���ִ��

	//��disconnectButton�����Ĳۺ���
	void disconnect();				//�Ͽ�����,��ʼ����api��صĿ�����
									//֪ͨ�ѱ���������

	//��selectShowMd���������Ĳۺ���
	void showSelectMdWindow();		//չʾ�Ի�����ʹ����ѡ����ʾ�ĺ�Լ

	//��writeToDB���������Ĳۺ���
	void selectFileForWriter();		//չʾ�Ի�����ʹ����ѡ���ļ�д�����ݿ�
private:
	//ѡ���ĺ��˶�����������Ŀؼ������
	QPushButton *connectButton;
	QPushButton *disconnectButton;
	QLineEdit *subscribeInput;
	QPushButton *subscribeButton;
	QLineEdit *unsubscribeInput;
	QPushButton *unsubscribeButton;

	//״̬���Ŀؼ������
	QLabel *timeLabel;
	QTimer *timerForUpdateTimeLabel;
	QLabel *statusLabel;

	//�Ի���
	SelectShowMdWindow *sMdWindow=nullptr;

	//���
	MdTable *table;

	//�˵���
	QMenu *selectMenu;

	//����
	QAction *selectShowMd;
	QAction *writeToDB;

	//������
	std::shared_ptr<ConnectController> connectController;
	std::shared_ptr<SubscribeController> subController;
	std::shared_ptr<UnsubscribeController> unsubController;
	std::shared_ptr<DBWriterController> dbWriterController;
};