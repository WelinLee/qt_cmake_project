/************************************************************************
 *                              main UI
 ************************************************************************/

#include "MainWindow.h"
#include "TitleWidget.h"
#include "ui_MainWindow.h"
#include "AboutGui.h"
#include "SystemSetUi.h"
#include "PluginUpdateUi.h"
#include "DefaultPageWidget.h"
#include "../libCore/MessageDialog.h"
#include <QtWidgets>
#include <QTimer>
#include <QDebug>

#define qAppDir	   QCoreApplication::applicationDirPath()
#define sText(x)   QStringLiteral(x)

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_mTitleWidget(nullptr), m_mCenterWidget(nullptr), m_mCustomMenu(nullptr)
    , m_mDefaultPageWidget(nullptr), m_lbLinkImg(nullptr), m_iTimerId(0),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	this->initWindowStyle();
	this->initWidgets();
	this->initCustomMenu();
	this->resize(900, 600);
    this->setWindowIcon(QIcon(":/main.ico"));

	m_iTimerId = QObject::startTimer(500);
}

MainWindow::~MainWindow()
{
}

void MainWindow::ActiveShow()
{
	this->showNormal();
	this->activateWindow();
}

void MainWindow::RaiseShow()
{
	this->showNormal();
	this->activateWindow();
	this->raise();
}

void MainWindow::ReSize(int w, int h)
{
	this->resize(w, h);
	this->show();
}

void MainWindow::SetTitleLogo(QString& sMainText, QString& sSubText, QString& sLogoFile)
{
	if ((m_mTitleWidget) && (sMainText.size() > 0) && (sLogoFile.size() > 0))
	{
		m_mTitleWidget->setTitleLogo(sMainText, sSubText, sLogoFile);
	}
}

void MainWindow::initWindowStyle()
{
	//this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	//this->setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
	this->setMouseTracking(true);

	statusBar()->setFixedHeight(26);
	statusBar()->setStyleSheet("QStatusBar {background-color:#7FFFD4;}");	// 7D26CD 66CDAA
    QLabel* pCompany = new QLabel(QStringLiteral("QtCmake"), this);
	pCompany->setStyleSheet("color:#F0030303; font-size:14px; font-weight:bold;");
	statusBar()->addPermanentWidget(pCompany);

    QLabel* m_lbLink = new QLabel(QStringLiteral(" RunStatus:"));
	m_lbLink->setStyleSheet("font-size:14px;");
	m_lbLink->setFixedWidth(75);
	statusBar()->addWidget(m_lbLink);

	m_lbLinkImg = new QLabel();
	m_lbLinkImg->setFixedWidth(26);
	statusBar()->addWidget(m_lbLinkImg);
}

void MainWindow::initWidgets()
{
	m_mTitleWidget = new TitleWidget(this);
    ui->titleWidget->layout()->addWidget(m_mTitleWidget);
    ui->titleWidget->layout()->setContentsMargins(0, 0, 0, 0);

	m_mCenterWidget = new QStackedWidget(this);
    ui->ContainerFrame->layout()->addWidget(m_mCenterWidget);
	m_mDefaultPageWidget = new DefaultPageWidget(this);
	m_mCenterWidget->addWidget(m_mDefaultPageWidget);

    ui->ContainerFrame->installEventFilter(this);
	m_sContextSkin = qAppDir.append("/Skins/SkinContent.jpg");

	QObject::connect(m_mTitleWidget, &TitleWidget::sig_ShowMenu, this, &MainWindow::slot_ShowMenu);
	QObject::connect(m_mTitleWidget, &TitleWidget::sig_QueryLog, this, &MainWindow::slot_QueryLog);
	QObject::connect(m_mTitleWidget, &TitleWidget::sig_ShowUser, this, &MainWindow::slot_ShowUser);
	QObject::connect(m_mTitleWidget, &TitleWidget::sig_ShowMin, this, &MainWindow::showMinimized);
	QObject::connect(m_mTitleWidget, &TitleWidget::sig_Close, this, &MainWindow::close);
}

