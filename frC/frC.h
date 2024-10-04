#pragma once

#include "BigInt.h"
#include "Fraction.h"
#include "Matrix.h"
#include "ui_frC.h"

#include <QInputDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtWidgets/QMainWindow>
#include <QSvgRenderer>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
    class frCClass;
};
QT_END_NAMESPACE

class frC : public QMainWindow {
    Q_OBJECT
    void on_rSpinBoxLeft_valueChanged(int value);

    void on_cSpinBoxLeft_valueChanged(int value);

    void on_rSpinBoxRight_valueChanged(int value);

    void on_cSpinBoxRight_valueChanged(int value);

    void on_rSpinBoxSelf_valueChanged(int value);

    void on_cSpinBoxSelf_valueChanged(int value);
    void calculateBino(bool clicked);
    void calculateMono(bool clicked);
    void clearLeft(bool clicked);
    void clearRight(bool clicked);
    void clearSelf(bool clicked);
   public:
    frC(QWidget *parent = nullptr);
    ~frC();



    void resizeMatrix(QTableWidget *tableWidget, int rows, int cols);

   

    void readInFromTables(QTableWidget *table, Matrix &to);

    void showResult(QLabel *resultWindow, const Matrix &result);

    void showResultDeterminant(const Fraction &result);


   private:
    Ui::frCClass *ui;
};
