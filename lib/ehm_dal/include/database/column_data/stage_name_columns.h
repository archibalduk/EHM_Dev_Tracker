#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Stage name column data --- //
/*!
 * \brief The StageNameColumns class sets out the column indexes for the `ehm_dal::schema::StageName` schema
 */
class StageNameColumns : public ehm_dal::column_data::ColumnData
{
public:
    // Constructor
    StageNameColumns();

    enum ENUM_COLUMNS {
        LongName = FirstStandardDerivedColumnIndex,
        ShortName,
        PluralName,
        StageGenericType,
        GroupGenericType,
        LongNameGender,
        ShortNameGender,
        PluralNameGender,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
