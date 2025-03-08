#pragma once

// Qt headers
#include <QGroupBox>
class QCheckBox;

namespace tools {
/*!
 * \brief The IndividualToolsWidget class is a user interface for selecting which 
 * tools/reports to run on a per-DB/Sav basis
 */
class IndividualToolsWidget : public QGroupBox
{
public:
    IndividualToolsWidget(QWidget *parent);

    // Run tools
    qint32 run(const QStringList &files);

    // Result flags
    enum RESULT_FLAGS { UNABLE_TO_OPEN_FILE = -999, INVALID_FILE_EXTENSION };

private:
    // Run tools
    qint32 run();

    // Tools checkboxes
    struct ToolItem
    {
        std::unique_ptr<QCheckBox> check_box_;
        std::function<bool()> tool_function_;
    };

    std::vector<ToolItem> tools_;

    // User interface
    void initUi();
};
} // namespace tools
