#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QTimer>

//QT_CHARTS_USE_NAMESPACE
QT_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialPort = new QSerialPort(this);
    setupSerialPortSettings();

    // 设置图表
    QChart *chart = new QChart();
    chart->setTitle("坐标轨迹");
    chart->createDefaultAxes();

    // 设置X轴和Y轴范围
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 100000);
    axisX->setTitleText("X坐标");
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 100000);
    axisY->setTitleText("Y坐标");
    chart->addAxis(axisY, Qt::AlignLeft);

    // 创建设备1的轨迹系列
    QLineSeries *series1 = new QLineSeries();
    series1->setName("设备1");
    chart->addSeries(series1);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);

    // 创建设备2的轨迹系列
    QLineSeries *series2 = new QLineSeries();
    series2->setName("设备2");
    chart->addSeries(series2);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);

    // 设置图表视图
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartLayout->addWidget(chartView);


    // 连接串口数据接收信号
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readSerialData);

    //追加连接
    connect(ui->btnSend, &QPushButton::clicked,
            this,        &MainWindow::on_btnSend_clicked);


    processTimer = new QTimer(this);
    processTimer->setInterval(50);
    connect(processTimer, &QTimer::timeout,
            this,        &MainWindow::processBufferedData);


}

MainWindow::~MainWindow()
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }
    delete ui;
}

void MainWindow::setupSerialPortSettings()
{
    // 填充波特率选项
    ui->baudRateComboBox->addItem("9600", QSerialPort::Baud9600);
    ui->baudRateComboBox->addItem("115200", QSerialPort::Baud115200);
    ui->baudRateComboBox->setCurrentText("115200");

    // 填充数据位选项
    ui->dataBitsComboBox->addItem("8", QSerialPort::Data8);
    ui->dataBitsComboBox->setCurrentText("8");

    // 填充校验位选项
    ui->parityComboBox->addItem("无", QSerialPort::NoParity);
    ui->parityComboBox->addItem("奇校验", QSerialPort::OddParity);
    ui->parityComboBox->addItem("偶校验", QSerialPort::EvenParity);
    ui->parityComboBox->setCurrentText("无");

    // 填充停止位选项
    ui->stopBitsComboBox->addItem("1", QSerialPort::OneStop);
    ui->stopBitsComboBox->addItem("2", QSerialPort::TwoStop);
    ui->stopBitsComboBox->setCurrentText("1");

    // 填充流控制选项
    ui->flowControlComboBox->addItem("无", QSerialPort::NoFlowControl);
    ui->flowControlComboBox->addItem("硬件", QSerialPort::HardwareControl);
    ui->flowControlComboBox->addItem("软件", QSerialPort::SoftwareControl);
    ui->flowControlComboBox->setCurrentText("无");

    // 刷新串口列表
    on_refreshButton_clicked();
}

void MainWindow::on_refreshButton_clicked()
{
    ui->portNameComboBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->portNameComboBox->addItem(info.portName());
    }
}

void MainWindow::on_connectButton_clicked()
{
    if (serialPort->isOpen()) {
        serialPort->close();
        ui->connectButton->setText("连接");
        ui->statusLabel->setText("串口已断开");
    } else {
        // 设置串口参数
        serialPort->setPortName(ui->portNameComboBox->currentText());
        serialPort->setBaudRate(ui->baudRateComboBox->currentData().toInt());
        serialPort->setDataBits(static_cast<QSerialPort::DataBits>(ui->dataBitsComboBox->currentData().toInt()));
        serialPort->setParity(static_cast<QSerialPort::Parity>(ui->parityComboBox->currentData().toInt()));
        serialPort->setStopBits(static_cast<QSerialPort::StopBits>(ui->stopBitsComboBox->currentData().toInt()));
        serialPort->setFlowControl(static_cast<QSerialPort::FlowControl>(ui->flowControlComboBox->currentData().toInt()));

        // 打开串口
        if (serialPort->open(QIODevice::ReadOnly)) {
            ui->connectButton->setText("断开");
            ui->statusLabel->setText("串口已连接");
        } else {
            QMessageBox::critical(this, "错误", "无法打开串口: " + serialPort->errorString());
            ui->statusLabel->setText("串口连接失败");
        }
    }
}

/* ====================================================================== */
/*                          接收 + 发送                                    */
/* ====================================================================== */

void MainWindow::readSerialData()
{
    buffer.append(serialPort->readAll());          // 只缓存，不处理

    if (!buffer.isEmpty() && !processTimer->isActive())
        processTimer->start();                     // 启动定时器
}

void MainWindow::on_btnSend_clicked()
{
    if (!serialPort->isOpen()) {
        QMessageBox::warning(this, "提示", "请先打开串口");
        return;
    }
    QByteArray data = ui->lineTx->text().toUtf8();
    serialPort->write(data);
    ui->textRx->appendPlainText(QString("TX[%1] %2")
                                    .arg(data.size())
                                    .arg(QString::fromUtf8(data)));
    ui->lineTx->clear();
}

