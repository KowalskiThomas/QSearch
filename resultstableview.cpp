#include "resultstableview.h"

#include "resultsmodel.h"

ResultsTableView::ResultsTableView(QWidget *parent) : QTableView(parent)
{
    model_ = new ResultsModel(this);
    setModel(model_);
}


