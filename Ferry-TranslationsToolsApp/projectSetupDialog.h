#ifndef PROJECTSETUPDIALOG_H
#define PROJECTSETUPDIALOG_H

#include <QDialog>

namespace Ui {
class ProjectSetupDialog;
}

class ProjectSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectSetupDialog(QWidget *parent = nullptr);
    ~ProjectSetupDialog();

private:
    Ui::ProjectSetupDialog *ui;
};

#endif // PROJECTSETUPDIALOG_H