void MainWindow::parseDataPacket(const QByteArray &packet)
{
    // 解析设备ID
    quint8 deviceId = static_cast<quint8>(packet.at(1));

    // 解析X坐标 (3字节)
    quint32 x = ((static_cast<quint8>(packet.at(2)) << 16) |
                 (static_cast<quint8>(packet.at(3)) << 8) |
                 static_cast<quint8>(packet.at(4)));

    // 解析Y坐标 (3字节)
    quint32 y = ((static_cast<quint8>(packet.at(5)) << 16) |
                 (static_cast<quint8>(packet.at(6)) << 8) |
                 static_cast<quint8>(packet.at(7)));

    // 添加到对应设备的点集
    if (deviceId == 0x01) {
        device1Points.append(QPointF(x, y));
    } else if (deviceId == 0x02) {
        device2Points.append(QPointF(x, y));
    }

    // 更新图表
    updatePlot();

    // 在状态栏显示最新数据
    ui->statusLabel->setText(QString("收到数据 - 设备: 0x%1, X: %2, Y: %3").arg(deviceId, 2, 16, QChar('0')).arg(x).arg(y));
}

void MainWindow::processBufferedData()
{
    /* ---------- 1. 每次最多处理 1000 字节，防止卡顿 ---------- */
    const int chunkSize = 1000;
    QByteArray chunk = buffer.left(chunkSize);
    buffer.remove(0, chunk.size());

    /* ---------- 2. 十六进制 + ASCII 显示（可选行数限制） ---------- */
    QString hex = chunk.toHex(' ').toUpper();
    QString ascii;
    for (char c : chunk)
        ascii.append((c >= 32 && c < 127) ? c : '.');

    ui->textRx->appendPlainText(
        QString("RX[%1] %2  |  %3")
            .arg(chunk.size(), 3, 10, QChar(' '))
            .arg(hex, -30)
            .arg(ascii));

    /* ---------- 3. 限制最大行数，防止内存爆炸 ---------- */
    const int maxLines = 1000;
    if (ui->textRx->blockCount() > maxLines)
        ui->textRx->setMaximumBlockCount(maxLines);

    /* ---------- 4. 解析数据包 ---------- */
    int head = chunk.indexOf(0xFA);
    while (head != -1 && chunk.size() > head + 8) {
        if ((quint8)chunk.at(head + 8) == 0xAF) {
            QByteArray packet = chunk.mid(head, 9);
            parseDataPacket(packet);               // 你的原函数
            chunk.remove(0, head + 9);
        } else {
            chunk.remove(0, head + 1);
        }
        head = chunk.indexOf(0xFA);
    }

    /* ---------- 5. 如果还有数据，继续定时；否则停止 ---------- */
    if (!buffer.isEmpty())
        processTimer->start();
    else
        processTimer->stop();
}




void MainWindow::updatePlot()
{

    static int frameSkip = 0;
    if (++frameSkip % 5) return;   // 每 5 次才刷新一次
    // 获取 chart
    QChartView *chartView = qobject_cast<QChartView *>(ui->chartLayout->itemAt(0)->widget());
    if (!chartView) return;
    QChart *chart = chartView->chart();
    if (!chart) return;

    // 获取两个序列
    QLineSeries *series1 = nullptr;
    QLineSeries *series2 = nullptr;
    for (QAbstractSeries *s : chart->series()) {
        if (s->name() == "设备1") series1 = qobject_cast<QLineSeries *>(s);
        if (s->name() == "设备2") series2 = qobject_cast<QLineSeries *>(s);
    }

    // 更新数据
    if (series1) {
        series1->clear();
        series1->append(device1Points);
    }
    if (series2) {
        series2->clear();
        series2->append(device2Points);
    }

    // 合并所有点
    QList<QPointF> allPoints;
    allPoints << device1Points << device2Points;
    if (allPoints.isEmpty()) return;

    // 计算坐标范围
    qreal xMin = allPoints.first().x();
    qreal xMax = xMin;
    qreal yMin = allPoints.first().y();
    qreal yMax = yMin;

    for (const QPointF &p : allPoints) {
        xMin = qMin(xMin, p.x());
        xMax = qMax(xMax, p.x());
        yMin = qMin(yMin, p.y());
        yMax = qMax(yMax, p.y());
    }

    // 留边距
    const qreal margin = 5;
    xMin -= margin;
    xMax += margin;
    yMin -= margin;
    yMax += margin;

    // 获取坐标轴（避免使用废弃接口）
    QList<QAbstractAxis *> axes = chart->axes(Qt::Horizontal);
    if (!axes.isEmpty()) {
        QValueAxis *axisX = qobject_cast<QValueAxis *>(axes.first());
        if (axisX) axisX->setRange(xMin, xMax);
    }

    axes = chart->axes(Qt::Vertical);
    if (!axes.isEmpty()) {
        QValueAxis *axisY = qobject_cast<QValueAxis *>(axes.first());
        if (axisY) axisY->setRange(yMin, yMax);
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 1 && (!device1Points.isEmpty() || !device2Points.isEmpty())) {
        updatePlot();
    }
}
