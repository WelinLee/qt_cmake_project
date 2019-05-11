/************************************************************************
 *                      自定义基础应用图形框架 基类
 *	 
 *	 
 *	    
 *
 ************************************************************************/
#pragma once
#include <QtCore/qglobal.h>
#include <QWidget>
#include <QString>

class IPageWindow : public QWidget
{
//	Q_OBJECT				// 加入这个Q_OBJECT 需要将此文件添加到工程生成moc文件

public:
	IPageWindow(QWidget *parent) : QWidget(parent){}
	virtual ~IPageWindow(){}

	virtual void SetWindowActive(bool bActive) = 0;

};




