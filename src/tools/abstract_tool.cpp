#include "abstract_tool.h"

// Application headers
#include "lib/ehm_dal/include/settings/settings.h"

using namespace tools;

QString AbstractTool::file_name_prefix_;

AbstractTool::AbstractTool() {}

void AbstractTool::setFileNamePrefix(const QString &text)
{
    file_name_prefix_ = text;
}

QString AbstractTool::folderPath() const
{
    ehm_dal::settings::Settings settings;
    return settings.value(QStringLiteral("output_folder_path")).toString();
}

QString AbstractTool::spreadsheetFileType() const
{
    ehm_dal::settings::Settings settings;
    if (settings.value(QStringLiteral("output_file_format")).toInt() == XLSX)
        return QStringLiteral("xlsx");
    else
        return QStringLiteral("csv");
}
