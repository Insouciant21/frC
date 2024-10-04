#include "frC.h"

frC::frC(QWidget *parent) : QMainWindow(parent), ui(new Ui::frCClass()) {
    ui->setupUi(this);
    connect(ui->monoCalc, &QPushButton::clicked, this, &frC::calculateMono);
    connect(ui->binoCalc, &QPushButton::clicked, this, &frC::calculateBino);
    connect(ui->rSpinBoxLeft, &QSpinBox::valueChanged, this, &frC::on_rSpinBoxLeft_valueChanged);
    connect(ui->cSpinBoxLeft, &QSpinBox::valueChanged, this, &frC::on_cSpinBoxLeft_valueChanged);
    connect(ui->rSpinBoxRight, &QSpinBox::valueChanged, this, &frC::on_rSpinBoxRight_valueChanged);
    connect(ui->cSpinBoxRight, &QSpinBox::valueChanged, this, &frC::on_cSpinBoxRight_valueChanged);
    connect(ui->rSpinBoxSelf, &QSpinBox::valueChanged, this, &frC::on_rSpinBoxSelf_valueChanged);
    connect(ui->cSpinBoxSelf, &QSpinBox::valueChanged, this, &frC::on_cSpinBoxSelf_valueChanged);
    connect(ui->leftClear, &QPushButton::clicked, this, &frC::clearLeft);
    connect(ui->rightClear, &QPushButton::clicked, this, &frC::clearRight);
    connect(ui->selfClear, &QPushButton::clicked, this, &frC::clearSelf);
}

frC::~frC() {
    delete ui;
}

void frC::on_cSpinBoxLeft_valueChanged(int value) {
    resizeMatrix(ui->leftInput, ui->rSpinBoxLeft->value(), value);
}

void frC::on_rSpinBoxLeft_valueChanged(int value) {
    resizeMatrix(ui->leftInput, value, ui->cSpinBoxLeft->value());
}

void frC::on_cSpinBoxRight_valueChanged(int value) {
    resizeMatrix(ui->rightInput, ui->rSpinBoxRight->value(), value);
}

void frC::on_rSpinBoxRight_valueChanged(int value) {
    resizeMatrix(ui->rightInput, value, ui->cSpinBoxRight->value());
}

void frC::on_cSpinBoxSelf_valueChanged(int value) {
    resizeMatrix(ui->selfInput, ui->rSpinBoxSelf->value(), value);
}

void frC::on_rSpinBoxSelf_valueChanged(int value) {
    resizeMatrix(ui->selfInput, value, ui->cSpinBoxSelf->value());
}

void frC::resizeMatrix(QTableWidget *tableWidget, int rows, int cols) {
    tableWidget->setRowCount(rows);
    tableWidget->setColumnCount(cols);
}

void frC::clearLeft(bool clicked) {
    ui->leftInput->clearContents();
}

void frC::clearRight(bool clicked) {
    ui->rightInput->clearContents();
}

void frC::clearSelf(bool clicked) {
    ui->selfInput->clearContents();
}

QString toLaTeX(const Matrix &mat) {
    QString latexResult = "\\begin{bmatrix}";
    for (int i = 0; i < mat.getRow(); i++) {
        for (int j = 0; j < mat.getCol(); j++) {
            latexResult += mat[i][j].toLaTeXString();
            latexResult += "&";
        }
        latexResult.removeLast();
        latexResult += "\\\\[8pt]";
    }
    latexResult += "\\end{bmatrix}";
    return latexResult;
}

Matrix pow(Matrix base, BigInt exponent) {
    if (base.getRow() != base.getCol()) throw std::invalid_argument("Invalid power!");
    Matrix result = Matrix::identity(base.getRow());
    while (exponent > 0) {
        if (exponent % 2 == 1) result = result * base;
        base = base * base;
        exponent /= 2;
    }
    return result;
}
// bool networkConnected = false; TO DO

void frC::readInFromTables(QTableWidget *table, Matrix &to) {
    const int r = table->rowCount(), c = table->columnCount();
    to.reSpec(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (table->item(i, j) != nullptr) {
                to[i][j] = Fraction::fromString(table->item(i, j)->text());
            }
            else {
                to[i][j] = Fraction();
            }
        }
    }
}

void frC::showResult(QLabel *resultWindow, const QString &latexResult) {
    const QString szUrl = "https://latex.codecogs.com/svg.image?" + latexResult;
    resultWindow->setText("加载公式中…");
    QUrl url(szUrl);
    QEventLoop loop;
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray jpegData = reply->readAll();
    QPixmap pm(resultWindow->size());
    QSvgRenderer svg_renderer(jpegData);
    pm.fill(Qt::transparent);
    QPainter painter(&pm);
    svg_renderer.setAspectRatioMode(Qt::KeepAspectRatio);
    svg_renderer.render(&painter, pm.rect());
    resultWindow->setPixmap(pm);
}

void frC::calculateBino(bool clicked) {
    Matrix lhs, rhs;
    readInFromTables(ui->leftInput, lhs);
    readInFromTables(ui->rightInput, rhs);
    QString mode = ui->binoMode->currentText();
    if (mode == "加法") showResult(ui->res, toLaTeX(lhs + rhs));
    if (mode == "减法") showResult(ui->res, toLaTeX(lhs - rhs));
    if (mode == "乘法") showResult(ui->res, toLaTeX(lhs * rhs));
}

void frC::calculateMono(bool clicked) {
    Matrix lhs;
    readInFromTables(ui->selfInput, lhs);
    QString mode = ui->monoMode->currentText();
    if (mode == "乘方") {
        bool ok;
        QString power = QInputDialog::getText(this, "输入乘方次数", "乘方次数:", QLineEdit::Normal, "2", &ok);
        if (ok && !power.isEmpty()) {
            showResult(ui->resultSelf, toLaTeX(pow(lhs, BigInt(power))));
        }
    }
    if (mode == "行列式") showResult(ui->resultSelf, lhs.determinant().toLaTeXString());
    if (mode == "转置") showResult(ui->resultSelf, toLaTeX(lhs.transpose()));
    if (mode == "矩阵的逆") showResult(ui->resultSelf, toLaTeX(lhs.inverse()));
}
