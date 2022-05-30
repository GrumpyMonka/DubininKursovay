/********************************************************************************
** Form generated from reading UI file 'diagramview.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAGRAMVIEW_H
#define UI_DIAGRAMVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiagramView
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *DiagramView)
    {
        if (DiagramView->objectName().isEmpty())
            DiagramView->setObjectName(QString::fromUtf8("DiagramView"));
        DiagramView->resize(917, 590);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        DiagramView->setFont(font);
        gridLayout = new QGridLayout(DiagramView);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(DiagramView);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        retranslateUi(DiagramView);

        QMetaObject::connectSlotsByName(DiagramView);
    } // setupUi

    void retranslateUi(QWidget *DiagramView)
    {
        DiagramView->setWindowTitle(QApplication::translate("DiagramView", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiagramView: public Ui_DiagramView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGRAMVIEW_H
