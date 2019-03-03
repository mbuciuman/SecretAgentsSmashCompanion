#ifndef SASC_PRINTREPORT_HPP_
#define SASC_PRINTREPORT_HPP_

/**
 * @brief Class with utility method for printing Gamecube Report vars.
 *
 */
class PrintReport {
  public:
    /**
     * @brief Prints the controller report to Serial
     *
     * @param report given controller report
     */
    static void printReport(Gamecube_Report_t &report) {
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
};

#endif // SASC_PRINTREPORT_HPP_