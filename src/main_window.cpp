#include "src/main_window.h"

// Application headers
#include "lib/ehm_dal/include/library_info.h"

// Qt headers
#include <QButtonGroup>
#include <QCoreApplication>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

using namespace app;

/* ===================== */
/*      Main Window      */
/* ===================== */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("%1 v%2").arg(QCoreApplication::applicationName(),
                                                QCoreApplication::applicationVersion()));
    initUi();
}

/* =============== */
/*      Tools      */
/* =============== */

void MainWindow::runIndividualTools()
{
    control_panel_->saveSettings();
    const auto files{control_panel_->files()};

    if (files.isEmpty())
        return;

    const auto result{individual_tools_widget_->run(files)};

    qInfo().noquote() << QStringLiteral("Individual tool run complete (%L1 tools run)").arg(result);
}

/* ======================== */
/*      User Interface      */
/* ======================== */

qint32 MainWindow::about()
{
    // MSVC++ compiler version
    auto msc_ver{QString::number(_MSC_VER)};
    msc_ver.insert(msc_ver.size() - 2, ".");

    const auto application_name{QString(qApp->applicationName() + " " + qApp->applicationVersion())};
    const auto informative_text{
        QStringLiteral(
            "By Archibalduk<br /><br />"
            "<a href=\"mailto:archibalduk@gmail.com\">archibalduk@gmail.com</a><br/>"
            "<a href=\"https://www.ehmtheblueline.com\">https://www.ehmtheblueline.com</a><br/>"
            "<table>"
            "<tr><td colspan=\"2\"><b>Build Environment</b></td></tr>"
            "<tr><td width=\"150\">Microsoft Visual C++</td><td>%1</td></tr>"
            "<tr><td>Qt</td><td>%2</td></tr>"
            "</table><br/>"
            "<table>"
            "<tr><td colspan=\"2\"><b>Run Time Environment</b></td></tr>"
            "<tr><td width=\"150\">Qt</td><td>%3</td></tr>"
            "</table><br/><br/>"
            "<b>EHM DAL Module</b><br/>"
            "EHM Data Abstraction Layer version %4 by archibalduk<br/><a "
            "href=\"https://github.com/archibalduk/EHM_DAL/\">"
            "https://github.com/archibalduk/EHM_DAL/</a><br/><br/>"
            "<b>XLSX Module</b><br/>"
            "QXlsx version 1.4.6 by Jay Two<br/><a href=\"https://qtexcel.github.io/QXlsx/\">"
            "https://qtexcel.github.io/QXlsx/</a><br/>")
            .arg(msc_ver, QT_VERSION_STR, qVersion())
            .arg(ehm_dal::library_info::libraryVersion())};

    QMessageBox about;
    about.setWindowTitle(QString("About " + application_name));
    about.setText(QString("<font size='4'><b>" + application_name + "</b></font>"));
    about.setInformativeText(informative_text);
    about.setStandardButtons(QMessageBox::Ok);
    about.setDefaultButton(QMessageBox::Ok);
    return about.exec();
}

void MainWindow::initUi()
{
    main_widget_ = new QWidget(this);
    setCentralWidget(main_widget_);

    auto layout{new QVBoxLayout(main_widget_)};

    // Widgets
    control_panel_ = new ControlPanel(this);
    layout->addWidget(control_panel_);

    individual_tools_widget_ = new tools::IndividualToolsWidget(this);
    layout->addWidget(individual_tools_widget_);

    // Buttons
    auto button_box{new QDialogButtonBox(Qt::Horizontal, this)};
    layout->addWidget(button_box);

    individual_tools_button_ = new QPushButton(QStringLiteral("&Run reports"), this);
    QObject::connect(individual_tools_button_,
                     &QPushButton::clicked,
                     this,
                     &MainWindow::runIndividualTools);
    button_box->addButton(individual_tools_button_, QDialogButtonBox::ActionRole);

    about_button_ = new QPushButton(QStringLiteral("&About"), this);
    QObject::connect(about_button_, &QPushButton::clicked, this, &MainWindow::about);
    button_box->addButton(about_button_, QDialogButtonBox::HelpRole);
}
