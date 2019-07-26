#include "resultstableview.h"

#include <QHeaderView>
#include <QDesktopServices>

#include "resultsmodel.h"

ResultsTableView::ResultsTableView(QWidget *parent) : QTableView(parent)
{
    model_ = new ResultsModel(this);
    setModel(model_);

    auto header = horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    header->setSectionResizeMode(0, QHeaderView::ResizeMode::Stretch);
    header->setHighlightSections(false);

    setSelectionBehavior(SelectionBehavior::SelectRows);

    connect(this, &QTableView::clicked, [this](const QModelIndex& idx) {
        emit fileSelected(model_->data(idx, Qt::UserRole).value<QFileInfo>());
    });

    connect(this, &QTableView::doubleClicked, [this](const QModelIndex& idx) {
        QFileInfo file = model_->data(idx, Qt::UserRole).value<QFileInfo>();
        auto path = file.absoluteFilePath();
        QDesktopServices::openUrl(path);
    });
}


