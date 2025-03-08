#include "research_spreadsheet_tool.h"

// Application headers
#include "lib/ehm_dal/include/database/column_data/staff/player_data_columns.h"
#include "lib/ehm_dal/include/database/column_data/staff_columns.h"
#include "lib/ehm_dal/include/database/database.h"
#include "lib/ehm_dal/include/spreadsheet/spreadsheet.h"
#include "lib/ehm_dal/include/tables/abstract_table.h"
#include "lib/ehm_dal/include/tables/table_index.h"

using namespace tools;
using namespace ehm_dal::column_data;

ResearchSpreadsheetTool::ResearchSpreadsheetTool() {}

bool ResearchSpreadsheetTool::runPlayersAndNonPlayers()
{
    auto db{ehm_dal::Database()};
    auto staff{db.table(ehm_dal::tables::TableIndex::STAFF).get()};
    auto players{db.table(ehm_dal::tables::TableIndex::PLAYER_DATA).get()};

    ehm_dal::spreadsheet::Spreadsheet sheet(
        QString("%1/%2 - Staff.%3").arg(folderPath(), fileNamePrefix(), spreadsheetFileType()));

    qInfo() << sheet.file();

    // Column data
    const std::vector<qint32> staff_columns{-1,
                                            StaffColumns::FirstName,
                                            StaffColumns::SecondName,
                                            StaffColumns::DateOfBirth,
                                            StaffColumns::Nation,
                                            StaffColumns::SecondNation,
                                            StaffColumns::DeclaredNation,
                                            StaffColumns::Birthplace,
                                            StaffColumns::Classification,
                                            StaffColumns::JobForClub,
                                            StaffColumns::ClubContracted,
                                            StaffColumns::ClubPlaying,
                                            StaffColumns::DateJoinedClub,
                                            StaffColumns::ContractExpiresClub,
                                            StaffColumns::EstimatedWage,
                                            StaffColumns::EstimatedWageWeekly,
                                            StaffColumns::EstimatedValue,
                                            StaffColumns::JobForNation,
                                            StaffColumns::NationContracted,
                                            StaffColumns::DateJoinedNation,
                                            StaffColumns::ContractExpiresNation,
                                            StaffColumns::InternationalApps,
                                            StaffColumns::InternationalGoals,
                                            StaffColumns::InternationalAssists,
                                            StaffColumns::FirstNHLContract,
                                            StaffColumns::StanleyCupsWon,
                                            -1,
                                            -1,
                                            -1,
                                            StaffColumns::Adaptability,
                                            StaffColumns::Ambition,
                                            StaffColumns::Determination,
                                            StaffColumns::Loyalty,
                                            StaffColumns::Pressure,
                                            StaffColumns::Professionalism,
                                            StaffColumns::Sportsmanship,
                                            StaffColumns::Temperament};
    const std::vector<qint32> player_columns{PlayerDataColumns::CurrentAbility,
                                             PlayerDataColumns::PotentialAbility,
                                             PlayerDataColumns::HomeReputation,
                                             PlayerDataColumns::CurrentReputation,
                                             PlayerDataColumns::WorldReputation,
                                             PlayerDataColumns::Goaltender,
                                             PlayerDataColumns::LeftDefense,
                                             PlayerDataColumns::RightDefense,
                                             PlayerDataColumns::LeftWing,
                                             PlayerDataColumns::Center,
                                             PlayerDataColumns::RightWing,
                                             PlayerDataColumns::OffensiveRole,
                                             PlayerDataColumns::DefensiveRole,
                                             PlayerDataColumns::PlayerRole,
                                             PlayerDataColumns::Handedness,
                                             PlayerDataColumns::FavouriteNumber,
                                             PlayerDataColumns::SquadNumber,
                                             PlayerDataColumns::InternationalSquadNumber,
                                             PlayerDataColumns::HeightCentimetres,
                                             PlayerDataColumns::WeightKilograms,
                                             PlayerDataColumns::JuniorPreference,
                                             PlayerDataColumns::Aggression,
                                             PlayerDataColumns::Anticipation,
                                             PlayerDataColumns::Bravery,
                                             PlayerDataColumns::Consistency,
                                             PlayerDataColumns::Decisions,
                                             PlayerDataColumns::Dirtiness,
                                             PlayerDataColumns::Flair,
                                             PlayerDataColumns::ImportantMatches,
                                             PlayerDataColumns::Leadership,
                                             PlayerDataColumns::Morale,
                                             PlayerDataColumns::PassTendency,
                                             PlayerDataColumns::Teamwork,
                                             PlayerDataColumns::Creativity,
                                             PlayerDataColumns::WorkRate,
                                             PlayerDataColumns::Acceleration,
                                             PlayerDataColumns::Agility,
                                             PlayerDataColumns::Balance,
                                             PlayerDataColumns::Fighting,
                                             PlayerDataColumns::Hitting,
                                             PlayerDataColumns::InjuryProneness,
                                             PlayerDataColumns::NaturalFitness,
                                             PlayerDataColumns::Pace,
                                             PlayerDataColumns::Stamina,
                                             PlayerDataColumns::Strength,
                                             PlayerDataColumns::Agitation,
                                             PlayerDataColumns::Checking,
                                             PlayerDataColumns::Deflections,
                                             PlayerDataColumns::Deking,
                                             PlayerDataColumns::Faceoffs,
                                             PlayerDataColumns::Movement,
                                             PlayerDataColumns::OneOnOnes,
                                             PlayerDataColumns::Passing,
                                             PlayerDataColumns::Pokecheck,
                                             PlayerDataColumns::Positioning,
                                             PlayerDataColumns::Slapshot,
                                             PlayerDataColumns::Stickhandling,
                                             PlayerDataColumns::Versatility,
                                             PlayerDataColumns::Wristshot,
                                             PlayerDataColumns::Blocker,
                                             PlayerDataColumns::Glove,
                                             PlayerDataColumns::Rebounds,
                                             PlayerDataColumns::Recovery,
                                             PlayerDataColumns::Reflexes};

    // Header
    sheet.addHeader({QStringLiteral("staff"), QStringLiteral("dmy"), QStringLiteral("metric")});
    sheet.addNewHeaderRow();
    sheet.addHeader(staff, staff_columns, players, player_columns);

    // Data
    sheet.add(staff, staff_columns, players, player_columns);

    return sheet.write();
}
