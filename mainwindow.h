#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QLineEdit>

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
    void on_pushButton2_clicked();

    void on_pushButton0_clicked();

    void on_pushButton1_clicked();

private:
    Ui::MainWindow *ui;

    void init();

    int n;

    bool res;

    bool isValidate(int val, int row, int col);

    std::vector<QLineEdit*> lineEditArr;

    std::vector<int> nums;

    std::vector<std::vector<int>> matrix;

    void solveMatrix(int cur);

    void matrixToLineEdit();

    void LineEditToMatrix();
};
#endif // MAINWINDOW_H
