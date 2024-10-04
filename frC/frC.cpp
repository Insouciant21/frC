#include "frC.h"

frC::frC(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::frCClass())
{
    ui->setupUi(this);
}

frC::~frC()
{
    delete ui;
}
