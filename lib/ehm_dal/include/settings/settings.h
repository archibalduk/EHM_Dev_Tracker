#pragma once

// Qt headers
#include <QHash>
#include <QString>
#include <QVariant>

namespace ehm_dal::settings {

// --- Application settings cache/manager --- //
class Settings
{
public:
    // Constructor
    Settings();

    // File i/o
    void writeAll() const;

    // Get data
    static bool debugMode();
    QVariant value(const QString &key, const QVariant &default_value = QVariant());

    // Set data
    void remove(const QString &key);
    void setValue(const QString &key, const QVariant &value);

private:
    // File i/o
    static const QString file_name_;
    QVariant read(const QString &key, const QVariant &default_value = QVariant()) const;

    // Settings cache
    static QHash<QString, QVariant> cache_;
};
} // namespace ehm_dal::settings
