#include "research_spreadsheet_tool.h"

// Application headers
#include "lib/ehm_dal/include/database/database.h"
#include "lib/ehm_dal/include/spreadsheet/spreadsheet.h"
#include "lib/ehm_dal/include/tables/abstract_table.h"
#include "lib/ehm_dal/include/tables/table_index.h"

using namespace tools;

ResearchSpreadsheetTool::ResearchSpreadsheetTool() {}

bool ResearchSpreadsheetTool::runPlayersAndNonPlayers()
{
    auto db{ehm_dal::Database()};
    auto model_to_export{db.table(ehm_dal::tables::TableIndex::STAFF).get()};

    ehm_dal::spreadsheet::Spreadsheet sheet(
        QString("%1/%2 - Staff data.%3").arg(folderPath(), fileNamePrefix(), spreadsheetFileType()));

    qInfo() << sheet.file();

    sheet.addHeader(model_to_export);
    sheet.add(model_to_export);

    return sheet.write();
}
