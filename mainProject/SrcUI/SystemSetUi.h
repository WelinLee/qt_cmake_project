#pragma once

#include <QDialog>

namespace Ui {
  class SystemSetUi;
}

class SystemSetUi : public QDialog
{
	Q_OBJECT

public:
	SystemSetUi(QWidget *parent = Q_NULLPTR);
	~SystemSetUi();

private:
    Ui::SystemSetUi *ui;
};
