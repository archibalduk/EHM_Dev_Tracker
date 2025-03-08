#include "control_panel.h"

// Application headers
#include "lib/ehm_dal/include/settings/settings.h"

// Qt headers
#include <QButtonGroup>
#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QStringBuilder>

using namespace app;

/* ======================= */
/*      Control Panel      */
/* ======================= */

ControlPanel::ControlPanel(QWidget *parent)
    : QWidget(parent)
{
    auto layout{new QVBoxLayout(this)};
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(initFileInputUi());
    layout->addWidget(initFileOutputUi());
}

ControlPanel::~ControlPanel()
{
    saveSettings();
}

/* ====================== */
/*      File Dialogs      */
/* ====================== */

bool ControlPanel::selectOutputFolder()
{
    const auto path{QFileDialog::getExistingDirectory(this,
                                                      QStringLiteral("Select output folder"),
                                                      output_folder_path_->text())};

    if (!path.isEmpty())
        output_folder_path_->setText(path);

    return !path.isEmpty();
}

bool ControlPanel::selectSourceFile()
{
    const auto path{QFileDialog::getOpenFileName(this,
                                                 QStringLiteral("Select database or saved game"),
                                                 source_file_path_->text(),
                                                 QStringLiteral("EHM 1 files (*.db *.sav)"))};

    if (!path.isEmpty())
        source_file_path_->setText(path);

    saveSettings();

    return !path.isEmpty();
}

bool ControlPanel::selectSourceFolder()
{
    const auto path{QFileDialog::getExistingDirectory(this,
                                                      QStringLiteral("Select source folder"),
                                                      source_folder_path_->text())};

    if (!path.isEmpty())
        source_folder_path_->setText(path);

    saveSettings();

    return !path.isEmpty();
}

/* ================== */
/*      File I/O      */
/* ================== */

QStringList ControlPanel::files() const
{
    // Source file
    if (source_type_file_->isChecked()) {
        return {source_file_path_->text()};
    }

    // Source folder
    const auto path{source_folder_path_->text()};
    QDir dir(path);
    const auto file_list{
        dir.entryList({QStringLiteral("*.db"), QStringLiteral("*.sav")}, QDir::Files, QDir::Name)};

    QStringList path_list;
    for (const auto &itr : file_list)
        path_list << path % QStringLiteral("/") % itr;

    return path_list;
}

/* ================== */
/*      Settings      */
/* ================== */

void ControlPanel::saveSettings()
{
    ehm_dal::settings::Settings settings;

    // Folder path settings
    settings.setValue(QStringLiteral("output_folder_path"), output_folder_path_->text());
    settings.setValue(QStringLiteral("source_file_path"), source_file_path_->text());
    settings.setValue(QStringLiteral("source_folder_path"), source_folder_path_->text());

    // Radio button settings
    settings.setValue(QStringLiteral("output_file_format"), output_format_group_->checkedId());
    settings.setValue(QStringLiteral("source_type"), source_group_->checkedId());

    settings.writeAll();
}

/* ======================== */
/*      User Interface      */
/* ======================== */

