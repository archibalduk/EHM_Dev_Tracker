#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Injury column data --- //
/*!
 * \brief The InjuryColumns class sets out the column indexes for the `ehm_dal::schema::Injury` schema
 */
class InjuryColumns : public ehm_dal::column_data::ColumnData
{
public:
    // Constructor
    InjuryColumns();

    enum ENUM_COLUMNS {
        Name = FirstStandardDerivedColumnIndex,
        NameDative,
        NameGenetive,
        NameSpecialNominative,
        MinimumDaysOut,
        ExtraDaysOut,
        Category,
        Chance,
        InactiveRatio,
        Severity,
        Cause,
        IsRecurring,
        GenderName,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
