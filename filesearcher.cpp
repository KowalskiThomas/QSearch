#include "filesearcher.h"

#include "configuration.h"

#include <chrono>

#include <QFileInfo>

int Searcher::count = 0;
QQueue<QString> Searcher::paths;

Searcher::Searcher(QRegularExpression match, QString path)
    : QObject(), match(match), path(path)
{
    count++;
}

Searcher::Searcher(QString match, QString path)
    : QObject(), path(path)
{
    count++;

    auto rx = QStringLiteral("^%1$").arg(match);

    constexpr auto options =
            QRegularExpression::PatternOption::DontCaptureOption |
            (Configuration::caseInsensitive ? QRegularExpression::CaseInsensitiveOption : QRegularExpression::NoPatternOption);
    QRegularExpression regex(rx, options);

    this->match = regex;
}

SearchResult Searcher::manage()
{
    auto dir = QDir(path);
    if (!dir.exists())
    {
        emit finished(SearchResult::DirectoryDoesntExist);
        return SearchResult::DirectoryDoesntExist;
    }
    if (!match.isValid())
    {
        qCritical() << "Invalid regex" << match;
        emit finished(SearchResult::InvalidTerm);
        return SearchResult::InvalidTerm;
    }

    paths.push_back(path);
    results = search();

    while (!paths.isEmpty())
    {
        if(count < MAX_SEARCHERS)
        {
            auto searcher = new Searcher(match, paths.dequeue());
            searchers.push_back(searcher);
            futures.push_back(std::async(std::launch::async, &Searcher::search, searcher));
        }

        int i = 0;
        for(auto& future : futures)
        {
            if (future.valid() && future.wait_for(std::chrono::microseconds(1)) == std::future_status::ready)
            {
                auto results = future.get();
                if (!results.isEmpty())
                {
                    emit newResults(results);
                    // notify(results);
                }

                delete searchers[i];
            }
            i++;
        }
    }

    emit finished(SearchResult::Complete);
    return SearchResult::Complete;
}

QList<QFileInfo> Searcher::search()
{
    QDir dir(path);
    for(auto file : dir.entryInfoList(QDir::Filter::Files))
    {
        if (match.match(file.fileName()).hasMatch())
        {
            results.push_back(file);
        }
    }

    for(auto subDir : dir.entryInfoList(QDir::Filter::Dirs))
    {
        if (subDir.fileName() == "." || subDir.fileName() == "..")
            continue;

        paths.push_back(subDir.absoluteFilePath());
    }

    return results;
}

Searcher::~Searcher()
{
    count--;
}
