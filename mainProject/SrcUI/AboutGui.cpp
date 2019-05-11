#include "AboutGui.h"
#include "ui_AboutGui.h"
#include <QPushButton>

#define qAppDir	   QCoreApplication::applicationDirPath()

AboutGUI::AboutGUI(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::AboutGUI)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("About Us"));
	this->setWindowModality(Qt::ApplicationModal);
	this->setWindowFlags(Qt::SubWindow);
	this->setFixedSize(364,253);

    QPixmap px(QString(qAppDir.append("/Skins/logo.png")));
    ui->label->setPixmap(px);

    connect(ui->pushButton, &QPushButton::clicked, this, &AboutGUI::BtnOnClose);
}

AboutGUI::~AboutGUI()
{

}

void AboutGUI::BtnOnClose()
{
	this->close();
}
