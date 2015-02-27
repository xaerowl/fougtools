#include "test_qttools.h"

#include "../src/qttools/core/qlocale_utils.h"
#include "../src/qttools/gui/qstandard_item_explorer.h"
#include "../src/qttools/script/calculator.h"
#include "../src/qttools/sql/cpp_sql_enum_map.h"

#ifdef FOUGTOOLS_HAVE_QTTOOLS_TASK
# include "../src/qttools/Task/RunnerCurrentThread.h"
# include "../src/qttools/Task/RunnerQThreadPool.h"
# include "../src/qttools/Task/RunnerStdAsync.h"
# include "../src/qttools/Task/Manager.h"
#endif // FOUGTOOLS_HAVE_QTTOOLS_TASK

#include "../src/mathtools/consts.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

#include <cmath>
#include <unordered_map>

void TestQtTools::core_QLocaleUtils_test()
{
    QCOMPARE(static_cast<int>(QLocale::France), 74);
    QCOMPARE(qttools::QLocaleUtils::toCountry(74), QLocale::France);
    //  foreach (auto country, qttools::QLocaleTools::allCountries()) {
    //    qDebug() << QLocale::countryToString(country);
    //  }
}

void TestQtTools::gui_QStandardItemExplorer_test()
{
    QStandardItemModel itemModel;

    auto rootItem = new QStandardItem(QLatin1String("root"));
    itemModel.appendRow(rootItem);

    auto item1 = new QStandardItem(QLatin1String("item_1"));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_1")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_2")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_3")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_4")));

    auto item2 = new QStandardItem(QLatin1String("item_2"));

    rootItem->appendRow(item1);
    rootItem->appendRow(item2);

    qttools::QStandardItemExplorer explorer(&itemModel);
    QCOMPARE(explorer.current(), itemModel.invisibleRootItem());
    explorer.goNext();
    QCOMPARE(explorer.current(), rootItem);
    explorer.goNext();
    QCOMPARE(explorer.current(), item1);
    explorer.goNext();
    QCOMPARE(explorer.current(), item2);
    explorer.goNext();
    for (int i = 0; i < item1->rowCount(); ++i) {
        QCOMPARE(explorer.current(), item1->child(i));
        explorer.goNext();
    }
    QCOMPARE(explorer.atEnd(), true);
}

void TestQtTools::script_Calculator_test()
{
    qttools::Calculator calc;
    QVERIFY(calc.hasResult() && calc.lastErrorText().isEmpty());

    calc.evaluate("2*3");
    QVERIFY(calc.hasResult());
    QCOMPARE(calc.lastResult(), 6.0);

    calc.evaluate("sin(PI/4)");
    QVERIFY(calc.hasResult());
    QCOMPARE(calc.lastResult(), std::sin(math::pi / 4.0));

    calc.evaluate("4*");
    QVERIFY(!calc.hasResult());
    QVERIFY(!calc.lastErrorText().isEmpty());
    //qDebug() << calc.lastErrorText();
}

namespace Internal {

enum class Status
{
    Started,
    Running,
    Finished
};

} // namespace Internal

void TestQtTools::sql_SqlCppEnumMap_test()
{
    qttools::SqlCppEnumMap<Internal::Status> enumMap;
    enumMap.addMapping(Internal::Status::Started, "status_started");
    enumMap.addMapping(Internal::Status::Running, "status_running");
    enumMap.addMapping(Internal::Status::Finished, "status_finished");

    QCOMPARE(enumMap.size(), static_cast<std::size_t>(3));

    QCOMPARE(enumMap.index(Internal::Status::Started), static_cast<std::size_t>(0));
    QCOMPARE(enumMap.index(Internal::Status::Running), static_cast<std::size_t>(1));
    QCOMPARE(enumMap.index(Internal::Status::Finished), static_cast<std::size_t>(2));

    QCOMPARE(enumMap.cppValueAt(0), Internal::Status::Started);
    QCOMPARE(enumMap.cppValueAt(1), Internal::Status::Running);
    QCOMPARE(enumMap.cppValueAt(2), Internal::Status::Finished);

    QCOMPARE(enumMap.cppValue("status_started"), Internal::Status::Started);
    QCOMPARE(enumMap.cppValue("status_running"), Internal::Status::Running);
    QCOMPARE(enumMap.cppValue("status_finished"), Internal::Status::Finished);

    QCOMPARE(enumMap.sqlValue(Internal::Status::Started), "status_started");
    QCOMPARE(enumMap.sqlValue(Internal::Status::Running), "status_running");
    QCOMPARE(enumMap.sqlValue(Internal::Status::Finished), "status_finished");
}

