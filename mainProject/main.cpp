/************************************************************************
 *                     Application function API
 ************************************************************************/
#include "QSingleApplication.h"
#include "./SrcUI/MainWindow.h"
#include "../libCore/MessageDialog.h"
#include <QCoreApplication>
#include <QDesktopWidget>
#include <QDateTime>
#include <QSettings>
#include <QThread>
#include <QTimer>
#include <QDebug>

#define qAppDir   QCoreApplication::applicationDirPath()
#define sText(x) 	QStringLiteral(x)


/************************************************************************
 *                    read ini file
 ************************************************************************/
typedef struct _STAppCfgParam
{
    QString sMainText;
    QString sSubText;
    QString sLogoFile;
    int iAppWidth;
    int iAppHeight;

    _STAppCfgParam& operator= (const _STAppCfgParam &obj)
    {
        this->sMainText = obj.sMainText;
        this->sSubText = obj.sSubText;
        this->sLogoFile = obj.sLogoFile;
        this->iAppWidth = obj.iAppWidth;
        this->iAppHeight = obj.iAppHeight;
        return *this;
    }

    _STAppCfgParam() : iAppWidth(800), iAppHeight(500)
    {
        sMainText.clear();
        sSubText.clear();
        sLogoFile.clear();
    }
}AppCfgParamDef;

static AppCfgParamDef GetAppCfgParam()
{
    AppCfgParamDef AppSetting;
    QString sCfgFile = qAppDir.append("/CfgFile/AppCfg.ini");
    QSettings settings(sCfgFile, QSettings::Format::IniFormat);
    AppSetting.sMainText = settings.value(QString("GlobalConfig/MainText"), QVariant("")).toString();
    AppSetting.sSubText = settings.value(QString("GlobalConfig/SubText"), QVariant("")).toString();
    AppSetting.iAppWidth = settings.value(QString("GlobalConfig/Width"), QVariant("850")).toInt();
    AppSetting.iAppHeight = settings.value(QString("GlobalConfig/Height"), QVariant("550")).toInt();
    QString sLogo = settings.value(QString("GlobalConfig/LogoFile"), QVariant("")).toString();
    if(sLogo.size() > 0)
    {
        AppSetting.sLogoFile = qAppDir.append(sLogo);
    }
    else
    {
        AppSetting.sLogoFile.clear();
    }
    return AppSetting;
}

static void loadQss(const QString &fileName)
{
    QString path = qAppDir;
    path += "/Skins/";
    path += fileName;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
         QApplication * p = (QApplication*)QApplication::instance();
         if(p)
         {
             p->setStyleSheet(file.readAll().data());
         }
    }
    else qDebug() << "load QSS fail!";
    file.close();
}


/************************************************************************
*                   main interface
************************************************************************/
int main(int argc, char *argv[])
{
	int iRetVal = 0;
	QSingleApplication a(argc, argv);  
	if (a.isRunning())
	{
        MessageDialog::WarningDlg(nullptr, sText("Warning"), sText("The app has been open..."));
		return 0;
	}

	{
        loadQss(QString("MainApp.qss"));
		MainWindow w;
		a.SetBaseWindow(&w);

        AppCfgParamDef AppSetting = GetAppCfgParam();
        w.SetTitleLogo(AppSetting.sMainText, AppSetting.sSubText, AppSetting.sLogoFile);
        w.ReSize(AppSetting.iAppWidth, AppSetting.iAppHeight);
	
        QDesktopWidget *pDesk = QApplication::desktop();
		w.move((pDesk->width() - w.width()) / 2, (pDesk->height() - w.height() - 20) / 2);
		w.show();

		qDebug() << "QTimer::singleShot: " << QDateTime::currentDateTime();
//        QTimer::singleShot(300, Qt::VeryCoarseTimer, &w, &MainWindow::slot_DelayLoadModules);

		iRetVal = a.exec();
	}

	return iRetVal;
}
