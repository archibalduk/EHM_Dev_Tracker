#pragma once

// Application headers
#include "include/spreadsheet/private/spreadsheet_file.h"
namespace ehm_dal::data_types {
class Pointer;
}
namespace ehm_dal::settings {
class FolderPath;
}
namespace ehm_dal::tables {
class AbstractTable;
}

// Qt headers
class QAbstractTableModel;
#include <QString>
#include <QVariant>
#include <span>
#include <vector>

namespace ehm_dal::spreadsheet {

// --- Spreadsheet --- //
class Spreadsheet
{
public:
    // Constructor
    Spreadsheet(const QString &file_path = QString());
    Spreadsheet(const settings::FolderPath &path);
    ~Spreadsheet();

    // Add data - cells/rows: basic
    inline void add() { add(QVariant()); }
    inline void add(const QString &text) { add(QVariant(text)); }
    void add(const QVariant &data);
    void add(const QVariant &data, const qint32 row);
    void add(const QVariant &data, const qint32 start_row, const qint32 row_count);

    // Add data - cells/rows: AbstractTable data
    /*!
     * \brief Adds all rows and columns from `model` to the spreadsheet. This is generally used to export a
     * `ehm_dal::tables::AbstractTable` using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `ehm_dal::tables::AbstractTable`
     * \param role Source data role
     */
    void add(ehm_dal::tables::AbstractTable *model, const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds all rows and the selected columns from `model` to the spreadsheet. This is generally used to export 
     * a `ehm_dal::tables::AbstractTable` using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `ehm_dal::tables::AbstractTable`
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(ehm_dal::tables::AbstractTable *model,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected row and all columns from `model` to the spreadsheet. This is generally used to export 
     * a `ehm_dal::tables::AbstractTable` using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `ehm_dal::tables::AbstractTable`
     * \param row Source row
     * \param role Source data role
     */
    void add(ehm_dal::tables::AbstractTable *model,
             const qint32 row,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected row and selected columns from `model` to the spreadsheet. This is generally used to 
     * export a `ehm_dal::tables::AbstractTable` using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `ehm_dal::tables::AbstractTable`
     * \param row Source row
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(ehm_dal::tables::AbstractTable *model,
             const qint32 row,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);

    // Add data - cells/rows: QAbstractTableModel data
    /*!
     * \brief Adds all rows and columns from `model` to the spreadsheet. This is generally used to export
     * a `QAbstractTableModel` using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `QAbstractTableModel`
     * \param role Source data role
     */
    void add(QAbstractTableModel *model, const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds all rows and the selected columns from `model` to the spreadsheet. This is generally used to export 
     * a `QAbstractTableModel` using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `QAbstractTableModel`
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(QAbstractTableModel *model,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected row and all columns from `model` to the spreadsheet. This is generally used to export 
     * a `QAbstractTableModel` using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `QAbstractTableModel`
     * \param row Source row
     * \param role Source data role
     */
    void add(QAbstractTableModel *model,
             const qint32 row,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected row and selected columns from `model` to the spreadsheet. This is generally used to 
     * export a `QAbstractTableModel` using `Qt::DisplayRole` or `Qt::EditRole`.
     * \param model Source `QAbstractTableModel`
     * \param row Source row
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(QAbstractTableModel *model,
             const qint32 row,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);

    // Add data - cells/rows: Pointer data
    /*!
     * \brief Adds all columns of the selected Pointer to the spreadsheet.
     * \param pointer Source pointer
     * \param role Source data role
     */
    void add(const ehm_dal::data_types::Pointer &pointer, const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected columns of the selected Pointer to the spreadsheet.
     * \param pointer Source pointer
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(const ehm_dal::data_types::Pointer &pointer,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds all columns of the selected Pointers to the spreadsheet.
     * \param pointer_list Source pointers
     * \param role Source data role
     */
    void add(const std::vector<ehm_dal::data_types::Pointer> &pointer_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);
    /*!
     * \brief Adds the selected columns of the selected Pointers to the spreadsheet.
     * \param pointer_list Source pointers
     * \param column_index_list Column indexes to be added
     * \param role Source data role
     */
    void add(const std::vector<ehm_dal::data_types::Pointer> &pointer_list,
             const std::vector<qint32> &column_index_list,
             const Qt::ItemDataRole role = Qt::DisplayRole);

    // Add data - prefix cells
    /*!
     * \brief Adds a blank cell to the current prefix row.
     */
    inline void addPrefix() { addPrefix(QVariant()); }
    /*!
     * \brief Adds `data` to the current prefix row.
     * \param data Data to be added
     */
    inline void addPrefix(const QVariant &data) { prefix_cell_data_.push_back(data); }

    // Add data - header: basic
    /*!
     * \brief Adds a blank cell to the current header row.
     */
    inline void addHeader() { add(QVariant()); }
    /*!
     * \brief Adds `text` to the current header row.
     * \param text Text to be added
     */
    inline void addHeader(const QString &text) { addHeader(QVariant(text)); }
    /*!
     * \brief Adds the `text_list` to the current header row.
     * \param text_list `QStringList` to be added
     */
    void addHeader(const QStringList &text_list);
    /*!
     * \brief Adds `data` to the current header row.
     * \param data Data to be added
     */
    void addHeader(const QVariant &data);

    // Add data - header: model data
    /*!
     * \brief Adds a header row of column names of all columns from the 'model'. 
     * This is typically used to add the names of all columns from a Table as a header row to the spreadsheet.
     * \param model Source `QAbstractTableModel` or Table
     */
    void addHeader(QAbstractTableModel *model);
    /*!
     * \brief Adds a header row of column names of the selected columnd from the 'model'. 
     * This is typically used to add the names of the selected columns from a Table as a header row to the spreadsheet.
     * \param model Source `QAbstractTableModel` or Table
     * \param column_index_list Column indexes to be added
     */
    void addHeader(QAbstractTableModel *model, const std::vector<qint32> &column_index_list);

    // Add data - prefix header
    /*!
     * \brief Adds a blank cell to the current prefix header row.
     */
    inline void addHeaderPrefix() { addHeaderPrefix(QVariant()); }
    /*!
     * \brief Adds `data` to the current prefix header row.
     * \param data Data to be added
     */
    inline void addHeaderPrefix(const QVariant &data) { prefix_header_data_.push_back(data); }

    // Date format
    /*!
     * \brief The DateFormat enum represents the date format used when returning cell data.
     */
    enum class DateFormat {
        DateMonthYear, /*!< DD-MM-YYYY */
        MonthDateYear, /*!< MM-DD-YYYY */
        YearMonthDate  /*!< YYYY-MM-DD */
    };

    /*!
     * \brief Returns the current date format used when returning cell data.
     */
    static DateFormat dateFormat();
    /*!
     * \brief Returns the current date format used when returning cell data.
     */
    inline static QString dateFormatString() { return date_format_; }
    /*!
     * \brief Sets the data format to `date_format` when returning cell data. This can be modified before or after reading spreadsheet data.
     * \param date_format Selected `DateFormat`
     */
    static void setDateFormat(const DateFormat date_format);

    // Debugging / diagnostics
    /*!
     * \brief Prints various diagnostic data to the console.
     */
    void printDiagnosticData() const;

    // File details - get data
    /*!
     * \brief Returns the file path, file base name and file extension.
     */
    QString file();
    /*!
     * \brief Returns the file path and name of the output spreadsheet.
     */
    inline QString fileName() { return file_name_; }
    /*!
     * \brief Returns the file type of the output spreadsheet.
     * \return the file type
     */
    QString fileType() const;
    /*!
     * \brief Returns the file path
     */
    inline QString folderPath() const { return path_; }
    /*!
     * \brief Returns the identifier text string located at the top left cell (i.e. Cell A1).
     */
    inline QString identifier() { return headerCell(0,0).toString().replace(" ", "_").toLower(); }

    // File details - set data
    /*!
     * \brief Adds `suffix` to the end of the file name.
     * \param suffix
     */
    void addFileNameSuffix(const QString &suffix);
    /*!
     * \brief Set the file path, name and extension from `path`.
     * \param path
     * \return Returns whether `path` contains any text.
     */
    bool setFile(const QString &path);

    // File extensions
    /*!
     * \brief Returns the default file extension.
     */
    static qint32 defaultFileExtension();
    /*!
     * \brief Returns a list of supported file extensions.
     * \param merged_list If `true`, the list will include ";;" separators for use as individual file filters.
     */
    static QString fileExtensionListAsString(const bool merged_list = true);
    /*!
     * \brief Returns a list of supported file extensions.
     */
    static QStringList fileExtensionListAsStringList();
    /*!
     * \brief Set the default file extension to `i`.
     * \param i `Spreadsheet::ENUM_FILE_EXTENSIONS`
     */
    static void setDefaultFileExtension(const qint32 i);

    // File I/O
    /*!
     * \brief Opens a file without showing a dialog window.
     * \param file_path Folder path and file name to be opened
     * \return whether or not the file was successfully read
     */
    bool open(const QString &file_path);
    /*!
     * \brief Opens a file without showing a dialog window.
     * \param folder Folder path
     * \param file_name File name
     * \return whether or not the file was successfully read
     */
    bool open(const QString &folder, const QString &file_name);
    /*!
     * \brief Reads the current file.
     * \return whether or not the file was successfully read
     */
    bool read();
    /*!
     * \brief Saves the spreadsheet to the selected folder path and file name.
     * \param folder Folder path
     * \param file_name File name
     * \return whether or not the file was successfully saved
     */
    bool save(const QString &folder, const QString &file_name);
    /*!
     * \brief Writes/saves the spreadsheet to the output file.
     * \return whether the spreadsheet file was successfully saved
     */
    bool write();

    // File I/O dialog windows
    /*!
     * \brief Displays a dialog window allowing the user to select a spreadsheet to open.
     * \param file_path Initial file path to show in the dialog
     * \param read_data `True` = read the file. `False` = do not read the file.
     * \return whether the file was successfully read and/or selected. Returns `false` if the user has clicked `cancel`.
     */
    bool showOpenDialog(QString file_path = QString(), const bool read_data = true);
    /*!
     * \brief Displays a dialog window allowing the user to select a spreadsheet to open.
     * \param path Initial file path to show in the dialog
     * \param read_data `True` = read the file. `False` = do not read the file.
     * \return whether the file was successfully read and/or selected. Returns `false` if the user has clicked `cancel`.
     */
    bool showOpenDialog(settings::FolderPath &path, const bool read_data = true);
    /*!
     * \brief Displays a dialog window allowing the user to save the spreadsheet.
     * \param file_name Initial file name to show in the dialog
     * \param file_path Initial file path to show in the dialog
     * \return whether the file was successfully saved. Returns `false` if the user has clicked `cancel`.
     */
    bool showSaveDialog(const QString &file_name = "output.csv", QString file_path = QString());
    /*!
     * \brief Displays a dialog window allowing the user to save the spreadsheet.
     * \param Initial file path to show in the dialog
     * \return whether the file was successfully saved. Returns `false` if the user has clicked `cancel`.
     */
    bool showSaveDialog(settings::FolderPath &path);

    // Get data - cells
    /*!
     * \brief Returns the data located at `row` and `col`.
     * \param row Row index
     * \param col Column index
     */
    QVariant cell(const qint32 row, const qint32 col, const bool return_as_date = false) const;
    /*!
     * \brief Returns the cell data as a QDate located at `row` and `col`.
     * \param row Row index
     * \param col Column index
     * \param return_as_date `True` = return the value as a date
     */
    std::span<const QVariant> cells(const qint32 row,
                                    const qint32 col,
                                    const qint32 col_count) const;
    /*!
     * \brief Returns whether a column contains any data
     * \param column Column index
     */
    bool columnContainsData(const qint32 column) const;
    /*!
     * \brief Returns the column count for the selected row.
     * \param row Row index
     * \return column count
     */
    qint32 columnCount(const qint32 row) const;
    /*!
     * \brief Returns the data of the entirety of the selected `row`.
     * \param row Row index
     * \return Column data
     */
    std::span<const QVariant> row(const qint32 row) const;
    /*!
     * \brief Returns the data row count.
     * \return row count
     */
    inline qint32 rowCount() const { return static_cast<qint32>(cell_data_.size()); }

    // Get data - prefix cells
    QVariant prefix(const qint32 row) const;
    inline bool hasPrefixData() const { return prefixCount() > 0; }
    inline qint32 prefixCount() const { return static_cast<qint32>(prefix_cell_data_.size()); }

    // Get data - header
    std::span<const QVariant> header(const qint32 row) const;
    QVariant headerCell(const qint32 row, const quint16 col) const;
    inline qint32 headerCount() const
    {
        return std::max(static_cast<qint32>(header_data_.size()), header_count_);
    }

    // Get data - header
    QVariant prefixHeader(const qint32 row) const;
    inline bool hasPrefixHeaderData() const { return prefixHeaderCount() > 0; }
    inline qint32 prefixHeaderCount() const
    {
        return static_cast<qint32>(prefix_header_data_.size());
    }

    // Get settings
    /*!
     * \brief Returns the default file path used for exporting data.
     */
    static QString exportPath();
    /*!
     * \brief Returns the default file path used for importing data.
     */
    static QString importPath();

    // Row data: add data
    /*!
     * \brief Adds a new header row.
     */
    void addNewHeaderRow();
    /*!
     * \brief Adds a new data row.
     */
    void addNewRow();

    // Set header data
    /*!
     * \brief Sets the number of header rows to `header_row_count`.
     * \param header_row_count
     */
    void setHeaderCount(const qint32 header_row_count);

    // Spreadsheet file
    /*!
     * \brief Creates a new spreadsheet from `f` and returns a pointer to the created `ehm_dal::spreadsheet::SpreadsheetFile`.
     * \param f Source `QFile`
     * \return pointer to the created `ehm_dal::spreadsheet::SpreadsheetFile`
     */
    std::unique_ptr<SpreadsheetFile> newSpreadsheet(QFile &f);

private:
    // Data
    std::vector<std::vector<QVariant>> cell_data_;
    std::vector<std::vector<QVariant>> header_data_;
    std::vector<QVariant> prefix_cell_data_;
    std::vector<QVariant> prefix_header_data_;

    // Add data - cells/rows: Private model data methods
    void addFromTableModel(QAbstractTableModel *model,
                           const std::vector<qint32> &column_index_list,
                           const Qt::ItemDataRole role = Qt::DisplayRole);
    void addFromTableModel(QAbstractTableModel *model,
                           const qint32 row,
                           const std::vector<qint32> &column_index_list,
                           const Qt::ItemDataRole role = Qt::DisplayRole);
    void addFromTreeModel(QAbstractTableModel *model,
                          const std::vector<qint32> &column_index_list,
                          const Qt::ItemDataRole role = Qt::DisplayRole);
    void addFromTreeModel(QAbstractTableModel *model,
                          const qint32 parent_row,
                          const std::vector<qint32> &column_index_list,
                          const Qt::ItemDataRole role = Qt::DisplayRole);

    // Column data
    std::vector<qint32> columnList(const qint32 column_count) const;

    // Convert value
    QDate toDate(const QVariant &value) const;

    // Date format
    static QString date_format_;

    // File data
    quint8 file_extension_;
    QString file_name_;
    QString path_;

    // File extensions (functions)
    static QHash<QString, quint8> fileExtensions();
    static QString filterText(const qint32 type);

    // File extensions (members)
    enum ENUM_FILE_EXTENSIONS { CSV, XLSX, FILE_EXTENSION_COUNT };

    // Header
    qint32 header_count_{2};

    // Progress display
    bool hide_progress_{false};

    // Row data: get data
    std::vector<QVariant> *currentHeaderRow();
    std::vector<QVariant> *currentRow();
};
} // namespace ehm_dal::spreadsheet
