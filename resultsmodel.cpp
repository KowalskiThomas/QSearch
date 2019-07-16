#include "resultsmodel.h"
#include "utils.h"

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
    results_.clear();
    emit layoutChanged();

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
    searcher_->cancel();
//    delete searcher_;
//    searcher_ = nullptr;
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

    if (role == Qt::UserRole)
        return QVariant::fromValue(results_[index.row()]);

    return QVariant();
}

QString ResultsModel::getDisplayableData(const QModelIndex& index) const
{
    auto info = results_[index.row()];
    switch(static_cast<Column>(index.column()))
    {
        case Path:
            return info.absoluteFilePath();
        case Size:
            return Utils::readableSize(info.size());
    }

    return "";
}
