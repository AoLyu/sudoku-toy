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
}

// 随机
void MainWindow::on_pushButton0_clicked()
{

    res = false;

    while(!res)
    {
        for(int i = 0; i < nums.size()-1 ; ++i)
        {
            int change =QRandomGenerator::global()->bounded(n-i);
            if(change!=0)
                std::swap(nums[i],nums[i+change]);
        }

        for(int i = 0 ; i < lineEditArr.size(); ++i)
        {
            lineEditArr[i]->setText("");
        }

        findSolution();

        for(int i = 0; i < n * n; ++i)
        {
            int row = i / n;
            int col = i % n;
            int hide =QRandomGenerator::global()->bounded(100);
            if(lineEditArr[i]->text().isEmpty() && (hide & 1) !=0)
            {

                lineEditArr[i]->setText(QString::number(matrix[row][col]));
            }
        }
        findSolution();
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

    findSolution();

    if(res)
    {
        for(int i = 0; i < n * n; ++i)
        {
            int row = i / n;
            int col = i % n;
            if(lineEditArr[i]->text().isEmpty())
            {
                lineEditArr[i]->setText(QString::number(matrix[row][col]));
            }
        }
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
        lineEditArr.push_back(lineEdit);
    }
}

bool MainWindow::isValidate(std::vector<std::vector<int> > &matrix, int row, int col)
{
    int blockRow =  row/2;
    int blockCol = col/3;

    for(int i = blockRow*2 ; i <= row; i++)
    {
        for(int j = blockCol*3 ; j < blockCol*3+3; j++)
        {
            if(i==row && j == col)
                continue;

            if(matrix[i][j] == matrix[row][col])
                return false;
        }
    }

    for(int i = 0 ; i < row ; ++i)
    {
        if(matrix[i][col] == matrix[row][col])
            return false;
    }
    for(int i = 0; i <col ;++i)
    {
        if(matrix[row][i] == matrix[row][col])
            return false;
    }
    if(row == col)
    {
        for(int i = 0 ; i < row ; i++)
        {
            if(matrix[i][i] == matrix[row][col])
                return false;
        }
    }
    if(row + col == n-1)
    {
        for(int i = 0 ; i < row ; i++)
        {
            if(matrix[i][n-i-1] == matrix[row][col])
                return false;
        }
    }
    return true;
}

void MainWindow::solveMatrix(std::vector<std::vector<int> >& matrix, int cur)
{
    if( cur == 36)
    {
        res = true;
        return;
    }

    int row = cur / n;
    int col = cur % n;

    if(matrix[row][col]>0)
    {
        solveMatrix(matrix,cur+1);
    }
    else
    {
        int i = 0;
        for(; i < nums.size() ; ++i )
        {
            matrix[row][col] = nums[i];
            if(isValidate(matrix ,row, col))
            {
                solveMatrix(matrix,cur+1);
                if(res)
                    return;
            }
            matrix[row][col] = 0;
        }

    }


}

void MainWindow::findSolution()
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

    res = false;

    solveMatrix(matrix,0);

}

