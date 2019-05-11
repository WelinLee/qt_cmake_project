/************************************************************************
 *                         default page
 ************************************************************************/
#pragma once

#include "../BaseClass/IPageWindow.h"
#include <QWidget>

namespace Ui {
  class DefaultPageWidget;
}

class DefaultPageWidget : public IPageWindow
{
	Q_OBJECT

public:
	DefaultPageWidget(QWidget *parent);
	~DefaultPageWidget();

	virtual void SetWindowActive(bool bActive) override;

private:
    Ui::DefaultPageWidget *ui;
};
