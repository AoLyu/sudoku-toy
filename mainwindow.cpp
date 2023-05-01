#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , n(6)
    , res(false)
    , matrix(n,std::vector<int>(n,0))
{
    ui->setupUi(this);
    for(int i = 1 ; i <= n; i++)
    {
        nums.push_back(i);
    }

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 清空
void MainWindow::on_pushButton2_clicked()
{
    for(int i = 0 ; i < lineEditArr.size(); ++i)
    {
        lineEditArr[i]->setText("");
    }

    LineEditToMatrix();
}

// 随机
void MainWindow::on_pushButton0_clicked()
{
    for(int i = 0; i < nums.size()-1 ; ++i)
    {
        int change =QRandomGenerator::global()->bounded(n-i);
        if(change!=0)
            std::swap(nums[i],nums[i+change]);
    }

    res = false;

    while(!res)
    {

        for(int i = 0 ; i < lineEditArr.size(); ++i)
        {
            lineEditArr[i]->setText("");
        }

        LineEditToMatrix();

        solveMatrix(0);

        for(int i = 0; i < n ; ++i)
        {
            for(int j = 0 ; j < n ; ++j )
            {
                int hide =QRandomGenerator::global()->bounded(100);
                if((hide & 1) == 1)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        matrixToLineEdit();

        solveMatrix(0);

    }

}

// 求解
void MainWindow::on_pushButton1_clicked()
{
    for(int i = 0; i < nums.size()-1 ; ++i)
    {
        int change =QRandomGenerator::global()->bounded(n-i);
        if(change!=0)
            std::swap(nums[i],nums[i+change]);
    }

    res = false;

    LineEditToMatrix();

    solveMatrix(0);

    if(res)
    {
        matrixToLineEdit();
    }
    else
    {
        QMessageBox::critical(this, tr("错误"), tr("当前数独无解！"));
    }
}

void MainWindow::init()
{
    QRegExp regExp("[1-6]");
    QRegExpValidator* a = new QRegExpValidator(regExp, this);

    for(int i = 0; i<36; ++i)
    {
        QLineEdit* lineEdit = findChild<QLineEdit *>("lineEdit"+QString::number(i));
        lineEdit->setValidator(a);
        lineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        lineEditArr.push_back(lineEdit);
    }
}

bool MainWindow::isValidate(int val, int row, int col)
{
    int blockRow =  row/2;
    int blockCol = col/3;

    for(int i = blockRow*2 ; i < blockRow*2+2; i++)
    {
        for(int j = blockCol*3 ; j < blockCol*3+3; j++)
        {

            if(matrix[i][j] == val)
                return false;
        }
    }

    for(int i = 0 ; i < n ; ++i)
    {
        if(matrix[i][col] == val || matrix[row][i] == val)
            return false;
    }

    if(row == col)
    {
        for(int i = 0 ; i < n ; i++)
        {
            if(matrix[i][i] == val)
                return false;
        }
    }
    if(row + col == n-1)
    {
        for(int i = 0 ; i < n ; i++)
        {
            if(matrix[i][n-i-1] == val)
                return false;
        }
    }
    return true;
}

void MainWindow::solveMatrix(int cur)
{
    if( cur == n*n)
    {
        res = true;
        return;
    }

    int row = cur / n;
    int col = cur % n;

    if(matrix[row][col]>0)
    {
        solveMatrix(cur+1);
    }
    else
    {
        for(int i = 0; i < nums.size() ; ++i )
        {

            if(isValidate(nums[i] ,row, col))
            {
                matrix[row][col] = nums[i];
                solveMatrix(cur+1);
                if(res)
                    return;
                matrix[row][col] = 0;
            }
        }
    }
}

void MainWindow::matrixToLineEdit()
{
    for(int i = 0; i < n * n; ++i)
    {
        int row = i / n;
        int col = i % n;
        if(matrix[row][col] == 0)
            continue;

        lineEditArr[i]->setText(QString::number(matrix[row][col]));
    }
}

void MainWindow::LineEditToMatrix()
{
    for(int i = 0; i < n*n; ++i)
    {
        int row = i / n;
        int col = i % n;
        matrix[row][col] = 0;

        if(lineEditArr[i]->text().isEmpty())
            continue;

        matrix[row][col] = lineEditArr[i]->text().toInt();
    }
}

