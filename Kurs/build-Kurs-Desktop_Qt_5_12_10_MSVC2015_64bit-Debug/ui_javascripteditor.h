/********************************************************************************
** Form generated from reading UI file 'javascripteditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JAVASCRIPTEDITOR_H
#define UI_JAVASCRIPTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JavaScriptEditor
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit;
    QTextEdit *textEdit_3;
    QPushButton *pushButton_2;
    QCheckBox *checkBox;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *JavaScriptEditor)
    {
        if (JavaScriptEditor->objectName().isEmpty())
            JavaScriptEditor->setObjectName(QString::fromUtf8("JavaScriptEditor"));
        JavaScriptEditor->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        JavaScriptEditor->setFont(font);
        centralwidget = new QWidget(JavaScriptEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setMaximumSize(QSize(16777215, 60));

        gridLayout->addWidget(textEdit_2, 2, 0, 1, 4);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setTabStopWidth(20);

        gridLayout->addWidget(textEdit, 4, 0, 1, 4);

        textEdit_3 = new QTextEdit(centralwidget);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setMaximumSize(QSize(16777215, 100));

        gridLayout->addWidget(textEdit_3, 6, 0, 1, 4);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 3, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setTristate(false);

        gridLayout->addWidget(checkBox, 3, 2, 1, 1);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 2, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 3, 1, 1);

        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 3, 1, 1, 1);

        checkBox_3 = new QCheckBox(centralwidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 1, 1, 1, 1);

        JavaScriptEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(JavaScriptEditor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        JavaScriptEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(JavaScriptEditor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        JavaScriptEditor->setStatusBar(statusbar);

        retranslateUi(JavaScriptEditor);

        QMetaObject::connectSlotsByName(JavaScriptEditor);
    } // setupUi

    void retranslateUi(QMainWindow *JavaScriptEditor)
    {
        JavaScriptEditor->setWindowTitle(QApplication::translate("JavaScriptEditor", "MainWindow", nullptr));
        label_3->setText(QApplication::translate("JavaScriptEditor", "Input:", nullptr));
        label_2->setText(QApplication::translate("JavaScriptEditor", "Output:", nullptr));
        label->setText(QApplication::translate("JavaScriptEditor", "JavaScript:", nullptr));
        pushButton_2->setText(QApplication::translate("JavaScriptEditor", "Info", nullptr));
        checkBox->setText(QApplication::translate("JavaScriptEditor", "Default", nullptr));
        pushButton_3->setText(QApplication::translate("JavaScriptEditor", "Save", nullptr));
        pushButton->setText(QApplication::translate("JavaScriptEditor", "Test", nullptr));
        checkBox_2->setText(QApplication::translate("JavaScriptEditor", "XMLHttpRequest", nullptr));
        checkBox_3->setText(QApplication::translate("JavaScriptEditor", "FINITE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JavaScriptEditor: public Ui_JavaScriptEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JAVASCRIPTEDITOR_H
