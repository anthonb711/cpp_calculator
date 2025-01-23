#include "calculator.h"
#include "ui_calculator.h"
#include <cmath>


double calcVal = 0.0;
double memVal = 0.0;

MathOperator mathOperator = NONE;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    // Calls the UI widget named Display
    ui->Display->setText(QString::number(calcVal));

    // Creates arrays of QPushButtons for the indexed number buttons
    QPushButton *numButtons[10];

    // Loops through the number button widgets in the UI and adds them to the array
    for(int i =0; i < 10; ++i){
        QString butName = "NumPushBut_" + QString::number(i);

        // This is how you search for a specfic widgit - Call parent and then findChild cast to the Qt widget type param is search term
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);

        // This calls the SLOT function from .h and connects it to a SIGNAL event which in this case is the release of the button.
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    // Calls the SLOT function from .h and connectes it to a SIGNAL event which in this case is the release of the buttton.
    connect(ui->Divide,     SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply,   SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Add,        SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract,   SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Modulo,     SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Percent,    SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equals,     SIGNAL(released()), this, SLOT(EqualsButtonPressed()));

    connect(ui->SignChange, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->MemAdd,     SIGNAL(released()), this, SLOT(AddMemoryPressed()));
    connect(ui->MemRecall,  SIGNAL(released()), this, SLOT(GetMemoryPressed()));
    connect(ui->MemSub,     SIGNAL(released()), this, SLOT(SubtractMemoryPressed()));
    connect(ui->AllClear,   SIGNAL(released()), this, SLOT(AllClear()));
    connect(ui->Backspace,  SIGNAL(released()), this, SLOT(Delete()));
    connect(ui->Decimal,    SIGNAL(released()), this, SLOT(DecimalPressed()));
}



Calculator::~Calculator()
{
    delete ui;
}


/************************************************************
 * * SLOT NUM PRESSED:
 * Triggered on a number button released event
 ***********************************************************/
void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(displayVal != "0." && ((dblDisplayVal == 0) || (dblDisplayVal == 0.0))){
        ui->Display->setText(butVal);

    } else {
        QString newVal = displayVal + butVal;
        double dbNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dbNewVal, 'g', 16));
    }

}

/************************************************************
 * * MATH BUTTON PRESSED:
 * Triggered on a math opertor button release event
 * Updates mathOperator with user selected operator
 * Displays the operation selected
 ***********************************************************/
void Calculator::MathButtonPressed(){
    mathOperator = NONE;

    // update calcVal with the left hand side of math operator. This happens before the math button pressed signal is handled.
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    // now handle the math button pressed event and store the math operation pressed in butVal
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    // Which math operator was pressed?
    if(butVal == "÷"){
        mathOperator = DIVIDE;

    } else if(butVal == "x"){
        mathOperator = MULTIPLY;

    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){ // Although it is unecessary I am leaving the QString::compare for an example.
        mathOperator = ADD;

    } else if(butVal == "-"){
        mathOperator = SUBTRACT;

    } else if (butVal == "mod"){
        mathOperator = MODULO;

    } else{
        mathOperator = PERCENT;
    }

    //clear the display
    ui->Display->setText(butVal);
}


/************************************************************
 * * SLOT CHANGE NUMBER SIGN:
 * Triggered on change sign button released event
 * Changes the sign of the number in the display
 ***********************************************************/
void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    ui->Display->setText(QString::number((dblDisplayVal * -1), 'g', 16));
}


/************************************************************
 * * EQUALS BUTTON PRESSED:
 * Triggered on Equal button released event
 * Performs the math operation and display solution
 ***********************************************************/
void Calculator::EqualsButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    switch(mathOperator) {
    case 0:
        solution = dblDisplayVal;
        break;

    case 1:
        solution = (calcVal / dblDisplayVal);
        break;
    case 2:
        solution = (calcVal * dblDisplayVal);
        break;
    case 3:
        solution = (calcVal + dblDisplayVal);
        break;
    case 4:
        solution = (calcVal - dblDisplayVal);
        break;
    case 5:
        solution = std::fmod(calcVal, dblDisplayVal);
        break;
    case 6:
        solution = (calcVal * (dblDisplayVal / 100));
        break;
    default:
        break;
    }

    ui->Display->setText(QString::number(solution, 'g', 16));
}


/************************************************************
 * * ADD MEMORY BUTTON PRESSED:
 * Triggered on M+ button released event
 *
 ***********************************************************/
void Calculator::AddMemoryPressed(){

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    memVal = memVal + calcVal;


    ui->Display->setText(QString::number(memVal, 'g', 16));
}


/************************************************************
 * * GET MEMORY BUTTON PRESSED:
 * Triggered on M button released event
 *
 ***********************************************************/
void Calculator::GetMemoryPressed(){
    ui->Display->setText(QString::number(memVal, 'g', 16));
}


/************************************************************
 * * SUBTRACT MEMORY BUTTON PRESSED:
 * Triggered on M- button released event
 *
 ***********************************************************/
void Calculator::SubtractMemoryPressed(){
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    memVal = memVal - calcVal;
    ui->Display->setText(QString::number(memVal, 'g', 16));
}


/************************************************************
 * * CLEAR BUTTON PRESSED:
 * Triggered on AC button released event
 *
 ***********************************************************/
void Calculator::AllClear(){
    calcVal = 0;
    ui->Display->setText(" ");
}

/************************************************************
 * * BACKSPACE BUTTON PRESSED:
 * Triggered on Delete button released event
 *
 ***********************************************************/
void Calculator::Delete(){

    QString displayVal = ui->Display->text();

    displayVal.remove(displayVal.length() - 1, 1);
    ui->Display->setText(displayVal);

}

/************************************************************
 * * DECIMAL BUTTON PRESSED
 * Triggered on Decimal button released event
 *
 ***********************************************************/
void Calculator::DecimalPressed(){

    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0){
        ui->Display->setText("0.");

   }else{
    ui->Display->setText(displayVal + ".");

    }
}

