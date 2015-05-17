#ifndef NORDX_H
#define NORDX_H

#include <QDialog>
#include <QPainterPath>

namespace Ui {
class NorDx;
}

class NorDx : public QDialog
{
    Q_OBJECT

public:
    explicit NorDx(QWidget *parent = 0);
    ~NorDx();
    QPainterPath getPath(){return path;}
    void updatePath();

signals:
    void updatePaint();

private slots:
    void on_NordBtn_clicked();

private:
    Ui::NorDx *ui;
    QPainterPath path;
};

#endif // NORDX_H
