#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Arena column data --- //
/*!
 * \brief The ArenaColumns  class sets out the column indexes for the `ehm_dal::schema::Arena` schema
 */
class ArenaColumns : public ehm_dal::column_data::ColumnData
{
public:
    ArenaColumns();

    enum COLUMN_INDEXES {
        Name = FirstStandardDerivedColumnIndex,
        City,
        Nation,
        NearbyArena,
        IceCondition,
        RinkSize,
        NormalCapacity,
        SeatedCapacity,
        ExpansionCapacity,
        Gender,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data

