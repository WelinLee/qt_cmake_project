#pragma once

#include <QDialog>

namespace Ui {
  class PluginUpdateUi;
}

class PluginUpdateUi : public QDialog
{
	Q_OBJECT

public:
	PluginUpdateUi(QWidget *parent = Q_NULLPTR);
	~PluginUpdateUi();

private:
    Ui::PluginUpdateUi *ui;
};
