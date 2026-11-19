#include "projectSetupDialog.h"
#include "ui_project_setup_dialog.h"
#include "QFileDialog"

ProjectSetupDialog::ProjectSetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProjectSetupDialog)
{
    ui->setupUi(this);
}

ProjectSetupDialog::~ProjectSetupDialog()
{
    delete ui;
}

void ProjectSetupDialog::on_buttonBox_accepted()
{
    if (checkValidInputs()) {
        // TODO: setupProject();
    }
}

bool checkValidInputs() {
    // TODO: check valid data for Project name, Project path, Source file, Source language.
    return false;
}

void ProjectSetupDialog::on_pushButtonBrowseProjectPath_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this);
    if (path != QString("")) {
        ui->lineEditProjectPath->setText(path);
    }
}


void ProjectSetupDialog::on_pushButtonBrowseSourceFilePath_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select a source file"),
        ui->lineEditProjectPath->text(),
        tr("Plain Text files (*.txt);;XML (*.xml);; CSV (*.csv);; JSON (*.json);;"
            " Subtitle files (*.srt);; All files (*)"));
    if (path != QString("")) {
        ui->lineEditSourceFilePath->setText(path);
    }
}

