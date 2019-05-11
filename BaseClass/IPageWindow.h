/************************************************************************
 *                      �Զ������Ӧ��ͼ�ο�� ����
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
//	Q_OBJECT				// �������Q_OBJECT ��Ҫ�����ļ���ӵ���������moc�ļ�

public:
	IPageWindow(QWidget *parent) : QWidget(parent){}
	virtual ~IPageWindow(){}

	virtual void SetWindowActive(bool bActive) = 0;

};




