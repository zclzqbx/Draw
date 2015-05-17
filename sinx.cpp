#include "sinx.h"
#include "ui_sinx.h"
#include <math.h>
#include <QString>
#include <QMessageBox>

SinX::SinX(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SinX)
{
    ui->setupUi(this);
    ui->ALineEdit->setText(QString::number(100));
    ui->TLineEdit->setText(QString::number(50));
    ui->BLineEdit->setText(QString::number(0));
}

SinX::~SinX()
{
    delete ui;
}

void SinX::on_SinBtn_clicked()
{
    updatePath();
}

void SinX::updatePath()
{
    QPainterPath newPath;
    if(ui->ALineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("幅值不能为空!"));
        return;
    }
    if(ui->TLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("周期不能为空!"));
        return;
    }
    if(ui->BLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("相角不能为空!"));
        return;
    }

    double A=ui->ALineEdit->text().toDouble();
    double T=ui->TLineEdit->text().toDouble();
    double B=ui->BLineEdit->text().toDouble();
    const double min=-277;
    const double max=277;
    const int Num=10000;
    const double pi=3.14159;
    const double distance=(max-min)/Num;
    double x=min;
    double y=A*sin((2*pi/T)*x+B);
    QPoint original(287,260);
    for(int i=1;i<Num;++i)
    {
        newPath.moveTo(original.x()+x,original.y()-y);
        x+=distance;
        y=A*sin((2*pi/T)*x+B);
        newPath.lineTo(original.x()+x,original.y()-y);
    }
    path=newPath;
    emit updatePaint();
}
