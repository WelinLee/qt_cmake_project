#pragma once

#include <QMainWindow>
#include <QCloseEvent>
#include <QStackedWidget>

#include "../BaseClass/IBaseWindow.h"
#include "../BaseClass/IPageWindow.h"
#include "Page_Button.h"

class QLabel;
class TitleWidget;
class DefaultPageWidget;
class AboutGUI;
class SystemSetUi;
class PluginUpdateUi;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow, public IBaseWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	virtual void ActiveShow() override;
	virtual void RaiseShow() override;
	virtual void ReSize(int w, int h) override;
	void SetTitleLogo(QString& sMainText, QString& sSubText, QString& sLogoFile);

protected:
	void initWindowStyle();
	void initWidgets();
	void initCustomMenu();
	void showMaxRestore();
	void updateLinkLabel();

protected:
	void slot_QueryLog();
	void slot_ShowUser();
	void slot_ShowMenu();
	void slot_ActionSet();
	void slot_ActionPluginInfo();
	void slot_ActionAboutUs();
	void slot_TurnPage();

protected:
	virtual void  mousePressEvent(QMouseEvent *ev);
	virtual void  mouseReleaseEvent(QMouseEvent *ev);
	virtual void  mouseMoveEvent(QMouseEvent *ev);
	virtual bool  eventFilter(QObject *, QEvent *);
	virtual void  closeEvent(QCloseEvent *);
	virtual bool  nativeEvent(const QByteArray & eventType, void * message, long * result);
	virtual void  timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
	QMap<PageButton*, IPageWindow*> m_mapPageList;
	TitleWidget*         m_mTitleWidget;
	QStackedWidget*      m_mCenterWidget;
	DefaultPageWidget*   m_mDefaultPageWidget;
	
	QString              m_sContextSkin;
	QMenu*               m_mCustomMenu;
	AboutGUI*            m_aboutDlg = nullptr;
	SystemSetUi*         m_systemSetDlg = nullptr;
	PluginUpdateUi*      m_pluginUpdateDlg = nullptr;
	QLabel*              m_lbLinkImg;
	int                  m_iTimerId;

private:
	QString  m_sBackgroundSkin;
	QPoint	 pressedPos;
	bool	 isMousePressed = false;
};
