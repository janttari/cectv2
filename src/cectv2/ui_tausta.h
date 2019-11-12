/********************************************************************************
** Form generated from reading UI file 'tausta.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAUSTA_H
#define UI_TAUSTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tausta
{
public:
    QLabel *label;

    void setupUi(QWidget *Tausta)
    {
        if (Tausta->objectName().isEmpty())
            Tausta->setObjectName(QStringLiteral("Tausta"));
        Tausta->resize(400, 300);
        Tausta->setStyleSheet(QStringLiteral("background-color:rgb(42, 160, 170);"));
        label = new QLabel(Tausta);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 150, 181, 19));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu Mono"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("font: 20pt \"Ubuntu Mono\";\n"
"color: rgb(255, 255, 0)"));

        retranslateUi(Tausta);

        QMetaObject::connectSlotsByName(Tausta);
    } // setupUi

    void retranslateUi(QWidget *Tausta)
    {
        Tausta->setWindowTitle(QApplication::translate("Tausta", "Form", nullptr));
        label->setText(QApplication::translate("Tausta", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tausta: public Ui_Tausta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAUSTA_H
