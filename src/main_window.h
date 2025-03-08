#pragma once

// Application headers
#include "src/control_panel.h"
#include "src/tools/individual_tools_widget.h"

// Qt headers
#include <QMainWindow>
class QPushButton;

namespace app {
/*!
 * \brief The MainWindow class provides the main application window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    // User interface: functions
    void initUi();

    // User interface: buttons
    QPushButton *about_button_;
    QPushButton *individual_tools_button_;

    // User interface: widgets
    ControlPanel *control_panel_;
    tools::IndividualToolsWidget *individual_tools_widget_;
    QWidget *main_widget_;

private slots:
    // Tools
    void runIndividualTools();

    // User interface
    qint32 about();
};
} // namespace app
