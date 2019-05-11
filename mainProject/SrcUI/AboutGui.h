#ifndef ABOUTGUI_H
#define ABOUTGUI_H

#include <QWidget>

namespace Ui {
  class AboutGUI;
}

class AboutGUI : public QWidget
{
	Q_OBJECT

public:
	AboutGUI(QWidget *parent = 0);
	~AboutGUI();

private slots:
	void BtnOnClose();

private:
    Ui::AboutGUI *ui;
};

#endif // ABOUTGUI_H
