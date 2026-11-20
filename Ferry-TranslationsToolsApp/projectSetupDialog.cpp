#include "projectSetupDialog.h"
#include "ui_project_setup_dialog.h"
#include "QFileDialog"
#include "QMessageBox"
#include "iostream"
#include "QJsonParseError"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"

ProjectSetupDialog::ProjectSetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProjectSetupDialog)
{
    ui->setupUi(this);
    fillComboBox();
}

ProjectSetupDialog::~ProjectSetupDialog()
{
    delete ui;
}

void ProjectSetupDialog::fillComboBox(){
    QFile languagesJsonFile(":/data/languages.json");
    if (!languagesJsonFile.open(QIODevice::ReadOnly)) {
        std::cerr << "Cannot open /data/languages.json file!" << "\n";
        QMessageBox::warning(this, tr("Error"), tr("Cannot open %1 - %2").arg(languagesJsonFile.fileName(), languagesJsonFile.errorString()));
        return;
    }
    QJsonParseError err;
    const QJsonDocument languagesJsonDoc = QJsonDocument::fromJson(languagesJsonFile.readAll(), &err);
    if (err.error != QJsonParseError::NoError) {
        std::cerr << "Error while parsign json file (/data/languages.json)." << "\n";
        QMessageBox::warning(this, tr("Json Parse Error"), tr("An Error occured when parsing languages.json"));
        return;
    }
    const QJsonArray languagesArray = languagesJsonDoc.array();
    ui->comboBoxSelectSourceLanguage->clear();
    for (const QJsonValue &v : languagesArray) {
        const QJsonObject languageObj = v.toObject();
        QString flag = languageObj.value("flag").toString();
        QString label = languageObj.value("label").toString();
        QString nativeLabel = languageObj.value("native_label").toString();
        QString showText = flag + " " + label;
        if(label != nativeLabel) {
            showText += " (" + nativeLabel + ")";
        }
        ui->comboBoxSelectSourceLanguage->addItem(showText);
    }
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

