#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- States & provinces column data --- //
/*!
 * \brief The StateColumns class sets out the column indexes for the `ehm_dal::schema::State` schema
 */
class StateColumns : public ehm_dal::column_data::ColumnData
{
public:
    StateColumns();

    enum COLUMN_INDEXES {
        Abbreviation = FirstStandardDerivedColumnIndex,
        Name,
        ShortName,
        Nation,
        Gender,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

