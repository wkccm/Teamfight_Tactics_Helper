#ifndef VERSIONUPDATE_H
#define VERSIONUPDATE_H

#include <QWidget>

namespace Ui {
class VersionUpdate;
}

class VersionUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit VersionUpdate(QWidget *parent = nullptr);
    ~VersionUpdate();

private:
    Ui::VersionUpdate *ui;
};

#endif // VERSIONUPDATE_H