void MainWindow::initCustomMenu()
{
	if (nullptr != m_mCustomMenu)
	{
		return;
	}
    m_mCustomMenu = new QMenu(tr("CustomMenu"), this);
	QString sPath = qAppDir.append("/Skins/MenuImages/");
	
	m_systemSetDlg = new SystemSetUi;
	QAction* pQASet = new QAction(QIcon(QString(sPath).append("Set.png")),
        QStringLiteral("System Settings..."), this);
	QObject::connect(pQASet, &QAction::triggered, this, &MainWindow::slot_ActionSet);

	m_pluginUpdateDlg = new PluginUpdateUi;
	QAction* pQAUpdate = new QAction(QIcon(QString(sPath).append("Update.png")),
        QStringLiteral("Plugin Info..."), this);
	QObject::connect(pQAUpdate, &QAction::triggered, this, &MainWindow::slot_ActionPluginInfo);

	m_aboutDlg = new AboutGUI;
	QAction* pQAAbout = new QAction(QIcon(QString(sPath).append("AboutUs.png")),
        QStringLiteral("About Us..."), this);
	QObject::connect(pQAAbout, &QAction::triggered, this, &MainWindow::slot_ActionAboutUs);

	QAction* pQAQuit = new QAction(QIcon(QString(sPath).append("Quit.png")),
        QStringLiteral("Quit"), this);
	QObject::connect(pQAQuit, &QAction::triggered, this, &MainWindow::close);

	QList<QAction*> QAList;
	QAList << pQASet << pQAUpdate << pQAAbout << pQAQuit;
	m_mCustomMenu->addActions(QAList);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_iTimerId)
	{
		updateLinkLabel();
	}
}

void MainWindow::updateLinkLabel()
{
	static bool bErrSwap = false;
	static QString sConfirm = qAppDir.append("/Skins/StatusImages/Confirm.png");
	static QString sCancel = qAppDir.append("/Skins/StatusImages/Cancel.png");
	static bool bLinkOK = false;
	if (bLinkOK)
	{
		m_lbLinkImg->setPixmap(QPixmap(sConfirm).scaled(22, 22));
        m_lbLinkImg->setToolTip(QStringLiteral("Linked"));
		bErrSwap = false;
		return;
	}
	else
        m_lbLinkImg->setToolTip(QStringLiteral("Unlink"));

	if (false == bErrSwap)
	{
		m_lbLinkImg->setPixmap(QPixmap(sCancel).scaled(22, 22));
		bErrSwap = true;
	}
	else
	{
		m_lbLinkImg->setPixmap(QPixmap("").scaled(22, 22));
		bErrSwap = false;
	}
}

void MainWindow::showMaxRestore()
{
	if (this->isMaximized())
	{
		this->showNormal();
	}
	else
	{
		this->showMaximized();
	}
}

void MainWindow::slot_QueryLog()
{

}

void MainWindow::slot_ShowUser()
{
	
}

void MainWindow::slot_ShowMenu()
{
	if (m_mCustomMenu)
	{
		m_mTitleWidget->setMenuButtonRelease(false);
		m_mCustomMenu->exec(QCursor::pos());
		m_mTitleWidget->setMenuButtonRelease(true);
	}
}

void MainWindow::slot_ActionSet()
{
	m_systemSetDlg->exec();
}

void MainWindow::slot_ActionPluginInfo()
{
	m_pluginUpdateDlg->exec();
}

void MainWindow::slot_ActionAboutUs()
{
	m_aboutDlg->show();
}

