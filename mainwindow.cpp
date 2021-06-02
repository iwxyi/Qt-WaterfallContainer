#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cardQSS = "background: white;"
              "border-radius: 8px;";

//    for (int i = 0; i < 30; i++)
//    {
//        QWidget* w = new QWidget(ui->scrollArea->widget());
//        w->setStyleSheet(cardQSS);
//        w->resize(qrand() % 50 + 100, qrand() % 100 + 20);
//    }

    ui->scrollArea->initFixedChildren();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/// 固定列数
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->scrollArea->setFixedColCount(arg1);
    ui->scrollArea->adjustWidgetPos();
}

/// 添加控件
void MainWindow::on_pushButton_clicked()
{
    // 创建控件
    QWidget* w = new QWidget(ui->scrollArea->widget());
    w->setStyleSheet(cardQSS);
    w->resize(qrand() % 50 + 100, qrand() % 100 + 20);
    w->show();

    // 添加到区域
    ui->scrollArea->addWidget(w);
    ui->scrollArea->scrollToBottom();
}

/// 全部设为相同宽度
void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked()) // 相同宽度
    {
        ui->scrollArea->setAllowDifferentWidth(false);
        ui->scrollArea->resizeWidgetsToEqualWidth();
    }
    else // 随机宽度
    {
        foreach (auto w, ui->scrollArea->getWidgets())
        {
            w->resize(qrand() % 50 + 100, qrand() % 100 + 20);
        }
        ui->scrollArea->setAllowDifferentWidth(true);
    }
    ui->scrollArea->adjustWidgetPos();
}
