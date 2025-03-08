#pragma once

// Qt headers
#include <QWidget>
class QButtonGroup;
class QFormLayout;
class QLineEdit;
class QPushButton;
class QRadioButton;

namespace app {
/*!
 * \brief The ControlPanel class manages application settings and 
 * provides a control panel user interface
 */
class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    ControlPanel(QWidget *parent);
    ~ControlPanel();

    // File i/o
    QStringList files() const;

    // Settings
    void saveSettings();

private:
    // Ui: dimensions
    enum : qint32 { PATH_LINE_EDIT_MINIMUM_WIDTH = 500 };

    // Ui: file input/source
    QWidget *initFileInputUi();

    QButtonGroup *source_group_;
    QRadioButton *source_type_file_;
    QRadioButton *source_type_folder_;

    QPushButton *source_file_path_button_;
    QLineEdit *source_file_path_;

    QPushButton *source_folder_path_button_;
    QLineEdit *source_folder_path_;

    // Ui: file output
    QWidget *initFileOutputUi();

    QPushButton *output_folder_path_button_;
    QLineEdit *output_folder_path_;

    QButtonGroup *output_format_group_;
    QRadioButton *output_format_csv_;
    QRadioButton *output_format_xlsx_;

    // Ui: helpers
    void initFileSelectionWidget(const QString &title,
                                 QFormLayout *parent_layout,
                                 QLineEdit *path_line_edit,
                                 QPushButton *path_selection_button);
    QWidget *initRadioButtonGroup(QButtonGroup *group,
                                  QRadioButton *button_a,
                                  QRadioButton *button_b,
                                  const QString &settings_key);

private slots:
    // File dialogs
    bool selectOutputFolder();
    bool selectSourceFile();
    bool selectSourceFolder();
};
} // namespace app
