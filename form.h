#ifndef FORM_H
#define FORM_H

#include <QString>
#include <QWidget>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "lexanalyzer.h"

namespace Ui {
class Form;
}

/**
 * @brief 用于展示标识/常量表的子窗口类
 */
class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

public:
    /**
     * @brief setLex 设置数据源
     * @param ptr 词法分析器指针
     */
    void setLex(LexAnalyzer* ptr);
    /**
     * @brief init 初始化界面
     */
    void init();
    /**
     * @brief reset 重置所有表格
     */
    void reset();

    /**
     * @brief setFontPlat 设置单元格字体
     * @param item 单元格组件指针
     * @param size 字号
     * @param isBold 是否粗体
     */
    void setFontPlat(QTableWidgetItem *item, int size, bool isBold);

    /**
     * @brief setTableScale 设置表格规模
     * @param item 表格组件指针
     * @param coloum 列数
     * @param row 行数
     */
    void setTableScale(QTableWidget* item, int coloum, int row);

    /**
     * @brief setIdHeader 设置标识符表标头
     */
    void setIdHeader();

    /**
     * @brief setConstantHeader 设置常量表标头
     */
    void setConstantHeader();

    /**
     * @brief fillIdTable 填充标识符表
     */
    void fillIdTable();

    /**
     * @brief fillConstantTable 填充常量表
     */
    void fillConstantTable();

private:
    Ui::Form *ui;
    LexAnalyzer* util;
};

#endif // FORM_H
