#include "resultsmodel.h"

QMap<ResultsModel::Column, QString> ResultsModel::columns = {
    { ResultsModel::Column::Path, "Path" },
    { ResultsModel::Column::Size, "Size" }
};

ResultsModel::ResultsModel(QObject *parent)
    : QAbstractTableModel(parent), searcher_(nullptr)
{
    qRegisterMetaType<QList<QFileInfo>>("QList<QFileInfo>");
}

void ResultsModel::onResults(QList<QFileInfo> results)
{
    emit layoutAboutToBeChanged();
    results_.append(results);
    emit layoutChanged();
}

void ResultsModel::search(QString match, QString path)
{
    searcher_ = new Searcher(match, path);
    connect(searcher_, &Searcher::newResults, this, &ResultsModel::onResults);
    connect(searcher_, &Searcher::finished, [this](SearchResult res) {
        if (res == SearchResult::Complete)
        {
            qInfo() << "Search complete";
        }
        else if (res == SearchResult::DirectoryDoesntExist)
        {
            qInfo() << "Directory not found";
            emit directoryDoesntExist();
        }
        delete searcher_;
        searcher_ = nullptr;
    });
    f = std::async(std::launch::async, &Searcher::manage, searcher_);
}

bool ResultsModel::searching()
{
    return !!searcher_;
}

Searcher* ResultsModel::searcher()
{
    return searcher_;
}

void ResultsModel::stopSearching()
{
    delete searcher_;
    searcher_ = nullptr;
}

QVariant ResultsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return columns[static_cast<Column>(section)];
}

int ResultsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return results_.count();
}

int ResultsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columns.count();
}

QVariant ResultsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return getDisplayableData(index);

    return QVariant();
}

QString readableSize(qint64 s)
{
    if (s > 1E9)
        return QStringLiteral("%1 GB").arg(static_cast<double>(s) / 1E9, 0, 'f', 2);
    if (s > 1E6)
        return QStringLiteral("%1 MB").arg(static_cast<double>(s) / 1E6, 0, 'f', 2);
    if (s > 1E3)
        return QStringLiteral("%1 KB").arg(static_cast<double>(s) / 1E3, 0, 'f', 2);

    return QStringLiteral("%1 bytes").arg(s);
}

QString ResultsModel::getDisplayableData(const QModelIndex& index) const
{
    auto info = results_[index.row()];
    switch(static_cast<Column>(index.column()))
    {
        case Path:
            return info.absoluteFilePath();
        case Size:
            return readableSize(info.size());
    }

    return "";
}
