/********************************************************************************
** Form generated from reading UI file 'outputwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTPUTWIDGET_H
#define UI_OUTPUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutputWidget
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QTextEdit *textEdit_2;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OutputWidget)
    {
        if (OutputWidget->objectName().isEmpty())
            OutputWidget->setObjectName(QString::fromUtf8("OutputWidget"));
        OutputWidget->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        OutputWidget->setFont(font);
        centralwidget = new QWidget(OutputWidget);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(progressBar, 1, 0, 1, 3);

        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setMaximumSize(QSize(16777215, 400));

        gridLayout->addWidget(textEdit_2, 4, 0, 1, 3);

        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setChecked(true);

        gridLayout->addWidget(checkBox_2, 0, 1, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setChecked(true);

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setTabStopWidth(30);

        gridLayout->addWidget(textEdit, 2, 0, 1, 3);

        OutputWidget->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OutputWidget);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        OutputWidget->setMenuBar(menubar);
        statusbar = new QStatusBar(OutputWidget);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OutputWidget->setStatusBar(statusbar);

        retranslateUi(OutputWidget);

        QMetaObject::connectSlotsByName(OutputWidget);
    } // setupUi

    void retranslateUi(QMainWindow *OutputWidget)
    {
        OutputWidget->setWindowTitle(QApplication::translate("OutputWidget", "MainWindow", nullptr));
        checkBox_2->setText(QApplication::translate("OutputWidget", "Default", nullptr));
        checkBox->setText(QApplication::translate("OutputWidget", "XMLHttpRequest", nullptr));
        pushButton->setText(QApplication::translate("OutputWidget", "Execute", nullptr));
        textEdit->setHtml(QApplication::translate("OutputWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:12pt; font-weight:600; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutputWidget: public Ui_OutputWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTPUTWIDGET_H
