#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>

#include <QList>
#include <QFileInfo>
#include <QLabel>

class ResultsModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::future<void> f;
    int totalResults;

    ResultsModel* resultsModel;

    QLabel* labelCount;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onResults(QList<QFileInfo>& results);

    void test();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
