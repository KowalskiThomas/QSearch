#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H

#include <QObject>
#include <QAbstractTableModel>

#include <future>

#include <QFileInfo>
#include <QList>

#include "filesearcher.h"

class ResultsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Column
    {
        Path = 0,
        Size
    };

    QList<QFileInfo> results_;
    Searcher* searcher_;
    std::future<SearchResult> f;

    static QMap<Column, QString> columns;

public:
    explicit ResultsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void onResults(QList<QFileInfo> results);
    void search(QString match, QString path);
    void stopSearching();
    bool searching();
    Searcher* searcher();

    QString getDisplayableData(const QModelIndex& index) const;

private:
signals:
    void directoryDoesntExist();
};

Q_DECLARE_METATYPE(QList<QFileInfo>)

#endif // RESULTSMODEL_H
