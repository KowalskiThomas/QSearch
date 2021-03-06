#ifndef RESULTSTABLEVIEW_H
#define RESULTSTABLEVIEW_H

#include <QObject>
#include <QTableView>
#include <QFileInfo>

class ResultsModel;

class ResultsTableView : public QTableView
{
    Q_OBJECT

    ResultsModel* model_;

public:
    explicit ResultsTableView(QWidget *parent = nullptr);

signals:
    void fileSelected(QFileInfo);

public slots:
};

#endif // RESULTSTABLEVIEW_H