QWidget *ControlPanel::initFileInputUi()
{
    auto widget{new QGroupBox(QStringLiteral("File input"), this)};
    auto layout{new QFormLayout(widget)};

    // Source type
    source_group_ = new QButtonGroup(widget);
    source_type_file_ = new QRadioButton(QStringLiteral("Single file"), this);
    source_type_folder_ = new QRadioButton(QStringLiteral("Multiple files"), this);

    layout->addRow(QStringLiteral("Source type:"),
                   initRadioButtonGroup(source_group_,
                                        source_type_file_,
                                        source_type_folder_,
                                        QStringLiteral("source_type")));

    // File path
    source_file_path_ = new QLineEdit(widget);
    source_file_path_button_ = new QPushButton(QStringLiteral("Select..."), widget);
    QObject::connect(source_file_path_button_,
                     &QPushButton::clicked,
                     this,
                     &ControlPanel::selectSourceFile);
    initFileSelectionWidget(QStringLiteral("Source file:"),
                            layout,
                            source_file_path_,
                            source_file_path_button_);

    // Folder path
    source_folder_path_ = new QLineEdit(widget);
    source_folder_path_button_ = new QPushButton(QStringLiteral("Select..."), widget);
    QObject::connect(source_folder_path_button_,
                     &QPushButton::clicked,
                     this,
                     &ControlPanel::selectSourceFolder);
    initFileSelectionWidget(QStringLiteral("Source folder:"),
                            layout,
                            source_folder_path_,
                            source_folder_path_button_);

    // File/folder path toggle
    QObject::connect(source_type_file_, &QRadioButton::toggled, this, [&](const bool checked) {
        source_file_path_->setEnabled(checked);
        source_file_path_button_->setEnabled(checked);
        source_folder_path_->setDisabled(checked);
        source_folder_path_button_->setDisabled(checked);
    });

    emit source_type_file_->toggled(source_type_file_->isChecked());

    // Settings
    ehm_dal::settings::Settings settings;
    source_file_path_->setText(settings.value(QStringLiteral("source_file_path")).toString());
    source_folder_path_->setText(settings.value(QStringLiteral("source_folder_path")).toString());

    return widget;
}

QWidget *ControlPanel::initFileOutputUi()
{
    auto widget{new QGroupBox(QStringLiteral("File output"), this)};
    auto layout{new QFormLayout(widget)};

    // Output file format
    output_format_group_ = new QButtonGroup(widget);
    output_format_csv_ = new QRadioButton(QStringLiteral("csv"), this);
    output_format_xlsx_ = new QRadioButton(QStringLiteral("xlsx"), this);

    layout->addRow(QStringLiteral("File type:"),
                   initRadioButtonGroup(output_format_group_,
                                        output_format_csv_,
                                        output_format_xlsx_,
                                        QStringLiteral("output_file_format")));

    output_folder_path_ = new QLineEdit(widget);
    output_folder_path_button_ = new QPushButton(QStringLiteral("Select..."), widget);
    QObject::connect(output_folder_path_button_,
                     &QPushButton::clicked,
                     this,
                     &ControlPanel::selectOutputFolder);
    initFileSelectionWidget(QStringLiteral("Output folder:"),
                            layout,
                            output_folder_path_,
                            output_folder_path_button_);

    // Settings
    ehm_dal::settings::Settings settings;
    output_folder_path_->setText(settings.value(QStringLiteral("output_folder_path")).toString());

    return widget;
}

/* ================================ */
/*      User Interface Helpers      */
/* ================================ */

void ControlPanel::initFileSelectionWidget(const QString &title,
                                           QFormLayout *parent_layout,
                                           QLineEdit *path_line_edit,
                                           QPushButton *path_selection_button)
{
    auto container{new QWidget(this)};
    container->setContentsMargins(0, 0, 0, 0);
    auto layout{new QHBoxLayout(container)};
    layout->setContentsMargins(0, 0, 0, 0);

    path_line_edit->setMinimumWidth(PATH_LINE_EDIT_MINIMUM_WIDTH);

    layout->addWidget(path_line_edit);
    layout->addWidget(path_selection_button);
    parent_layout->addRow(title, container);
}

QWidget *ControlPanel::initRadioButtonGroup(QButtonGroup *group,
                                            QRadioButton *button_a,
                                            QRadioButton *button_b,
                                            const QString &settings_key)
{
    auto container{new QWidget(this)};
    container->setContentsMargins(0, 0, 0, 0);
    auto layout{new QHBoxLayout(container)};
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignLeft);

    group->addButton(button_a);
    layout->addWidget(button_a);

    group->addButton(button_b);
    layout->addWidget(button_b);

    ehm_dal::settings::Settings settings;
    const auto selected_id{settings.value(settings_key).toInt()};

    if (selected_id == group->id(button_b))
        button_b->setChecked(true);
    else
        button_a->setChecked(true); // Default to button_a

    return container;
}
