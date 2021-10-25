#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::setLex(LexAnalyzer *ptr)
{
    util = ptr;
}

void Form::init()
{
    reset();
    fillIdTable();
    fillConstantTable();
}

void Form::reset()
{
    ui->symbolTable->clear();
    ui->symbolTable->setColumnCount(0);
    ui->symbolTable->setRowCount(0);
    ui->constantTable->clear();
    ui->constantTable->setColumnCount(0);
    ui->constantTable->setColumnCount(0);
}

void Form::setFontPlat(QTableWidgetItem *item, int size, bool isBold)
{
    QFont font = item->font();
    font.setBold(isBold);
    font.setPointSize(size);
    item->setForeground(Qt::black);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setFont(font);
}

void Form::setTableScale(QTableWidget *item, int coloum, int row)
{
    if(item == nullptr) {
        return;
    }
    item->setColumnCount(coloum);
    item->setRowCount(row);
}

void Form::setIdHeader()
{
    QTableWidgetItem * item = new QTableWidgetItem("标识符");
    setFontPlat(item, 11, true);
    ui->symbolTable->setHorizontalHeaderItem(0, item);
    ui->symbolTable->setColumnWidth(0, 250);
}

void Form::setConstantHeader()
{
    QTableWidgetItem * item = new QTableWidgetItem("数值");
    setFontPlat(item, 11, true);
    ui->constantTable->setHorizontalHeaderItem(0, item);
    item = new QTableWidgetItem("类型");
    setFontPlat(item, 11, true);
    ui->constantTable->setHorizontalHeaderItem(1, item);
    ui->constantTable->setColumnWidth(0, 160);
    ui->constantTable->setColumnWidth(1, 80);
}

void Form::fillIdTable()
{
    setTableScale(ui->symbolTable, 1, util->getIdNum());
    setIdHeader();
    auto iter = util->getIdBegin();
    for(int i = 0; i < util->getIdNum(); i++, iter++) {
        QString name = iter->getValue();
        QTableWidgetItem * item = new QTableWidgetItem(name);
        setFontPlat(item, 10, false);
        ui->symbolTable->setItem(i, 0, item);
    }
}

void Form::fillConstantTable()
{
    setTableScale(ui->constantTable, 2, util->getConstantNum());
    setConstantHeader();
    auto iter = util->getConstantBegin();
    for(int i = 0; i < util->getConstantNum(); i++, iter++) {
        QTableWidgetItem * item = new QTableWidgetItem(iter->getValue());
        setFontPlat(item, 10, false);
        ui->constantTable->setItem(i, 0, item);
        QString name;
        switch (iter->getType()) {
        case LexAnalyzer::SymbolItem::Type::INTEGER: name = "integer"; break;
        case LexAnalyzer::SymbolItem::Type::FLOAT: name = "float"; break;
        case LexAnalyzer::SymbolItem::Type::STRING: name = "string"; break;
        default: break;
        }
        item = new QTableWidgetItem(name);
        setFontPlat(item, 10, false);
        ui->constantTable->setItem(i, 1, item);
    }
}


