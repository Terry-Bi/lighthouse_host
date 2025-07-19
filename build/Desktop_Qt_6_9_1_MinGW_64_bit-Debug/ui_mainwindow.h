/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabSerial;
    QVBoxLayout *verticalLayout_Serial;
    QGridLayout *gridLayout;
    QLabel *portNameLabel;
    QComboBox *portNameComboBox;
    QPushButton *refreshButton;
    QLabel *baudRateLabel;
    QComboBox *baudRateComboBox;
    QLabel *dataBitsLabel;
    QComboBox *dataBitsComboBox;
    QLabel *parityLabel;
    QComboBox *parityComboBox;
    QLabel *stopBitsLabel;
    QComboBox *stopBitsComboBox;
    QLabel *flowControlLabel;
    QComboBox *flowControlComboBox;
    QPushButton *connectButton;
    QLabel *statusLabel;
    QLabel *labelRx;
    QPlainTextEdit *textRx;
    QLabel *labelTx;
    QHBoxLayout *horizontalLayout_Tx;
    QLineEdit *lineTx;
    QPushButton *btnSend;
    QWidget *tabChart;
    QVBoxLayout *chartLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabSerial = new QWidget();
        tabSerial->setObjectName("tabSerial");
        verticalLayout_Serial = new QVBoxLayout(tabSerial);
        verticalLayout_Serial->setObjectName("verticalLayout_Serial");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        portNameLabel = new QLabel(tabSerial);
        portNameLabel->setObjectName("portNameLabel");

        gridLayout->addWidget(portNameLabel, 0, 0, 1, 1);

        portNameComboBox = new QComboBox(tabSerial);
        portNameComboBox->setObjectName("portNameComboBox");

        gridLayout->addWidget(portNameComboBox, 0, 1, 1, 1);

        refreshButton = new QPushButton(tabSerial);
        refreshButton->setObjectName("refreshButton");

        gridLayout->addWidget(refreshButton, 0, 2, 1, 1);

        baudRateLabel = new QLabel(tabSerial);
        baudRateLabel->setObjectName("baudRateLabel");

        gridLayout->addWidget(baudRateLabel, 1, 0, 1, 1);

        baudRateComboBox = new QComboBox(tabSerial);
        baudRateComboBox->setObjectName("baudRateComboBox");

        gridLayout->addWidget(baudRateComboBox, 1, 1, 1, 1);

        dataBitsLabel = new QLabel(tabSerial);
        dataBitsLabel->setObjectName("dataBitsLabel");

        gridLayout->addWidget(dataBitsLabel, 2, 0, 1, 1);

        dataBitsComboBox = new QComboBox(tabSerial);
        dataBitsComboBox->setObjectName("dataBitsComboBox");

        gridLayout->addWidget(dataBitsComboBox, 2, 1, 1, 1);

        parityLabel = new QLabel(tabSerial);
        parityLabel->setObjectName("parityLabel");

        gridLayout->addWidget(parityLabel, 3, 0, 1, 1);

        parityComboBox = new QComboBox(tabSerial);
        parityComboBox->setObjectName("parityComboBox");

        gridLayout->addWidget(parityComboBox, 3, 1, 1, 1);

        stopBitsLabel = new QLabel(tabSerial);
        stopBitsLabel->setObjectName("stopBitsLabel");

        gridLayout->addWidget(stopBitsLabel, 4, 0, 1, 1);

        stopBitsComboBox = new QComboBox(tabSerial);
        stopBitsComboBox->setObjectName("stopBitsComboBox");

        gridLayout->addWidget(stopBitsComboBox, 4, 1, 1, 1);

        flowControlLabel = new QLabel(tabSerial);
        flowControlLabel->setObjectName("flowControlLabel");

        gridLayout->addWidget(flowControlLabel, 5, 0, 1, 1);

        flowControlComboBox = new QComboBox(tabSerial);
        flowControlComboBox->setObjectName("flowControlComboBox");

        gridLayout->addWidget(flowControlComboBox, 5, 1, 1, 1);

        connectButton = new QPushButton(tabSerial);
        connectButton->setObjectName("connectButton");

        gridLayout->addWidget(connectButton, 6, 0, 1, 3);

        statusLabel = new QLabel(tabSerial);
        statusLabel->setObjectName("statusLabel");

        gridLayout->addWidget(statusLabel, 7, 0, 1, 3);


        verticalLayout_Serial->addLayout(gridLayout);

        labelRx = new QLabel(tabSerial);
        labelRx->setObjectName("labelRx");

        verticalLayout_Serial->addWidget(labelRx);

        textRx = new QPlainTextEdit(tabSerial);
        textRx->setObjectName("textRx");
        textRx->setReadOnly(true);
        textRx->setMaximumBlockCount(10000);

        verticalLayout_Serial->addWidget(textRx);

        labelTx = new QLabel(tabSerial);
        labelTx->setObjectName("labelTx");

        verticalLayout_Serial->addWidget(labelTx);

        horizontalLayout_Tx = new QHBoxLayout();
        horizontalLayout_Tx->setObjectName("horizontalLayout_Tx");
        lineTx = new QLineEdit(tabSerial);
        lineTx->setObjectName("lineTx");

        horizontalLayout_Tx->addWidget(lineTx);

        btnSend = new QPushButton(tabSerial);
        btnSend->setObjectName("btnSend");

        horizontalLayout_Tx->addWidget(btnSend);


        verticalLayout_Serial->addLayout(horizontalLayout_Tx);

        tabWidget->addTab(tabSerial, QString());
        tabChart = new QWidget();
        tabChart->setObjectName("tabChart");
        chartLayout = new QVBoxLayout(tabChart);
        chartLayout->setObjectName("chartLayout");
        tabWidget->addTab(tabChart, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\346\225\260\346\215\256\345\217\257\350\247\206\345\214\226\344\270\212\344\275\215\346\234\272", nullptr));
        portNameLabel->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\220\215\347\247\260:", nullptr));
        refreshButton->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        baudRateLabel->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207:", nullptr));
        dataBitsLabel->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215:", nullptr));
        parityLabel->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215:", nullptr));
        stopBitsLabel->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215:", nullptr));
        flowControlLabel->setText(QCoreApplication::translate("MainWindow", "\346\265\201\346\216\247\345\210\266:", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\346\234\252\350\277\236\346\216\245", nullptr));
        labelRx->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\345\214\272:", nullptr));
        labelTx->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\214\272:", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSerial), QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabChart), QCoreApplication::translate("MainWindow", "\345\235\220\346\240\207\350\275\250\350\277\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
