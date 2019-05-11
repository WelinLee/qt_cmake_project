/************************************************************************
 *                      �Զ���Ӧ��ͼ�ο�� ����
 *
 *	 ���ڶ������������ʹ�õġ�
 *	    
 *
 ************************************************************************/
#pragma once
#include <QtCore/qglobal.h>
#include <QObject>

#include <functional>
#include <string>
#include <atomic>
using namespace std;

typedef std::function< void(bool, const QByteArray& )> CallBackFunc;

class IBaseWindow //: public QObject
{

public:
	virtual ~IBaseWindow(){}
	virtual void ActiveShow() = 0;
	virtual void RaiseShow() = 0;
	virtual void ReSize(int w, int h) = 0;

};

#define MAINWINDOW  COREUIMGR->GetMainWindow()



