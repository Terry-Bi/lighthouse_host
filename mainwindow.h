#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVector>
#include <QPointF>





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();
    void on_refreshButton_clicked();
    void readSerialData();
    void on_tabWidget_currentChanged(int index);
    void on_btnSend_clicked();
    void processBufferedData();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QVector<QPointF> device1Points;
    QVector<QPointF> device2Points;
    QByteArray buffer;
    QTimer *processTimer;
    void setupSerialPortSettings();
    void parseDataPacket(const QByteArray &packet);
    void updatePlot();
};
#endif // MAINWINDOW_H
