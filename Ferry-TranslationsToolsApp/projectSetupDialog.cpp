#include "projectSetupDialog.h"
#include "ui_project_setup_dialog.h"

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
