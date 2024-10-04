#pragma once

#include "BigInt.h"
#include "Fraction.h"
#include "Matrix.h"
#include "ui_frC.h"

#include <QInputDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPainter>
#include <QSvgRenderer>
#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class frCClass;
};
QT_END_NAMESPACE

class frC : public QMainWindow {
    Q_OBJECT
    void on_rSpinBoxLeft_valueChanged(int value) const;
    void on_cSpinBoxLeft_valueChanged(int value) const;
    void on_rSpinBoxRight_valueChanged(int value) const;
    void on_cSpinBoxRight_valueChanged(int value) const;
    void on_rSpinBoxSelf_valueChanged(int value) const;
    void on_cSpinBoxSelf_valueChanged(int value) const;

    void calculateBino(bool clicked);
    void calculateMono(bool clicked);

    void clearLeft(bool clicked) const;
    void clearRight(bool clicked) const;
    void clearSelf(bool clicked) const;

   public:
    frC(QWidget *parent = nullptr);
    ~frC();
    static void resizeMatrix(QTableWidget *tableWidget, int rows, int cols);
    static void readInFromTables(QTableWidget *table, Matrix &to);
    static void showResult(QLabel *resultWindow, const QString &latexResult);

   private:
    Ui::frCClass *ui;
};
