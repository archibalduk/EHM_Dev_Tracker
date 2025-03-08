#pragma once

// Application headers
#include "include/settings/folder_path.h"

// Qt headers
#include <QTime>
class QDataStream;
class QString;
class QWidget;

namespace ehm_dal::file_io {
/*!
 * \brief The AbstractFileManager class is a base class providing simple read and write file access to database and saved game files
 * \details
 */
class AbstractFileManager
{
public:
    AbstractFileManager(const QString &folder_path_key);

    // Close database/tables
    /*!
     * \brief Closes the active database/saved game and clears all tables.
     * \param show_confirmation_dialog indicates whether or not to display a dialog asking the user to confirm
     * \return whether or not successful
     */
    bool close(const bool show_confirmation_dialog = true);

    // Descriptor
    /*!
     * \brief Returns the file manager descriptor.
     * E.g. This will return "database" for a database file manager.
     */
    virtual QString descriptor() const = 0;
    /*!
     * \brief Returns a list of supported file type filters for `QFileDialog`.
     */
    virtual QString fileFilterString() const = 0;

    // File i/o - read
    /*!
     * \brief Opens the file at `path`.
     * \param path file path
     * \return whether or not successful
     */
    bool open(const QString &path);
    /*!
     * \brief Displays a file dialog window and opens the user selected file.
     * \param parent parent widget for the dialog window
     * \return whether or not successful
     */
    bool open(QWidget *parent = nullptr);

    // File i/o - write
    /*!
     * \brief Saves the data to the existing file.
     * \return whether or not successful
     */
    bool save();
    /*!
     * \brief Displays a file dialog window and saves the user selected destination.
     * \param parent parent widget for the dialog window
     * \return whether or not successful
     */
    bool saveAs(QWidget *parent = nullptr);

    // Get data
    /*!
     * \brief Returns whether or not a file is presently open.
     */
    inline bool isOpen() const { return is_open_; }
    /*!
     * \brief Returns whether or not the file has been previously saved.
     */
    inline bool isSaved() const { return has_been_saved_; }

protected:
    // Status
    inline void setOpenStatus(const bool is_open) { is_open_ = is_open; }
    void setSaveStatus(const bool has_been_saved);

private:
    // Close database/tables
    virtual void closeAll() = 0;

    // File i/o - read
    virtual bool read(const QString &path) = 0;

    // File i/o - write
    virtual bool write(const QString &path) = 0;

    // Folder path cache
    settings::FolderPath source_folder_;

    // Status
    bool has_been_saved_{false};
    bool is_open_{false};
    QTime last_saved_time_{QTime::currentTime()};
};
} // namespace ehm_dal::file_io
