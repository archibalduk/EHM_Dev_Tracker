#pragma once

// Application headers
#include "include/database/pointer/pointer_flags.h"

// Qt headers
#include <QDataStream>
#include <QVariant>

namespace ehm_dal::data_types {
// TODO add sanity checks when getting data in case the id is -1
// TODO consider merging Flag and Pointer into a single class. This should be possible if FlagTable derives from AbstractTable.
// --- Abstract pointer base class --- //
/*!
 * \brief The AbstractPointer class represents a pointer to a table item.
 */
template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
class AbstractPointer
{
public:
    AbstractPointer();
    /*!
     * \brief Constructs an `AbstractPointer` with a table index of `table_id` and a record index of `record_id`.
     * \param table_id table index
     * \param record_id record index
     */
    AbstractPointer(const T_TableIndex table_id,
                    const T_IdDataType record_id = PointerFlags::NULL_POINTER);

    // File i/o
    friend QDataStream &operator>>(QDataStream &in, AbstractPointer &data)
    {
        in.readRawData(reinterpret_cast<char *>(&data.id_), sizeof(T_IdDataType));
        return in;
    }

    friend QDataStream &operator<<(QDataStream &out, const AbstractPointer &data)
    {
        auto id{data.id()};
        out.writeRawData(reinterpret_cast<char *>(&id), sizeof(T_IdDataType));
        return out;
    }

    // Get data - attributes
    /*!
     * \brief Returns the number of columns in the table pointed to.
     */
    qint32 columnCount() const { return constTable()->columnCount(); }
    /*!
     * \brief Returns whether or not the `AbstractPointer` is set to `ehm_dal::data_types::PointerFlags::NULL_POINTER`.
     */
    inline bool isNone() const { return !isPointer(); }
    /*!
     * \brief Returns whether or not the `AbstractPointer` has been set to an item index
     */
    inline bool isPointer() const { return id() > PointerFlags::NULL_POINTER; }
    /*!
     * \brief Returns whether or not the `AbstractPointer` has been set to an item index and to a table.
     */
    inline bool isValidPointer() const { return isValidTable() && isPointer(); }
    /*!
     * \brief Returns whether or not the `AbstractPointer` has been set to a table.
     */
    inline bool isValidTable() const
    {
        return table_id_ != static_cast<T_TableIndex>(PointerFlags::NULL_POINTER);
    }

    // Get data - pointer
    /*!
     * \brief Returns the data stored under the given `role`.
     * `Qt::DisplayRole` returns the item's display text and `Qt::EditRole` returns the item's id.
     * \param role  item data role. `Qt::DisplayRole` and `Qt::EditRole` are the most frequently used
     * \return a `QVariant` containing a copy of the data.
     */
    QVariant data(const qint32 role) const;
    /*!
     * \brief Returns data relating to the item pointed to by the `AbstractPointer`
     * for the given `role` and `column`.
     * \param column the selected column
     * \param role item data role. `Qt::DisplayRole` and `Qt::EditRole` are the most frequently used
     * \return a `QVariant` containing a copy of the data
     */
    virtual QVariant data(const qint32 column, const qint32 role) const;
    /*!
     * \brief Returns the item index pointed to.
     */
    inline virtual T_IdDataType id() const { return id_; }
    /*!
     * \brief idBuffer returns the buffered id which is generally only
     * useful when first initialising the links between child and parent data. Prefer using
     * `AbstractPointer::id()` wherever possible as the buffered value may be out of date.
     * \return buffered id value
     */
    inline T_IdDataType idBuffer() const { return id_; }
    /*!
     * \brief parentItemId returns the buffered id which is generally only
     * useful when first initialising the links between child and parent data. Prefer using
     * `AbstractPointer::id()` wherever possible as the buffered value may be out of date.
     * \return buffered id value
     */
    inline T_IdDataType parentItemId() const { return idBuffer(); }
    /*!
     * \brief Returns the display text of the item.
     */
    virtual QString text() const;

