#ifndef TAUSTA_H
#define TAUSTA_H

#include <QWidget>

namespace Ui {
class Tausta;
}

class Tausta : public QWidget
{
    Q_OBJECT

public:
    explicit Tausta(QWidget *parent = 0);
    ~Tausta();
    void updateLabel(QString label);

private slots:
    void kello();

private:
    Ui::Tausta *ui;
};

#endif // TAUSTA_H
