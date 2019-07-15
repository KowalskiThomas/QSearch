#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <QFileSystemModel>
#include <QFile>
#include <QObject>

#include <future>
#include <QRegularExpression>
#include <QQueue>
#include <QDebug>

#include <functional>
#include <vector>

#define MAX_SEARCHERS 32

#include "mainwindow.h"

enum class SearchResult
{
    Complete,
    DirectoryDoesntExist,
    InvalidTerm
};

class Searcher : public QObject
{
    Q_OBJECT

    using NewResultsCallback = std::function<void(QList<QFileInfo>&)>;

    QList<QFileInfo> results;
    QList<Searcher*> searchers;
    std::vector<std::future<QList<QFileInfo>>> futures;

    QRegularExpression match;
    QString path;

    size_t dirCount = 0;
    size_t fileCount = 0;

    static QQueue<QString> paths;

    std::vector<NewResultsCallback> callbacks;

    static int count;

public:
    void addCallback(NewResultsCallback cb)
    {
        callbacks.push_back(cb);
    }

    void notify(QList<QFileInfo> results)
    {
        for(auto& cb : callbacks)
            cb(results);
    }

    Searcher(QRegularExpression match, QString path = "C:/")
        : QObject(), match(match), path(path)
    {
        count++;
    }

    Searcher(QString match, QString path = "C:/")
        : QObject(), path(path)
    {
        count++;

        auto rx = QStringLiteral("^%1$").arg(match);
        QRegularExpression regex(rx, QRegularExpression::PatternOption::DontCaptureOption);
        if (!regex.isValid())
        {
            qCritical() << "Invalid regex" << regex;
            return;
        }
        this->match = regex;
    }

    virtual ~Searcher() override;

    SearchResult manage();
    QList<QFileInfo> search();

signals:
    void newResults(QList<QFileInfo>);
    void finished(SearchResult);
};

#endif // FILESEARCHER_H
