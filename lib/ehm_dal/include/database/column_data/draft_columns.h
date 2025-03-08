#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Draft column data --- //
/*!
 * \brief The DraftColumns class sets out the column indexes for the `ehm_dal::schema::Draft` schema
 */
class DraftColumns : public ehm_dal::column_data::ColumnData
{
public:
    // Constructor
    DraftColumns();

    enum ENUM_COLUMNS {
        Name = FirstStandardDerivedColumnIndex,
        Comp,
        Extinct,
        ExtraRules,
        GenderName,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
