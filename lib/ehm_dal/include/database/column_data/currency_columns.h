#pragma once

// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Currency column data --- //
/*!
 * \brief The CurrencyColumns class sets out the column indexes for the `ehm_dal::schema::Currency` schema
 */
class CurrencyColumns : public ehm_dal::column_data::ColumnData
{
public:
    // Constructor
    CurrencyColumns();

    enum ENUM_COLUMNS {
        Name = FirstStandardDerivedColumnIndex,
        NameShort,
        ThreeLetterCode,
        Symbol,
        Nation,
        ExchangeRate,
        ApproxExchangeRate,
        VeryApproxExchangeRate,
        GenderName,
        GenderNameShort,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data