#ifdef FOUGTOOLS_HAVE_QTTOOLS_TASK

namespace Internal {

static const bool debugOutput = true;

template<typename SELECTOR, typename ... ARGS>
static Task::BaseRunner* newTaskRunner(
        Task::Manager* mgr, const char* selectorName, ARGS ... args)
{
    auto runner = mgr->newTask<SELECTOR>(args ...);
    runner->setTaskTitle(QString("Tâche [%1] %2").arg(selectorName).arg(runner->taskId()));
    return runner;
}

} // namespace Internal

void TestQtTools::task_Manager_test()
{
    auto taskMgr = Task::Manager::globalInstance();
    QObject::connect(taskMgr, &Task::Manager::started,
                     [](quint64 taskId, const QString& title) {
        if (Internal::debugOutput)
            qDebug() << "Started:" << taskId << title;
    } );

    QObject::connect(taskMgr, &Task::Manager::progressStep,
                     [](quint64 taskId, const QString& title) {
        if (Internal::debugOutput)
            qDebug() << "Step:" << taskId << title;
    } );

    QObject::connect(taskMgr, &Task::Manager::message,
                     [](quint64 taskId, const QString& msg) {
        if (Internal::debugOutput)
            qDebug() << "Message:" << taskId << msg;
    } );

    std::vector<Task::BaseRunner*> taskVec;
    for (int i = 0; i < 5; ++i) {
        taskVec.push_back(Internal::newTaskRunner<QThreadPool>(taskMgr, "QThreadPool"));
        taskVec.push_back(Internal::newTaskRunner<QThread>(taskMgr, "QThread", QThread::HighestPriority));
        taskVec.push_back(Internal::newTaskRunner<Task::StdAsync>(taskMgr, "std::async()"));
        taskVec.push_back(Internal::newTaskRunner<Task::CurrentThread>(taskMgr, "CurrentThread"));
    }

    std::size_t taskCount = taskVec.size();
    std::unordered_map<quint64, bool> taskWorkDone;
    for (const auto task : taskVec)
        taskWorkDone.emplace(task->taskId(), false);

    QObject::connect(taskMgr, &Task::Manager::ended,
                     [&](quint64 taskId) {
        --taskCount;

        auto it = taskWorkDone.find(taskId);
        if (it != taskWorkDone.cend())
            (*it).second = true;

        if (Internal::debugOutput)
            qDebug() << "Ended:" << taskId << taskMgr->taskTitle(taskId);

        QVERIFY(taskMgr->taskProgress(taskId) != nullptr);
    } );

    for (auto task : taskVec)
        task->run( [=] {
            task->progress().outputMessage(QString("-- Function %1 --")
                                           .arg(task->taskId()));
        } );

    QTime chrono;
    chrono.start();
    while (taskCount > 0 && chrono.elapsed() < 5000)
        QCoreApplication::processEvents();
    QCOMPARE(taskCount, static_cast<std::size_t>(0));
    QCOMPARE(taskWorkDone.size(), taskVec.size());
    for (const auto& mapPair : taskWorkDone) {
        QVERIFY(mapPair.second);
        QCOMPARE(taskMgr->taskProgress(mapPair.first), static_cast<Task::Progress*>(nullptr));
    }
}
#endif // FOUGTOOLS_HAVE_QTTOOLS_TASK