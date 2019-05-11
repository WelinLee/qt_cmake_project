#include "SystemSetUi.h"
#include "ui_SystemSetUi.h"

SystemSetUi::SystemSetUi(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SystemSetUi)
{
    ui->setupUi(this);

    this->setWindowTitle(QStringLiteral("System Settings"));
}

SystemSetUi::~SystemSetUi()
{
}
