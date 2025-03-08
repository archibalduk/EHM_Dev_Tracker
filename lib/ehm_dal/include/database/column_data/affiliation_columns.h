#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Affiliation column data --- //
/*!
 * \brief The AffiliationColumns class sets out the column indexes for the `ehm_dal::schema::Affiliation` schema
 */
class AffiliationColumns : public ehm_dal::column_data::ColumnData
{
public:
    AffiliationColumns();

    enum COLUMN_INDEXES {
        UpperClub = FirstStandardDerivedColumnIndex,
        UpperComp,
        UpperNation,
        LowerClub,
        LowerComp,
        LowerNation,
        Type,
        Dependency,
        GoalieCount,
        SkaterCount,
        IsJuniorAffiliation,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

