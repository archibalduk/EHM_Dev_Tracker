#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- City column data --- //
/*!
 * \brief The CityColumns class sets out the column indexes for the `ehm_dal::schema::City` schema
 */
class CityColumns : public ehm_dal::column_data::ColumnData
{
public:
    CityColumns();

    enum COLUMN_INDEXES {
        Name = FirstStandardDerivedColumnIndex,
        Nation,
        State,
        Latitude,
        Longitude,
        Attraction,
        Gender,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::schema

