#pragma once

#include <QWidget>
#include <QString>

enum ButtonRole{ enNo = 0, enYes, enCancel, };

class  MessageDialog
{
public:
    static void SetStyle(QWidget* pWidget, const QString& sQssFile);
    static bool QuestionDlg(QWidget *parent, const QString& sTitle, const QString& sText);
    static ButtonRole Question_3BtnDlg(QWidget *parent, const QString& sTitle, const QString& sText);
    static void InformationDlg(QWidget *parent, const QString& sTitle, const QString& sText);
    static void WarningDlg(QWidget *parent, const QString& sTitle, const QString& sText);
    static void CloseWarningDlg();
    static void CloseInformationDlg();
};
