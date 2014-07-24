#include "MainWindow.h"
#include "GVAR.h"
#include "MdTable.h"
#include <qboxlayout.h>
#include <qdatetime.h>
#include <qstring.h>
#include <qstatusbar.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qfiledialog.h>
using std::shared_ptr;
using std::make_shared;


#include <qtablewidget.h>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent){

	//��ʼ�����ӡ��Ͽ���ť
	connectButton = new QPushButton("��������");
	disconnectButton = new QPushButton("�Ͽ�����");
	connect(disconnectButton, SIGNAL(clicked()), this, SLOT(disconnect()));
	disconnectButton->setEnabled(false);
	//һ�����İ�ť
	onekeySubButton = new QPushButton("һ������");
	onekeySubButton->setEnabled(false);
	//��ʼ�����ġ��˶�����
	subscribeInput = new QLineEdit();
	subscribeInput->setEnabled(false);
	subscribeButton = new QPushButton("��������");
	subscribeButton->setEnabled(false);				//��ʼ��ʱ��ť�ǲ��ɰ���
	unsubscribeInput = new QLineEdit();
	unsubscribeInput->setEnabled(false);
	unsubscribeButton = new QPushButton("�˶�����");
	unsubscribeButton->setEnabled(false);
	// ����/�˶���������
	//�����������㡱�Ĳ���
	QHBoxLayout *top1 = new QHBoxLayout();
	top1->addWidget(new QLabel("��Լ����:"));
	subscribeInput->setFixedSize(645, 25);
	top1->addWidget(subscribeInput);
	top1->addWidget(subscribeButton);
	QHBoxLayout *top2 = new QHBoxLayout();
	top2->addWidget(new QLabel("��Լ����:"));
	unsubscribeInput->setFixedSize(645, 25);
	top2->addWidget(unsubscribeInput);
	top2->addWidget(unsubscribeButton);
	QVBoxLayout *top = new QVBoxLayout();
	top->addLayout(top1);
	top->addLayout(top2);

	//���ñ��
	table = new MdTable();
	QVBoxLayout *conLayout = new QVBoxLayout();
	conLayout->addStretch();
	conLayout->addWidget(onekeySubButton);
	conLayout->addWidget(connectButton);
	conLayout->addWidget(disconnectButton);
	QHBoxLayout *down = new QHBoxLayout();		//�·��Ĳ����ɱ������Ӱ�ť��һ�����
	down->addWidget(table);
	down->addLayout(conLayout);
	down->setAlignment(Qt::AlignTop);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(top);
	mainLayout->addLayout(down);

	QWidget *mainW = new QWidget();
	mainW->setLayout(mainLayout);
	setCentralWidget(mainW);

	createStatusBur();	//����״̬��
	createMenu();		//�����˵���
	initController();

	//���ô�������
	setWindowTitle("��������");
}

/************************************˽�к���*******************************************************/

//��ʼ��������
void MainWindow::initController(){
	connectController = make_shared<ConnectController>();
	//���Ӱ�ť�����ӿ���������
	connect(connectButton, SIGNAL(clicked()), connectController.get(), SLOT(connectServer()));
	//���ӿ�������״̬������
	connect(connectController.get(), SIGNAL(connecting()), this, SLOT(statusConnecting()));
	//���ӿ�����֪ͨ����ʧ��
	connect(connectController.get(), SIGNAL(connectFailed()), this, SLOT(statusConnectFailed()));
	//���ӿ�����֪ͨ��½�ɹ�
	connect(connectController.get(), SIGNAL(loginSuccess()), this, SLOT(statusConnectSuccess()));

	unsubController = make_shared<UnsubscribeController>();
	//���Ŀ������밴ť����
	connect(unsubscribeButton, SIGNAL(clicked()), unsubController.get(), SLOT(unsubscribe()));

	subController = make_shared<SubscribeController>();
	//�˶��������밴ť����
	connect(subscribeButton, SIGNAL(clicked()), subController.get(), SLOT(subscribe()));

	//���ݿ�д�������
	dbWriterController = make_shared<DBWriterController>();

	//һ�����Ŀ�����
	onekeySubController = make_shared<OnekeySubsribeController>();
	connect(onekeySubButton, SIGNAL(clicked()), onekeySubController.get(), SLOT(onekeySubscribe()));
}

//����״̬��
void MainWindow::createStatusBur(){
	//����ʱ���ǩ
	timeLabel = new QLabel("");
	timerForUpdateTimeLabel = new QTimer(this);
	connect(timerForUpdateTimeLabel, SIGNAL(timeout()), this, SLOT(updateTime()));
	timerForUpdateTimeLabel->start(1000);
	//��ʼ��״̬��ǩ
	statusLabel = new QLabel(OFFLINE);
	statusBar()->addWidget(statusLabel);
	statusBar()->addPermanentWidget(timeLabel);
}

