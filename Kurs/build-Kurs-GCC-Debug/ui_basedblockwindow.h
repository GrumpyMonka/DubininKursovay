/********************************************************************************
** Form generated from reading UI file 'basedblockwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEDBLOCKWINDOW_H
#define UI_BASEDBLOCKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasedBlockWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pushButton_4;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QCheckBox *checkBox_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QCheckBox *checkBox;
    QTextEdit *textEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BasedBlockWindow)
    {
        if (BasedBlockWindow->objectName().isEmpty())
            BasedBlockWindow->setObjectName(QString::fromUtf8("BasedBlockWindow"));
        BasedBlockWindow->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        BasedBlockWindow->setFont(font);
        actionOpen = new QAction(BasedBlockWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave = new QAction(BasedBlockWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        centralwidget = new QWidget(BasedBlockWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 2, 1, 1);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 6, 3, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 6, 1, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 4, 1, 1);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 2);

        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 4, 3, 1, 1);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 8, 4, 1, 1);

        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 8, 3, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 4, 1, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setTabStopWidth(30);

        gridLayout->addWidget(textEdit, 7, 1, 1, 4);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 5, 3, 1, 2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 6, 4, 1, 1);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 5, 1, 1, 2);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 4, 3, 1);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 3, 1, 1);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 2, 3, 1, 1);

        BasedBlockWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(BasedBlockWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        BasedBlockWindow->setStatusBar(statusbar);

        retranslateUi(BasedBlockWindow);

        QMetaObject::connectSlotsByName(BasedBlockWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BasedBlockWindow)
    {
        BasedBlockWindow->setWindowTitle(QApplication::translate("BasedBlockWindow", "MainWindow", nullptr));
        actionOpen->setText(QApplication::translate("BasedBlockWindow", "Open Block", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("BasedBlockWindow", "Ctrl+Shift+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("BasedBlockWindow", "Save Block", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("BasedBlockWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        label->setText(QApplication::translate("BasedBlockWindow", "Text label:", nullptr));
        pushButton_4->setText(QApplication::translate("BasedBlockWindow", "Info", nullptr));
        label_6->setText(QApplication::translate("BasedBlockWindow", "Script:", nullptr));
        label_5->setText(QApplication::translate("BasedBlockWindow", "Name Block:", nullptr));
        label_3->setText(QApplication::translate("BasedBlockWindow", "Text lineEdit:", nullptr));
        checkBox_2->setText(QApplication::translate("BasedBlockWindow", "LineEdit", nullptr));
        pushButton_5->setText(QApplication::translate("BasedBlockWindow", "Cancel", nullptr));
        pushButton_6->setText(QApplication::translate("BasedBlockWindow", "OK", nullptr));
        checkBox->setText(QApplication::translate("BasedBlockWindow", "Label", nullptr));
        pushButton->setText(QApplication::translate("BasedBlockWindow", "Test Script", nullptr));
        label_4->setText(QApplication::translate("BasedBlockWindow", "NULL", nullptr));
        pushButton_3->setText(QApplication::translate("BasedBlockWindow", "Set Image", nullptr));
        pushButton_2->setText(QApplication::translate("BasedBlockWindow", "Delete Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BasedBlockWindow: public Ui_BasedBlockWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEDBLOCKWINDOW_H
