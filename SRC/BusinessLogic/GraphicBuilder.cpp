#include "GraphicBuilder.h"

GraphicBuilder::GraphicBuilder(std::shared_ptr<Report> &report):pReport(report){}

std::pair<double,double> GraphicBuilder::getMinMaxSum(){
    calculatePoints();
    double max=points[0].second;
    double min=points[0].second;
    for(int i=0;i<static_cast<int>(points.size());++i){
        if(points[i].second>max) max=points[i].second;
        if(points[i].second<min) min=points[i].second;
    }
    return {min,max};
}

std::vector<std::pair<std::string,double>> GraphicBuilder::getPoints(){
    calculatePoints();
    return points;
}

void GraphicBuilder::calculatePoints(){
    points.clear();
    points.resize(pReport->rowsCount());
    double sumPoint=0;
    for(int row=0;row<pReport->rowsCount();++row){
        RecordString record=pReport->getRow(row);
        double recordSum=record.getSum();
        std::string type=record.getType();
        if(type=="Прибыль") sumPoint+=recordSum;
        else sumPoint-=recordSum;
        points.push_back({record.getDate(),sumPoint});
    }
}
