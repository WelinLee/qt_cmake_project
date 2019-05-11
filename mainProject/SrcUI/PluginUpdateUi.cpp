#include "PluginUpdateUi.h"
#include "ui_PluginUpdateUi.h"

PluginUpdateUi::PluginUpdateUi(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::PluginUpdateUi)
{
    ui->setupUi(this);

    this->setWindowTitle(QStringLiteral("Plugin Info"));
}

PluginUpdateUi::~PluginUpdateUi()
{
}
