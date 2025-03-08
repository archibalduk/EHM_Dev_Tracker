#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Database_Header column data --- //
/*!
 * \brief The DatabaseHeaderColumns class sets out the column indexes for the `ehm_dal::schema::DatabaseHeader` schema
 */
class DatabaseHeaderColumns : public ehm_dal::column_data::ColumnData
{
public:
    DatabaseHeaderColumns();

    enum COLUMN_INDEXES {
        StartYear = FirstIdOnlyDerivedColumnIndex,
        Author,
        CurrentDatabaseVersion,
        OriginalDatabaseVersion,
        NextUid,
        Attributes1_100Scale,
        FakeData,
        MasterDatabase,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

