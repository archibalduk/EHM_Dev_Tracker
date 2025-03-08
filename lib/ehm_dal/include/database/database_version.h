#pragma once

// Qt headers
#include <QtGlobal>

namespace ehm_dal::database {
// --- Database version control --- //
/*!
 * \brief The DatabaseVersion class represents the database version number
 */
class DatabaseVersion
{
public:
    // Constructor
    DatabaseVersion(const qint16 version_number = NO_VERSION);

    // Debugging / diagnostics
    /*!
     * \brief Prints diagnostic data to the console
     */
    void printDiagnosticData() const;

    // Get data
    /*!
     * \brief Returns the database version number
     */
    inline qint16 version() const {return version_number_;}

    // Set data
    /*!
     * \brief Sets the database version number to `version_number`
     * \param version_number
     */
    inline void setVersion(const qint16 version_number) { version_number_ = version_number; }

    /*!
     * \brief The ENUM_VERSION_FLAGS enum sets out default database version numbers
     */
    enum ENUM_VERSION_FLAGS {
        NO_VERSION = -1,                 /*!< No version number set */
        NO_MINIMUM_VERSION = NO_VERSION, /*!< Minimum supported database version */
        EHM_1033 = 1033                  /*!< Database version 1033 */
    };

    // Operator overloading
    inline auto operator<=>(const qint16 rhs) const { return version() <=> rhs; }
    inline bool operator==(const qint16 rhs) const { return version() == rhs; }

private:
    qint16 version_number_{NO_VERSION}; // Private magic number
};
} // namespace ehm_dal::database
