/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QLabel *label;
    QLabel *label_2;
    QLabel *remaining;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSlider *horizontalSlider;
    QLabel *Hash_label;
    QLineEdit *lineEdit_2;
    QPushButton *stop_button;
    QLabel *calculated_seconds;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 202);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 40, 301, 22));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(320, 40, 71, 22));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 70, 381, 23));
        progressBar->setValue(0);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 0, 181, 31));
        QFont font;
        font.setFamily(QStringLiteral("Source Code Pro"));
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 100, 111, 16));
        remaining = new QLabel(centralWidget);
        remaining->setObjectName(QStringLiteral("remaining"));
        remaining->setGeometry(QRect(120, 100, 111, 16));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 130, 80, 22));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(240, 130, 81, 22));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 180, 381, 16));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(999999999);
        horizontalSlider->setSingleStep(1000000);
        horizontalSlider->setPageStep(10000001);
        horizontalSlider->setValue(0);
        horizontalSlider->setOrientation(Qt::Horizontal);
        Hash_label = new QLabel(centralWidget);
        Hash_label->setObjectName(QStringLiteral("Hash_label"));
        Hash_label->setGeometry(QRect(10, 160, 161, 16));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(240, 100, 151, 20));
        stop_button = new QPushButton(centralWidget);
        stop_button->setObjectName(QStringLiteral("stop_button"));
        stop_button->setGeometry(QRect(330, 130, 61, 22));
        calculated_seconds = new QLabel(centralWidget);
        calculated_seconds->setObjectName(QStringLiteral("calculated_seconds"));
        calculated_seconds->setGeometry(QRect(220, 160, 171, 16));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "File Location...", 0));
        pushButton->setText(QApplication::translate("MainWindow", "...", 0));
        label->setText(QApplication::translate("MainWindow", "Hourglass", 0));
        label_2->setText(QApplication::translate("MainWindow", "Time Remaining:", 0));
        remaining->setText(QApplication::translate("MainWindow", "0 Seconds", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Encrypt", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Decrypt", 0));
        Hash_label->setText(QString());
        lineEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "Seed", 0));
        stop_button->setText(QApplication::translate("MainWindow", "Stop", 0));
        calculated_seconds->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
