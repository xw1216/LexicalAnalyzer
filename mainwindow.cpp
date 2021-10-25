#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    util = new LexAnalyzer();
    on_srcTextEdit_textChanged();
}

MainWindow::~MainWindow()
{
    delete util;
    delete ui;
}


void MainWindow::on_srcHeaderFileBtn_clicked()
{
    QString text = openTextFile(this);
    ui->srcTextEdit->setPlainText(text);
}


void MainWindow::on_srcHeaderSymbolBtn_clicked()
{
    Form * form = new Form();
    form->setLex(this->util);
    form->init();
    form->setAttribute(Qt::WA_DeleteOnClose);
    form->setWindowFlag(Qt::Window, true);
    form->setVisible(true);
    form->show();
}

QString MainWindow::openTextFile(QWidget* widget)
{
    QString curPath = QDir::currentPath();
    QString dialogTitle = "请选择一个类C代码文件";
    QString filter = "文本文件(*.txt);;类C代码(*.c)";
    QString filename = QFileDialog::getOpenFileName(widget, dialogTitle, curPath, filter);
    if(filename.isEmpty()) {
        return QString();
    }
     QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    QTextStream stream(&file);
    stream.setAutoDetectUnicode(true);
    QString text = stream.readAll();
    file.close();
    return text;
}

void MainWindow::setFontPlat(QTableWidgetItem *item, int size, bool isBold)
{
    QFont font = item->font();
    font.setBold(isBold);
    font.setPointSize(size);
    item->setForeground(Qt::black);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setFont(font);
}

void MainWindow::setTableScale(int num) {
    ui->resultTable->clear();
    ui->resultTable->setColumnCount(1);
    ui->resultTable->setColumnWidth(0, 180);
    ui->resultTable->setRowCount(num);
    QTableWidgetItem * item = new QTableWidgetItem("语法单元");
    setFontPlat(item, 11, true);
    ui->resultTable->setHorizontalHeaderItem(0, item);
}

void MainWindow::resetTable()
{
    ui->resultTable->clear();
    ui->resultTable->setColumnCount(0);
    ui->resultTable->setRowCount(0);
}

void MainWindow::fillAnalyTable(QStringList::Iterator iter)
{
    int itemNum = util->getSymbolNum();
    setTableScale(itemNum);
    for(int i = 0; iter != util->getSymbolEnd(); i++, iter++) {
        QTableWidgetItem * item = new QTableWidgetItem(*iter);
        setFontPlat(item, 10, false);
        ui->resultTable->setItem(i, 0, item);
    }
}


void MainWindow::on_resultPreProBtn_clicked()
{
    ui->srcHeaderWarning->clear();
    QString src = ui->srcTextEdit->toPlainText();
    if(src.isEmpty()) {
        QMessageBox::information(this, "非法输入", "输入不能为空",
                                 QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    util->setSrc(src);
    if(util->startPreProcess()) {
        src = util->getSrc();
        ui->srcTextEdit->setPlainText(src);
        ui->resultAnalyAllBtn->setDisabled(false);
    } else {
        ui->srcHeaderWarning->setText(util->getErrorMsg());
    }
}


void MainWindow::on_resultAnalyAllBtn_clicked()
{
    ui->srcHeaderWarning->clear();
    QString src = ui->srcTextEdit->toPlainText();
    util->setSrc(src);
    util->initUtil();
    QStringList::Iterator iter;
    if(util->startLexAnalyze(iter)) {
        fillAnalyTable(iter);
        ui->srcHeaderSymbolBtn->setDisabled(false);
    } else {
        ui->srcHeaderWarning->setText(util->getErrorMsg());
    }
}


void MainWindow::on_srcTextEdit_textChanged()
{
    ui->srcHeaderSymbolBtn->setDisabled(true);
    ui->resultAnalyAllBtn->setDisabled(true);
    resetTable();
}

