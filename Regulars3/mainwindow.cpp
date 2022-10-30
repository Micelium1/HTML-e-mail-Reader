#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"
#include <QTextStream>
#include "QMessageBox"
#include <QRegularExpression>
#include <QStringList>
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->LinkButton,&QPushButton::clicked,this,&MainWindow::LinkButtonPress);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LinkButtonPress()
{
    QString Filename = QFileDialog::getOpenFileName(this, "Load File", "", "HTML files (*.html)");
    if (Filename.isEmpty()) {
        return;
    }
    QFile File(Filename);
    File.open(QFile::ReadOnly);
    QString StringContent(File.readAll());
    File.close();
    ui->EmailList->clear();
    QRegularExpression Mask("(\\w+@\\w+\\.\\w+)");
    QRegularExpressionMatchIterator It = Mask.globalMatch(StringContent);
    while(It.hasNext())
    {
      ui->EmailList->addItem(It.next().captured());
    }
    return;
}