//�����˵���
void MainWindow::createMenu(){
	//ѡ��˵�
	selectMenu = menuBar()->addMenu("ѡ��");
	selectShowMd = new QAction("չʾ��Լ", this);
	connect(selectShowMd, SIGNAL(triggered()), this, SLOT(showSelectMdWindow()));
	writeToDB = new QAction("д�����ݿ�", this);
	connect(writeToDB, SIGNAL(triggered()), this, SLOT(selectFileForWriter()));
	selectMenu->addAction(selectShowMd);
	selectMenu->addAction(writeToDB);
	//�鿴�˵�
	checkMenu = menuBar()->addMenu("�鿴");
	showSubscribingAction = new QAction("���ڶ���", this);
	connect(showSubscribingAction, SIGNAL(triggered()), this, SLOT(showSubscribing()));
	checkMenu->addAction(showSubscribingAction);
	//�༭�˵�
	editMenu = menuBar()->addMenu("�༭");
	editOnekeyAction = new QAction("һ������", this);
	connect(editOnekeyAction, SIGNAL(triggered()), this, SLOT(showEditOnekeyDialog()));
	editMenu->addAction(editOnekeyAction);
}

/************************************�ۺ���*********************************************************/

//ʱ�̸��±���ʱ��
void MainWindow::updateTime(){
	QTime time = QTime::currentTime();
	QString timeStr = time.toString("hh:mm:ss");
	timeLabel->setText("����ʱ��: " + timeStr);
}

//״̬���Ϊ��������,���Ӱ�ť������
void MainWindow::statusConnecting(){
	statusLabel->setText(CONNECTING);
	connectButton->setEnabled(false);
}

//����ʧ��
void MainWindow::statusConnectFailed(){
	statusLabel->setText(OFFLINE);
	connectController->reset();
	QMessageBox::information(this, "����ʧ��", "��鿴ǰ�û���ַ�Ƿ���ȷ");
	connectButton->setEnabled(true);
}

//���ӳɹ���״̬���Ϊ���ߣ�ʹ�ö��ĺ��˶���ִ��
void MainWindow::statusConnectSuccess(){
	statusLabel->setText(ONLINE);
	//���ö���/�˶�������
	subController->setReceiver(connectController->getReceiver());
	subController->setTextLine(subscribeInput);
	unsubController->setReceiver(connectController->getReceiver());
	unsubController->setTextLine(unsubscribeInput);
	//����һ������
	onekeySubController->setReceiver(connectController->getReceiver());

	//������صĴ��ڲ���
	subscribeButton->setEnabled(true);
	subscribeInput->setEnabled(true);
	unsubscribeButton->setEnabled(true);
	unsubscribeInput->setEnabled(true);
	disconnectButton->setEnabled(true);
	onekeySubButton->setEnabled(true);
}


//�Ͽ�����,��ʼ����api��صĿ�����
//֪ͨ�ѱ���������
void MainWindow::disconnect(){
	//�ø��������ָ�ԭ��״̬��ʹ�ú�̨api�Զ�����
	subController->reset();
	unsubController->reset();
	connectController->reset();
	onekeySubController->reset();
	//������ز���
	subscribeButton->setEnabled(false);
	subscribeInput->clear();
	subscribeInput->setEnabled(false);
	unsubscribeButton->setEnabled(false);
	unsubscribeInput->clear();
	unsubscribeInput->setEnabled(false);
	disconnectButton->setEnabled(false);
	onekeySubButton->setEnabled(false);
	//�����ӿ���������
	connectButton->setEnabled(true);
	//�޸�״̬����ʾ
	statusLabel->setText(OFFLINE);
	//������
	table->resetTable();
	//���Ѷ��ĵ��б����
	if (sMdWindow != nullptr){
		sMdWindow->clearShowedInstru();
	}
}

//չʾ�Ի�����ʹ����ѡ����ʾ�ĺ�Լ
void MainWindow::showSelectMdWindow(){
	if (sMdWindow == nullptr){
		sMdWindow = new SelectShowMdWindow();
		connect(sMdWindow, SIGNAL(showChange(std::set<QString>&)), table, SLOT(updateTableForSelect(std::set<QString>&)));
		connect(unsubscribeButton, SIGNAL(clicked()), table, SLOT(callUnsubUpdateTimer()));
	}
	sMdWindow->showDialog();
}

//չʾ�Ի�����ʹ����ѡ���ļ�д�����ݿ�
void MainWindow::selectFileForWriter(){
	if (connectController->isConnect() == true){
		QMessageBox::information(this, "����", "��Ͽ������ٲ���");
		return;
	}
	else{
		QStringList filenames = QFileDialog::getOpenFileNames(this,"ѡ�������¼","./data","��¼�ļ� (*.csv)");
		if (filenames.isEmpty()){
			return;
		}
		else{
			dbWriterController->readyToWrite(filenames);
		}
	}
}

//չʾ���ڶ��ĵĺ�Լ
void MainWindow::showSubscribing(){
	if (subDialog == nullptr){
		subDialog = new SubscribingDialog();
		subDialog->show();
	}
	else{
		subDialog->showDialog();
	}
}

//չʾ�༭Onekey�����ļ��ĶԻ���
void MainWindow::showEditOnekeyDialog(){
	if (editOnekeyDialog == nullptr){
		editOnekeyDialog = new EditOnekeyDialog();
		editOnekeyDialog->showDialog();
	}
	else{
		editOnekeyDialog->showDialog();
	}
}