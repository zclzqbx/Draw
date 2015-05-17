#include "nordx.h"
#include "ui_nordx.h"
#include <math.h>
#include <QMessageBox>

NorDx::NorDx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NorDx)
{
    ui->setupUi(this);
    ui->ELineEdit->setText(QString::number(0));
    ui->BLineEdit->setText(QString::number(1));
}

NorDx::~NorDx()
{
    delete ui;
}

void NorDx::on_NordBtn_clicked()
{
    updatePath();
}

void NorDx::updatePath()
{
    QPainterPath newPath;
    if(ui->ELineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("期望不能为空!"));
        return;
    }
    if(ui->BLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("方差不能为空!"));
        return;
    }
    if(fabs(ui->BLineEdit->text().toDouble())<0.0001)
    {
        QMessageBox::information(this,tr("提示"),tr("方差不能为零!"));
        return;
    }

    double E=ui->ELineEdit->text().toDouble();
    double B=ui->BLineEdit->text().toDouble();
    const double min=-277;
    const double max=277;
    const int Num=10000;
    const double pi=3.14159;
    const double distance=(max-min)/Num;
    double x=min;
    double y=300*(1/(sqrt(2*pi)*B))*exp(-(x/50-E)*(x/50-E)/(2*B*B));
    QPoint original(287,260);
    for(int i=1;i<Num;++i)
    {
        newPath.moveTo(original.x()+x,original.y()-y);
        x+=distance;
        y=300*(1/(sqrt(2*pi)*B))*exp(-(x/50-E)*(x/50-E)/(2*B*B));
        newPath.lineTo(original.x()+x,original.y()-y);
    }
    path=newPath;
    emit updatePaint();
}
