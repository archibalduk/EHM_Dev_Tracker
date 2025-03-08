#pragma once

// Qt headers
#include <QString>

namespace tools {
class AbstractTool
{
public:
    AbstractTool();

    static void setFileNamePrefix(const QString &text);

protected:
    inline QString fileNamePrefix() const { return file_name_prefix_; }
    QString folderPath() const;
    QString spreadsheetFileType() const;

private:
    enum ENUM_FLAGS { CSV = -2, XLSX = -3 };

    static QString file_name_prefix_;
};
} // namespace tools
