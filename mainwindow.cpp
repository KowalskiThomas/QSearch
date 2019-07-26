#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

#include <QDebug>
#include <QDir>
#include <QRegularExpression>
#include <QMessageBox>

#include <functional>

#include "filesearcher.h"
#include "resultsmodel.h"
#include "filterconverter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    totalResults(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labelCount = new QLabel(this);
    ui->statusBar->addPermanentWidget(labelCount);

    resultsModel = qobject_cast<ResultsModel*>(ui->results->model());
    Q_CHECK_PTR(resultsModel);

    ui->path->setText("C:\\");
    ui->term->setText(R"(*.jpg)");

    connect(ui->search, &QPushButton::clicked, [this]() {
        if (!resultsModel->searching())
            resultsModel->search(FilterConverter::convert(ui->term->text()), ui->path->text());
        else
            resultsModel->stopSearching();
    });

    connect(resultsModel, &ResultsModel::layoutChanged, [this]() {
        labelCount->setText(QStringLiteral("%1 results").arg(resultsModel->rowCount()));
    });

    connect(resultsModel, &ResultsModel::directoryDoesntExist, this, [this]() {
        QMessageBox::warning(this, "Error", "Couldn't find directory.");
    }, Qt::ConnectionType::QueuedConnection);

    connect(this, &QMainWindow::destroyed, [this] {
        if (resultsModel->searching())
            resultsModel->stopSearching();
    });

    connect(ui->results, &ResultsTableView::fileSelected, [this](QFileInfo info) {
        ui->widget->setFileInfo(info);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
