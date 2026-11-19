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

private slots:
    void on_buttonBox_accepted();

    void on_pushButtonBrowseProjectPath_clicked();

    void on_pushButtonBrowseSourceFilePath_clicked();

private:
    Ui::ProjectSetupDialog *ui;
};

bool checkValidInputs();

#endif // PROJECTSETUPDIALOG_H
