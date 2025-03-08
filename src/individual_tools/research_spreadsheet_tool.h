#pragma once

// Qt headers
#include "src/tools/abstract_tool.h"

namespace tools {
class ResearchSpreadsheetTool : public AbstractTool
{
public:
    ResearchSpreadsheetTool();

    bool runPlayersAndNonPlayers();
};
} // namespace tools
