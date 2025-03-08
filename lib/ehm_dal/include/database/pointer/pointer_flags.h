#pragma once

// TODO consider replacing with std::optional. Possibly not feasible given that EHM uses this value in the database
namespace ehm_dal::data_types {
/*!
 * \brief The PointerFlags enum represents flag values for certain `Pointer` related classes
 */
enum PointerFlags : char {
    NULL_POINTER = -1 /*!< No record / nullptr / no ID */
};
}
