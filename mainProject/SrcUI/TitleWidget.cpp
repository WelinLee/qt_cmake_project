#include "TitleWidget.h"
#include "ui_TitleWidget.h"
#include <QCoreApplication>
#include <QSignalMapper>


#define qAppDir	QCoreApplication::applicationDirPath()

// ui->horizontalSpacer->changeSize(0, 0, QSizePolicy::Ignored, QSizePolicy::Ignored);
TitleWidget::TitleWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
	this->initSysButton();
//	this->setFixedHeight(80);
    ui->mainTitle->setAlignment(Qt::AlignCenter);
	skin_name = qAppDir.append("/Skins/SkinTitle.jpg");

    ui->pBtnPage->setHidden(true);
}

TitleWidget::~TitleWidget()
{

}


void TitleWidget::initSysButton()
{
    ui->pBtMaxMin->setHidden(true);

	user_button = new QToolButton();
	querylog_button = new QToolButton();
	menu_button = new QToolButton();
	min_button = new QToolButton();
	close_button = new QToolButton();


    QString sBase = qAppDir.append("/Skins/SysBtnImages/");

	user_button->setFixedSize(27, 22);
	user_button->setIcon(QPixmap(QString(sBase).append("User.png")));
	user_button->setIconSize(QSize(30, 25));
    user_button->setToolTip(QStringLiteral("UserManager"));
	user_button->setStyleSheet("QToolButton{background-color:transparent;}\
		QToolButton:hover{background-color:#90FF69B4; border-radius:2px;}\
		QToolButton:pressed{background-color:#60FF69B4; border-radius:2px;}");

	querylog_button->setFixedSize(27, 22);
	querylog_button->setIcon(QPixmap(QString(sBase).append("DataModify.png")));// .scaled(30, 25));
	querylog_button->setIconSize(QSize(30, 25));
    querylog_button->setToolTip(QStringLiteral("LogQuery"));
	querylog_button->setStyleSheet("QToolButton{background-color:transparent;}\
		QToolButton:hover{background-color:#90FF69B4; border-radius:2px;}\
		QToolButton:pressed{background-color:#60FF69B4; border-radius:2px;}");

	menu_button->setFixedSize(27, 22);			// QRect(4, 4, 20, 16)
	menu_button->setIcon(QPixmap(QString(sBase).append("menu.png")).copy(QRect(4, 4, 20, 16)));// .scaled(42, 33));
	menu_button->setIconSize(QSize(30, 25));
    menu_button->setToolTip(QStringLiteral("Menu"));
	menu_button->setStyleSheet("QToolButton{background-color:transparent;}\
		QToolButton:hover{background-color:#90FF69B4; border-radius:2px;}\
		QToolButton:pressed{background-color:#60FF69B4; border-radius:2px;}");

	min_button->setFixedSize(27, 22);
	min_button->setIcon(QPixmap(QString(sBase).append("min.png")).copy(QRect(7, 4, 15, 16)));
	min_button->setIconSize(QSize(30, 25));
	min_button->setIconSize(QSize(30, 25));
    min_button->setToolTip(QStringLiteral("Minimize"));
	min_button->setStyleSheet("QToolButton{background-color:transparent;}\
		QToolButton:hover{background-color:#90FF69B4; border-radius:2px;}\
		QToolButton:pressed{background-color:#60FF69B4; border-radius:2px;}");

	close_button->setFixedSize(27, 22);
	close_button->setIcon(QPixmap(QString(sBase).append("ClostBtn.png")).copy(QRect(48,0,24,24)));
	close_button->setIconSize(QSize(30, 25));
    close_button->setToolTip(QStringLiteral("Close"));
	close_button->setStyleSheet("QToolButton{background-color:transparent;}\
		QToolButton:hover{background-color:#90FF69B4; border-radius:2px;}\
		QToolButton:pressed{background-color:#60FF69B4; border-radius:2px;}");
	
	QObject::connect(user_button, &QToolButton::clicked, this, &TitleWidget::sig_ShowUser);
	QObject::connect(menu_button, &QToolButton::clicked, this, &TitleWidget::sig_ShowMenu);
	QObject::connect(querylog_button, &QToolButton::clicked, this, &TitleWidget::sig_QueryLog);
	QObject::connect(min_button, &QToolButton::clicked, this, &TitleWidget::sig_ShowMin);
	QObject::connect(close_button, &QToolButton::clicked, this, &TitleWidget::sig_Close);

    ui->hMaxMinBtnLayout->addStretch();
    ui->hMaxMinBtnLayout->addWidget(menu_button, 0, Qt::AlignTop);
    ui->hMaxMinBtnLayout->addWidget(querylog_button, 0, Qt::AlignTop);
    ui->hMaxMinBtnLayout->addWidget(user_button, 0, Qt::AlignTop);

    ui->hMaxMinBtnLayout->addItem(new QSpacerItem(5 /*width*/, 8 /*height*/));	// add space
    ui->hMaxMinBtnLayout->addWidget(min_button, 0, Qt::AlignTop);
    ui->hMaxMinBtnLayout->addWidget(close_button, 0, Qt::AlignTop);
    ui->hMaxMinBtnLayout->setSpacing(1);
    ui->hMaxMinBtnLayout->setContentsMargins(0, 2, 2, 0);
}

void TitleWidget::setTitleLogo(QString& sMainText, QString& sSubText, QString& sLogoFile)
{
    ui->mainTitle->setText(sMainText);
    ui->mainTitle->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

    ui->subTitle->setText(sSubText);
    ui->subTitle->setStyleSheet(QStringLiteral("color: #FFFFFFFF;"));

    ui->LogoIcon->setFrameShape(QFrame::NoFrame);
    ui->LogoIcon->setPixmap(QPixmap(sLogoFile).scaled(60, 58));
    ui->LogoIcon->setFixedSize(QPixmap(sLogoFile).scaled(60, 58).size());
}

void TitleWidget::setMenuButtonRelease(bool bActive)
{
	menu_button->setEnabled(bActive);
	menu_button->update();				//	menu_button->repaint();
}

PageButton* TitleWidget::CreatePageButton(QString& sNameText, QString& sIconPath)
{
	PageButton* tool_button = new PageButton(sIconPath, this);
	tool_button->setText(sNameText);
    ui->hPageBtnLayout->addWidget(tool_button, 0, Qt::AlignBottom);
	return tool_button;
}

void TitleWidget::RemovePageButton(PageButton* tool_button)
{
    int iPos = ui->hPageBtnLayout->indexOf(tool_button);
	if (iPos < 0)
	{
		return;
	}

	tool_button->disconnect();
    ui->hPageBtnLayout->removeWidget(tool_button);
	tool_button->deleteLater();
}

void TitleWidget::slot_UpdateTitleSkin(QString skinFile)
{
	if (skinFile.size() > 0)
	{
		skin_name = skinFile;
		QWidget::update();
	}
}

void TitleWidget::paintEvent(QPaintEvent * event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	painter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(skin_name));
}
