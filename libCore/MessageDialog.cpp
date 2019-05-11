#include "MessageDialog.h"
#include <QtWidgets>
#include <QFile>

static QMessageBox* g_pWarningMsgBox = nullptr;
static QMessageBox* g_pInfoMsgBox = nullptr;

void MessageDialog::SetStyle(QWidget* pWidget, const QString& sQssFile)
{
    if ((nullptr == pWidget) || (sQssFile.isEmpty()))
        return;

    QFile file(sQssFile);
    if (file.open(QFile::ReadOnly))
    {
        pWidget->setStyleSheet(file.readAll());
        file.close();
    }
}

bool MessageDialog::QuestionDlg(QWidget *parent, const QString& sTitle, const QString& sText)
{
    QPushButton* pYesBtn = nullptr;
    QPushButton* pNoBtn = nullptr;
    QMessageBox questionMsgBox(parent);

    questionMsgBox.setIcon(QMessageBox::Question);
    pYesBtn = questionMsgBox.addButton(QStringLiteral("Confirm"), QMessageBox::ButtonRole::YesRole);
    pYesBtn->setFixedSize(QSize(70, 30));
    pNoBtn = questionMsgBox.addButton(QStringLiteral("Cancel"), QMessageBox::ButtonRole::NoRole);
    pNoBtn->setFixedSize(QSize(70, 30));

    questionMsgBox.setWindowTitle(sTitle);
    questionMsgBox.setText(sText);
    questionMsgBox.exec();

    return pYesBtn == questionMsgBox.clickedButton();
}

ButtonRole MessageDialog::Question_3BtnDlg(QWidget *parent, const QString& sTitle, const QString& sText)
{
    QPushButton* pYesBtn = nullptr;
    QPushButton* pNoBtn = nullptr;
    QPushButton* pCancelBtn = nullptr;

    QMessageBox questionMsgBox(parent);

    questionMsgBox.setIcon(QMessageBox::Question);
    pYesBtn = questionMsgBox.addButton(QStringLiteral("Yes"), QMessageBox::ButtonRole::YesRole);
    pYesBtn->setFixedSize(QSize(50, 30));
    pNoBtn = questionMsgBox.addButton(QStringLiteral("No"), QMessageBox::ButtonRole::NoRole);
    pNoBtn->setFixedSize(QSize(50, 30));
    pCancelBtn = questionMsgBox.addButton(QStringLiteral("Cancel"), QMessageBox::ButtonRole::NoRole);
    pCancelBtn->setFixedSize(QSize(50, 30));

    questionMsgBox.setWindowTitle(sTitle);
    questionMsgBox.setText(sText);
    questionMsgBox.exec();

    ButtonRole iRetVal = enCancel;
    if (pYesBtn == questionMsgBox.clickedButton())
    {
        iRetVal = enYes;
    }
    else if (pNoBtn == questionMsgBox.clickedButton())
    {
        iRetVal = enNo;
    }

    return iRetVal;
}

void MessageDialog::InformationDlg(QWidget *parent, const QString& sTitle, const QString& sText)
{
    QPushButton* pYesBtn = nullptr;
    QMessageBox infoMsgBox(parent);

    infoMsgBox.setIcon(QMessageBox::Information);
    pYesBtn = infoMsgBox.addButton(QStringLiteral("Confirm"), QMessageBox::ButtonRole::YesRole);
    pYesBtn->setFixedSize(QSize(70, 30));
    g_pInfoMsgBox = &infoMsgBox;

    infoMsgBox.setWindowTitle(sTitle);
    infoMsgBox.setText(sText);
    infoMsgBox.exec();
    g_pInfoMsgBox = nullptr;
}

void MessageDialog::WarningDlg(QWidget *parent, const QString& sTitle, const QString& sText)
{
    QPushButton* pYesBtn = nullptr;
    QMessageBox warningMsgBox(parent);

    warningMsgBox.setIcon(QMessageBox::Warning);
    pYesBtn = warningMsgBox.addButton(QStringLiteral("Confirm"), QMessageBox::ButtonRole::YesRole);
    pYesBtn->setFixedSize(QSize(70, 30));
    g_pWarningMsgBox = &warningMsgBox;

    warningMsgBox.setWindowTitle(sTitle);
    warningMsgBox.setText(sText);
    warningMsgBox.exec();

    g_pWarningMsgBox = nullptr;
}

void MessageDialog::CloseWarningDlg()
{
    if (nullptr != g_pWarningMsgBox)
        g_pWarningMsgBox->close();
}

void MessageDialog::CloseInformationDlg()
{
    if (nullptr != g_pInfoMsgBox)
        g_pInfoMsgBox->close();
}
