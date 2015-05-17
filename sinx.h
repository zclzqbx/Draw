#ifndef SINX_H
#define SINX_H

#include <QDialog>
#include <QPainterPath>

namespace Ui {
class SinX;
}

class SinX : public QDialog
{
    Q_OBJECT

public:
    explicit SinX(QWidget *parent = 0);
    ~SinX();
    QPainterPath getPath(){return path;}
    void updatePath();

signals:
    void updatePaint();

private slots:
    void on_SinBtn_clicked();

private:
    Ui::SinX *ui;
    QPainterPath path;
};

#endif // SINX_H
