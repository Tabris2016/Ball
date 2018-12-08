#include "mywidget.h"
#include "ui_mywidget.h"
#include "QVBoxLayout"
#include <QLayout>
#include "glwidget.h"

#include <QFileDialog>   //文件对话框

#include <QDebug>
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget),
    Myglwidget(new glwidget)
{
    ui->setupUi(this);
    QVBoxLayout* mylayout = new QVBoxLayout;
    //Myglwidget->moveToThread(&threadforball);
    //threadforball.start();
    mylayout->addWidget(Myglwidget);
    this->ui->widget->setLayout(mylayout);

}

myWidget::~myWidget()
{
    delete ui;
}

/******************************************************************************
 *                             Btn Events
 *****************************************************************************/
void myWidget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Open","../Ball/resource","STL(*.stl)");
    if(path.isEmpty() == false)
    {
        cout<<"SUCCEFF";
        ui->lineEdit->setText(path);
        QByteArray ba = path.toLocal8Bit();
        const char *cpath = ba.data();
        stlFile readFile;
        isOk = readFile.ReadFile(cpath);
        //QVector<Triangle> triangleList;
        triangleList = readFile.GetTriangleList();

        if(isOk == true)   //读取成功
        {
            cout<<"read successfully";
            Myglwidget->getTriangle(triangleList);
        }
        else
        {
            cout<<"read fail";
        }
    }
    else
    {
        cout<<"文件路径获取失败";
    }
}
