#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableWidget>
#include <QMessageBox>
#include <QMainWindow>
#include <QTableWidgetItem>

#include "form.h"
#include "lexanalyzer.h"

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
    // 所有按钮的回调函数
    void on_srcHeaderFileBtn_clicked();
    void on_srcHeaderSymbolBtn_clicked();
    void on_resultPreProBtn_clicked();
    void on_resultAnalyAllBtn_clicked();
    void on_srcTextEdit_textChanged();

private:
    Ui::MainWindow *ui;
    LexAnalyzer* util = nullptr;

    /**
     * @brief openTextFile 打开指定文件
     * @param widget 父组件
     * @return 文件内容
     */
    static QString openTextFile(QWidget* widget);
    /**
     * @brief initTableHeader 初始为词法分析表格头
     */
    void initTableHeader();
    /**
     * @brief fillAnalyTable 填充词法分析表
     * @param iter 分析结果起始迭代器
     */
    void fillAnalyTable(QStringList::Iterator iter);

    /**
     * @brief setTableScale 设置表格规模
     * @param item 表格组件指针
     * @param coloum 列数
     * @param row 行数
     */
    void setFontPlat(QTableWidgetItem *item, int size, bool isBold);

    /**
     * @brief setTableScale 设置表格规模
     * @param num Token 项数
     */
    void setTableScale(int num);

    /**
     * @brief resetTable 重置表格
     */
    void resetTable();
};
#endif // MAINWINDOW_H
