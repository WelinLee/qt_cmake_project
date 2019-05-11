#include "DefaultPageWidget.h"
#include "ui_DefaultPageWidget.h"

DefaultPageWidget::DefaultPageWidget(QWidget *parent)
    : IPageWindow(parent),
      ui(new Ui::DefaultPageWidget)
{
    ui->setupUi(this);
    ui->welcome_label->setFrameShape(QFrame::NoFrame);
}

DefaultPageWidget::~DefaultPageWidget()
{
}

void DefaultPageWidget::SetWindowActive(bool bActive)
{

}
