#pragma once
#include <vector>
#include <string>
#include "SRC/BusinessLogic/Report.h"
#include "SRC/BusinessLogic/RecordString.h"
#include <memory>


class GraphicBuilder{
public:
    GraphicBuilder(std::shared_ptr<Report>& report);
    std::pair<double,double> getMinMaxSum();
    std::vector<std::pair<std::string,double>> getPoints();
private:
    std::shared_ptr<Report> pReport;
    std::vector<std::pair<std::string,double>> points;

    void calculatePoints();
};


