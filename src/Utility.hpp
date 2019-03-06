#ifndef SASC_UTILITY_HPP_
#define SASC_UTILITY_HPP_

#ifdef DEBUG
/**
 * @brief Prints each of the report's vars to Serial
 *
 * @param report
 */
inline void printReport(Gamecube_Report_t &report) {
    Serial.println();
    Serial.println(F("Printing Gamecube controller report:"));
    Serial.print(F("Start:\t"));
    Serial.println(report.start);

    Serial.print(F("Y:\t"));
    Serial.println(report.y);

    Serial.print(F("X:\t"));
    Serial.println(report.x);

    Serial.print(F("B:\t"));
    Serial.println(report.b);

    Serial.print(F("A:\t"));
    Serial.println(report.a);

    Serial.print(F("L:\t"));
    Serial.println(report.l);
    Serial.print(F("R:\t"));
    Serial.println(report.r);
    Serial.print(F("Z:\t"));
    Serial.println(report.z);

    Serial.print(F("Dup:\t"));
    Serial.println(report.dup);
    Serial.print(F("Ddown:\t"));
    Serial.println(report.ddown);
    Serial.print(F("Dright:\t"));
    Serial.println(report.dright);
    Serial.print(F("Dleft:\t"));
    Serial.println(report.dleft);

    Serial.print(F("xAxis:\t"));
    Serial.println(report.xAxis, DEC);
    Serial.print(F("yAxis:\t"));
    Serial.println(report.yAxis, DEC);

    Serial.print(F("cxAxis:\t"));
    Serial.println(report.cxAxis, DEC);
    Serial.print(F("cyAxis:\t"));
    Serial.println(report.cyAxis, DEC);

    Serial.print(F("L:\t"));
    Serial.println(report.left, DEC);
    Serial.print(F("R:\t"));
    Serial.println(report.right, DEC);
    Serial.println();
}
#endif
/**
 * @brief Zeroes the DPad inputs from the given controller data
 *
 * @param dataToModify given controller data
 */
inline void removeDPadInputs(Gamecube_Data_t &dataToModify) {
    dataToModify.report.dleft = 0;
    dataToModify.report.dup = 0;
    dataToModify.report.dright = 0;
    dataToModify.report.ddown = 0;
}

/**
 * @brief Sets the given X and Y axis vars to be fully in one direction (i.e.
 * one var will be either MAX_AXIS_VAL or MIN_AXIS_VAL, the other will be
 * between that range)
 *
 * @param xAxis var representing X Axis
 * @param yAxis var representing Y Axis
 */
inline void setInRandomDirection(uint8_t &xAxis, uint8_t &yAxis) {
    // determine random axis to set min/max value
    bool useXAxis = (rand() % 2) == 0;
    // randomly choose whether to set previous axis to min or max value
    bool useMaxVal = (rand() % 2) == 0;

    // set the other axis to a random value
    if (useXAxis) {
        xAxis = useMaxVal ? MAX_AXIS_VAL : MIN_AXIS_VAL;
        yAxis = rand() % (MAX_AXIS_VAL - MIN_AXIS_VAL) + MIN_AXIS_VAL + 1;
    } else {
        xAxis = rand() % (MAX_AXIS_VAL - MIN_AXIS_VAL) + MIN_AXIS_VAL + 1;
        yAxis = useMaxVal ? MAX_AXIS_VAL : MIN_AXIS_VAL;
    }
}

#endif // SASC_UTILITY_HPP_