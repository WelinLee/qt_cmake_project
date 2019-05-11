#pragma once

#include <QWidget>
#include "Page_Button.h"

namespace Ui {
  class TitleWidget;
}

class TitleWidget : public QWidget
{
	Q_OBJECT

public:
	TitleWidget(QWidget *parent = 0);
	~TitleWidget();

	void initSysButton();
	void setTitleLogo(QString& sMainText, QString& sSubText, QString& sLogoFile);
	void setMenuButtonRelease(bool bActive);

	PageButton* CreatePageButton(QString& sNameText, QString& sIconPath);
	void RemovePageButton(PageButton* tool_button);

signals:
	void sig_ShowUser();
	void sig_ShowMenu();
	void sig_QueryLog();
	void sig_ShowMin();
	void sig_Close();

public slots:
	void slot_UpdateTitleSkin(QString skinFile);

protected:
	virtual void paintEvent(QPaintEvent * event);

private:
    Ui::TitleWidget *ui;
	QToolButton *user_button;
	QToolButton *querylog_button;
	QToolButton *menu_button;
	QToolButton *min_button;
	QToolButton *close_button;		
	QList<PageButton *> button_list;
	QString skin_name;	
};


