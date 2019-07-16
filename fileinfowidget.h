#ifndef FILEINFOWIDGET_H
#define FILEINFOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QFileInfo>
#include <QDebug>

namespace Ui
{
class FileInfoWidget;
}

class FileInfoWidget : public QWidget
{
    Q_OBJECT

    Ui::FileInfoWidget* ui;

    QFileInfo fileInfo;

public:
    explicit FileInfoWidget(QWidget *parent = nullptr);

    virtual ~FileInfoWidget() override;

    void resetFileInfo();
    void setFileInfo(QFileInfo info);

signals:
    void fileInfoChanged() const;

private slots:
    void onFileInfoChanged();
};

#endif // FILEINFOWIDGET_H
