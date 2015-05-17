#include "ex.h"
#include "ui_ex.h"
#include <QMessageBox>
#include <math.h>

Ex::Ex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ex)
{
    ui->setupUi(this);
    ui->ALineEdit->setText(QString::number(1));
    ui->BLineEdit->setText(QString::number(0.05));
}

Ex::~Ex()
{
    delete ui;
}

void Ex::updatePath()
{
    QPainterPath newPath;
    if(ui->ALineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("幅值不能为空!"));
        return;
    }
    if(ui->BLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("指数系数不能为空!"));
        return;
    }

    double A=ui->ALineEdit->text().toDouble();
    double B=ui->BLineEdit->text().toDouble();
    const double min=-277;
    const double max=277;
    const int Num=10000;
    const double distance=(max-min)/Num;
    double x=min;
    double y=A*exp(B*x);
    QPoint original(287,260);
    for(int i=1;i<Num;++i)
    {
        newPath.moveTo(original.x()+x,original.y()-y);
        x+=distance;
        y=A*exp(B*x);
        newPath.lineTo(original.x()+x,original.y()-y);
    }
    path=newPath;
    emit updatePaint();
}

void Ex::on_exBtn_clicked()
{
    updatePath();
}
