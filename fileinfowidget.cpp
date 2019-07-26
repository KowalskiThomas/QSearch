#include "fileinfowidget.h"
#include "ui_fileinfowidget.h"

#include <QDateTime>

#include "utils.h"

FileInfoWidget::FileInfoWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::FileInfoWidget)
{
    ui->setupUi(this);

    connect(this, &FileInfoWidget::fileInfoChanged, this, &FileInfoWidget::onFileInfoChanged);
    onFileInfoChanged();
}

FileInfoWidget::~FileInfoWidget()
{
    delete ui;
}

void FileInfoWidget::resetFileInfo()
{
    fileInfo = QFileInfo();
    emit fileInfoChanged();
}

void FileInfoWidget::setFileInfo(QFileInfo fileInfo)
{
    if (fileInfo == this->fileInfo)
        return;

    this->fileInfo = fileInfo;
    emit fileInfoChanged();
}

void FileInfoWidget::onFileInfoChanged()
{
    if (fileInfo.path().isNull() || fileInfo.path().isEmpty())
    {
        ui->name->setText("");
        ui->createdAt->setText("");
        ui->lastModified->setText("");
        ui->size->setText("");
        return;
    }

    ui->name->setText(fileInfo.fileName());
    ui->createdAt->setText(fileInfo.created().toString());
    ui->lastModified->setText(fileInfo.lastModified().toString());
    ui->size->setText(Utils::readableSize(fileInfo.size()));
}
