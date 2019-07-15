#include "resultstableview.h"

#include <QHeaderView>

#include "resultsmodel.h"

ResultsTableView::ResultsTableView(QWidget *parent) : QTableView(parent)
{
    model_ = new ResultsModel(this);
    setModel(model_);

    auto header = horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    header->setSectionResizeMode(0, QHeaderView::ResizeMode::Stretch);
    header->setHighlightSections(false);
}


