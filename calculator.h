#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

enum MathOperator {
    NONE = 0,
    DIVIDE = 1,
    MULTIPLY = 2,
    ADD = 3,
    SUBTRACT = 4,
    MODULO = 5,
    PERCENT = 6
};

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    MathOperator mathOperator = NONE;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void ChangeNumberSign();
    void EqualsButtonPressed();
    void AddMemoryPressed();
    void GetMemoryPressed();
    void SubtractMemoryPressed();
    void AllClear();
    void Delete();
    void DecimalPressed();
};
#endif // CALCULATOR_H
