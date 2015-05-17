#ifndef EX_H
#define EX_H

#include <QDialog>
#include <QPainterPath>

namespace Ui {
class Ex;
}

class Ex : public QDialog
{
    Q_OBJECT

public:
    explicit Ex(QWidget *parent = 0);
    ~Ex();

    QPainterPath getPath(){return path;}
    void updatePath();

signals:
    void updatePaint();

private slots:
    void on_exBtn_clicked();

private:
    Ui::Ex *ui;
    QPainterPath path;
};

#endif // EX_H
