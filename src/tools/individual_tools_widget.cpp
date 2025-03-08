#include "individual_tools_widget.h"

// Application headers
#include "lib/ehm_dal/include/database/file_io/database_file_manager.h"
#include "lib/ehm_dal/include/saved_game/file_io/saved_game_file_manager.h"
#include "lib/ehm_dal/include/widgets/dialogs/progress_dialog.h"
#include "src/individual_tools/research_spreadsheet_tool.h"

// Qt headers
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>

using namespace tools;

/* ================================= */
/*      Individual Tools Widget      */
/* ================================= */

IndividualToolsWidget::IndividualToolsWidget(QWidget *parent)
    : QGroupBox(parent)
{
    setTitle(QStringLiteral("Reports"));
    initUi();
}

/* ================== */
/*      File I/O      */
/* ================== */

QString IndividualToolsWidget::fileNameFromPath(const QString &path) const
{
    const auto pos{path.lastIndexOf(QStringLiteral("/"), Qt::CaseInsensitive) + 1};

    if (pos < 0)
        return path;

    QStringView sv(path);
    return path.sliced(pos);
}

/* =================== */
/*      Run Tools      */
/* =================== */

qint32 IndividualToolsWidget::run(const QStringList &files)
{
    auto run_count{0};

    auto progress_dialog{
        std::make_unique<ehm_dal::widgets::ProgressDialog>(QStringLiteral("Generating reports"),
                                                           0,
                                                           static_cast<qint32>(files.size()))};

    for (const auto &itr : files) {
        const auto file_name{fileNameFromPath(itr)};

        qInfo().noquote() << QStringLiteral("Processing: %1").arg(file_name);
        progress_dialog->increment(file_name);

        std::unique_ptr<ehm_dal::file_io::AbstractFileManager> file_manager;

        if (itr.endsWith(QStringLiteral(".db")))
            file_manager = std::make_unique<ehm_dal::file_io::DatabaseFileManager>();
        else if (itr.endsWith(QStringLiteral(".sav")))
            file_manager = std::make_unique<ehm_dal::file_io::SavedGameFileManager>();
        else
            return INVALID_FILE_EXTENSION;

        if (!file_manager->open(itr))
            return UNABLE_TO_OPEN_FILE;

        AbstractTool::setFileNamePrefix(file_name);
        run_count = run();

        file_manager->close(false);
    }

    progress_dialog->complete();
    return run_count;
}

qint32 IndividualToolsWidget::run()
{
    auto run_count{0};

    for (auto &itr : tools_) {
        if (!itr.check_box_->isChecked() || !itr.tool_function_)
            continue;

        itr.tool_function_();

        ++run_count;
    }

    return run_count;
}

/* ======================== */
/*      User Interface      */
/* ======================== */

void IndividualToolsWidget::initUi()
{
    // Checkboxes
    auto layout{new QGridLayout(this)};

    // Research sheet: staff (players & non-players)
    tools_.emplace_back(
        ToolItem(std::make_unique<QCheckBox>(QStringLiteral(
                                                 "Players && non-players research sheet"),
                                             this),
                 [] {
                     ResearchSpreadsheetTool tool;
                     return tool.runPlayersAndNonPlayers();
                 }));

    for (auto &itr : tools_) {
        itr.check_box_->setChecked(true);
        layout->addWidget(itr.check_box_.get());
    }
}
