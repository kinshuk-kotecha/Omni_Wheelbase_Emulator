#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "EmulatorView.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    QTimer *timer = new QTimer();
    Wheelbase *wheelbase = new Wheelbase();
    emulator = new Emulator(timer, scene, wheelbase);
    ui->emulatorView->initialise(scene);
    get_input();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete emulator;
    delete process;
}

void MainWindow::get_input() {
    ui->textBrowser->setText(QString("Welcome to the Omni Wheelbase Emulator\n1. Enter Acceleration Limit\n2. Enter Target(x)\n3. Enter Target(y)\n4. px\n5. py\n6. ix\n7. iy\n8. dx\n9. dy"));
    ui->pushButton->connect(ui->pushButton, SIGNAL (clicked()),this, SLOT (response_submitted()));
}

void MainWindow::response_submitted() {
    QString data = ui->textEdit->toPlainText();
    QStringList strList = data.split(QRegExp("[\n]"),QString::SkipEmptyParts);
    if (strList.length() != 9) {
        ui->textBrowser->setText(QString("ERROR: Please enter the required 9 values"));
        return;
    }
    emulator->set_acc_limit(strList[0].toFloat());
    emulator->set_target((const XYTheta){.x = strList[1].toFloat(),.y = strList[2].toFloat(), .theta = 0});
    emulator->set_pid_gains((const PIDGain){.p.x = strList[3].toFloat(),.p.y = strList[4].toFloat(),.p.theta = 0,
                                            .i.x = strList[5].toFloat(),.i.y = strList[6].toFloat(),.i.theta = 0,
                                            .d.x = strList[7].toFloat(),.d.y = strList[8].toFloat(),.d.theta = 0,});
}
