#include "InputChange.hpp"

/**
 * @brief Construct a new Input Change:: Input Change object
 */
InputChange::InputChange() : timeDiff(0), controller() {}

/**
 * @brief Initializes (or re-initializes) this Input Change
 *
 * @param timeDiff time elapsed between controller inputs in ms.
 * @param firstReport the first controller input report
 * @param secondReport the second controller input report
 */
void InputChange::initialize(const uint16_t timeDiff,
                             const Gamecube_Report_t &firstReport,
                             const Gamecube_Report_t &secondReport) {
    this->timeDiff = timeDiff;
    storeChanges(firstReport, secondReport);
}

/**
 * @brief Stores the changes between both controller reports
 */
void InputChange::storeChanges(const Gamecube_Report_t &firstReport,
                               const Gamecube_Report_t &secondReport) {
    controller.a = firstReport.a != secondReport.a;
    controller.b = firstReport.b != secondReport.b;
    controller.x = firstReport.x != secondReport.x;
    controller.y = firstReport.y != secondReport.y;
    controller.z = firstReport.z != secondReport.z;
    controller.l = firstReport.l != secondReport.l;
    controller.r = firstReport.r != secondReport.r;

    controller.lAnalog = secondReport.left;
    controller.rAnalog = secondReport.right;
    controller.xAxis = secondReport.xAxis;
    controller.yAxis = secondReport.yAxis;
    controller.cxAxis = secondReport.cxAxis;
    controller.cyAxis = secondReport.cyAxis;
}

/**
 * @brief Returns the time elapsed between input changes in ms.
 */
uint16_t InputChange::getTimeDiff() { return timeDiff; }

/**
 * @brief Applies this stored input change to a given reference of a
 * controller's data.
 *
 * @param dataToModify a given controller's data
 */
void InputChange::applyTo(Gamecube_Data_t &dataToModify) {
    dataToModify.report.a =
        controller.a ? !dataToModify.report.a : dataToModify.report.a;
    dataToModify.report.b =
        controller.b ? !dataToModify.report.b : dataToModify.report.b;
    dataToModify.report.x =
        controller.x ? !dataToModify.report.x : dataToModify.report.x;
    dataToModify.report.y =
        controller.y ? !dataToModify.report.y : dataToModify.report.y;
    dataToModify.report.z =
        controller.z ? !dataToModify.report.z : dataToModify.report.z;
    dataToModify.report.l =
        controller.l ? !dataToModify.report.l : dataToModify.report.l;
    dataToModify.report.r =
        controller.r ? !dataToModify.report.r : dataToModify.report.r;

    dataToModify.report.left = controller.lAnalog;
    dataToModify.report.right = controller.rAnalog;
    dataToModify.report.xAxis = controller.xAxis;
    dataToModify.report.yAxis = controller.yAxis;
    dataToModify.report.cxAxis = controller.cxAxis;
    dataToModify.report.cyAxis = controller.cyAxis;
}