void MainWindow::slot_TurnPage()
{
	PageButton* pageBtn = dynamic_cast<PageButton*>(this->sender());
	bool bContain = m_mapPageList.contains(pageBtn);
	if (true == bContain)
	{
		IPageWindow* pageWindow = m_mapPageList[pageBtn];
		m_mCenterWidget->setCurrentWidget(pageWindow);
	}
	else {
		m_mCenterWidget->setCurrentWidget(m_mDefaultPageWidget);
	}

	for (auto iter = m_mapPageList.begin(); iter != m_mapPageList.end(); iter++)
	{
		bool bActived = (pageBtn == iter.key()) ? true : false;
		iter.key()->setMousePress(bActived);
		(*iter)->SetWindowActive(bActived);
	}
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::LeftButton)
	{
		if (ev->type() == QEvent::MouseButtonPress)
		{
			pressedPos = ev->pos();
			// pressedPos = ev->globalPos() - this->frameGeometry().topLeft(); 
			isMousePressed = true;
		}
        else if (ev->type() == QEvent::MouseButtonDblClick && ev->pos().y() <= ui->titleWidget->height())
		{
			this->showMaxRestore();
		}
	}
//	else if ((Qt::MidButton == ev->button()) || (Qt::RightButton == ev->button()))
//	{
//		if (ev->type() == QEvent::MouseButtonPress)
//		{
//			pressedPos = ev->pos();
//			isMousePressed = true;
//		}
//	}
}
void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
	isMousePressed = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
	if (isMousePressed && this->isMaximized())
	{
		//this->showNormal();
		return;
	}
	if (isMousePressed)
	{
		this->move(ev->globalPos() - pressedPos);
	}
}

bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
    if ((obj == ui->ContainerFrame) && (ev->type() == QEvent::Paint))
	{
        QPainter painter(ui->ContainerFrame);
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::white);
		painter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(m_sContextSkin));
		return true;
	}

	return QMainWindow::eventFilter(obj, ev);
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    bool bYes = MessageDialog::QuestionDlg(this, sText("Information"),
        sText("Confirm to close the software?"));

    if (true == bYes)
    {
		ev->accept();
	}
    else
    {
		ev->ignore();
	}
//	QMainWindow::closeEvent(ev);
}

bool MainWindow::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
//	Q_UNUSED(eventType);
//	const int HIT_BORDER = 10;
//	const MSG *msg = static_cast<MSG*>(message);
//	if (msg->message == WM_NCHITTEST)
//	{
//		long oldRet = *result;
//		*result = HTNOWHERE;
//		int xPos = ((int)(short)LOWORD(msg->lParam)) - this->frameGeometry().x();
//		int yPos = ((int)(short)HIWORD(msg->lParam)) - this->frameGeometry().y();
//		if (xPos > 0 && xPos < HIT_BORDER)
//		{
//			*result = HTLEFT;
//		}
//		if (xPos > (this->width() - HIT_BORDER) && xPos < (this->width() - 0))
//		{
//			*result = HTRIGHT;
//		}
//		if (yPos > 0 && yPos < HIT_BORDER)
//		{
//			*result = HTTOP;
//		}
//		if (yPos > (this->height() - HIT_BORDER) && yPos < (this->height() - 0))
//		{
//			*result = HTBOTTOM;
//		}
//		if (xPos > 0 && xPos < HIT_BORDER && yPos > 0 && yPos < HIT_BORDER)
//		{
//			*result = HTTOPLEFT;
//		}
//		if (xPos > (this->width() - HIT_BORDER) && xPos < (this->width() - 0) && yPos > 0 && yPos < HIT_BORDER)
//		{
//			*result = HTTOPRIGHT;
//		}
//		if (xPos > 0 && xPos < HIT_BORDER && yPos >(this->height() - HIT_BORDER) && yPos < (this->height() - 0))
//		{
//			*result = HTBOTTOMLEFT;
//		}
//		if (xPos > (this->width() - HIT_BORDER) && xPos < (this->width() - 0) && yPos >(this->height() - HIT_BORDER) && yPos < (this->height() - 0))
//		{
//			*result = HTBOTTOMRIGHT;
//		}

//		if (*result == HTNOWHERE)
//		{
//			*result = oldRet;
//			return false;
//		}

//		return true;
//	}
//	return false;
    return false;
}
