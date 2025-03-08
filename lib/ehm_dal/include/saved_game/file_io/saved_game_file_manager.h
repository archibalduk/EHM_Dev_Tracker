#pragma once

// Application headers
#include "include/file_io/abstract_file_manager.h"

namespace ehm_dal::file_io {

class SavedGameFileManager : public ehm_dal::file_io::AbstractFileManager
{
public:
    SavedGameFileManager();

    // Descriptor
    inline QString descriptor() const override { return QStringLiteral("saved_game"); }
    inline QString fileFilterString() const override
    {
        return QStringLiteral("EHM 1 Saved Game (*.sav)");
    }

private:
    // Close saved game/database/tables
    void closeAll() override;

    // File i/o - read
    bool read(const QString &path) override;

    // File i/o - write
    bool write(const QString &path) override;
};
} // namespace ehm_dal::file_io
