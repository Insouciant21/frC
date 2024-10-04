#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_frC.h"

QT_BEGIN_NAMESPACE
namespace Ui { class frCClass; };
QT_END_NAMESPACE

class frC : public QMainWindow
{
    Q_OBJECT

public:
    frC(QWidget *parent = nullptr);
    ~frC();

private:
    Ui::frCClass *ui;
};