    // Get data - table
    /*!
     * \brief Returns the table name of the item.
     */
    QString description() const;
    /*!
     * \brief Returns a read-only pointer to the table pointed to.
     */
    virtual std::shared_ptr<T_Table> constTable() const = 0;
    /*!
     * \brief Returns a pointer to the table pointed to.
     */
    virtual std::shared_ptr<T_Table> table() = 0;
    /*!
     * \brief Returns the table id of the table pointed to.
     */
    T_TableIndex tableId() const { return table_id_; }

    // Operator overloading: Comparators
    inline auto operator<=>(const AbstractPointer &rhs) const { return id() <=> rhs.id(); }
    inline bool operator==(const AbstractPointer &rhs) const { return id() == rhs.id(); }
    inline auto operator<=>(const qint32 &rhs) const { return id() <=> rhs; }
    inline bool operator==(const qint32 &rhs) const { return id() == rhs; }

    // Set data - pointer
    // TODO deprecate set() in favour of setData()
    Q_DECL_DEPRECATED void set(const QVariant &value, const qint32 role)
    {
        return setData(value, role);
    }
    /*!
     * \brief Sets the `role` data for the item at `index` to `value`.
     * \param value value to apply to the item
     * \param role item data role; typically `Qt::EditRole`
     */
    virtual void setData(const QVariant &value, const qint32 role);
    /*!
     * \brief Sets the `role` data for the item pointed to at `column` to `value`.
     * \param column the selected column
     * \param value value to apply to the item
     * \param role item data role; typically `Qt::EditRole`
     * \return whether or not any data was successfully modified
     */
    bool setData(const qint32 column, const QVariant &value, const qint32 role);

protected:
    T_IdDataType id_{static_cast<T_IdDataType>(PointerFlags::NULL_POINTER)};       // Record id
    T_TableIndex table_id_{static_cast<T_TableIndex>(PointerFlags::NULL_POINTER)}; // Table id

    inline void setId(const qint32 id) { id_ = static_cast<T_IdDataType>(id); }
};

/* ============================ */
/*      Pointer Base Class      */
/* ============================ */

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::AbstractPointer()
{}

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::AbstractPointer(const T_TableIndex table_id,
                                                                      const T_IdDataType record_id)
    : id_(record_id)
    , table_id_(table_id)
{}

/* =========================== */
/*      Get Data - Pointer     */
/* =========================== */

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
QVariant AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::data(const qint32 role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return text();
    case Qt::EditRole:
        return id();
    default:
        return QVariant();
    }
}

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
QVariant AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::data(const qint32 column,
                                                                    qint32 role) const
{
    return constTable()->index(id(), column).data(role);
}

template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
QString AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::text() const
{
    return constTable()->index(id(), 2).data(Qt::DisplayRole).toString();
}

/* ========================= */
/*      Get Data - Table     */
/* ========================= */

// --- Get table name --- //
template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
QString AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::description() const
{
    if (tableId() != static_cast<T_TableIndex>(PointerFlags::NULL_POINTER))
        return constTable()->attributes()->name();

    return QStringLiteral("[No table]");
}

/* =========================== */
/*      Set Data - Pointer     */
/* =========================== */

// --- Sets the pointer id value --- //
template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
void AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::setData(const QVariant &value,
                                                                   const qint32 role)
{
    if (role == Qt::EditRole)
        id_ = static_cast<T_IdDataType>(value.toInt());
}

// --- Edits the underlying item pointed to --- //
template<typename T_IdDataType, typename T_TableIndex, typename T_Table>
bool AbstractPointer<T_IdDataType, T_TableIndex, T_Table>::setData(const qint32 column,
                                                                   const QVariant &value,
                                                                   const qint32 role)
{
    const auto index{table()->index(id(), column)};
    return table()->setData(index, value, role);
}
} // namespace ehm_dal::data_types


