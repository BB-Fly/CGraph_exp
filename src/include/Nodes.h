/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: Nodes.h
@Time: 2024/1/1 10:40 下午
@Desc: CGraph节点定义
***************************/

#ifndef CGRAPH_EXP_NODES_H
#define CGRAPH_EXP_NODES_H

#include "DataModel.h"
#include "Utils.h"
#include "CGraph/CGraph.h"

// 上下文结构，继承自GParam
struct ScheduleContext : public CGraph::GParam {
    std::vector<Schedule> all_schedules;
    std::vector<Schedule> recalled_schedules;
    std::vector<Schedule> filtered_schedules;
    std::vector<Schedule> sorted_schedules;
    std::vector<Schedule> paginated_schedules;
    UserRequest request;
    Response response;
    bool has_schedules = false;
};

// 数据加载节点
class DataLoadNode : public CGraph::GNode {
public:
    CStatus run() override {
        // 创建上下文参数
        auto status = this->createGParam<ScheduleContext>("schedule_context");
        if (!status.isOK()) {
            return status;
        }
        
        // 获取上下文
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 读取班次数据
        context->all_schedules = Utils::readSchedules("src/data/schedules.json");
        std::cout << "DataLoadNode: Loaded " << context->all_schedules.size() << " schedules" << std::endl;
        
        // 读取请求数据（这里简化处理，只取第一个请求）
        auto requests = Utils::readRequests("src/data/requests.json");
        if (!requests.empty()) {
            context->request = requests[0];
        }
        
        return CStatus();
    }
};

// 召回节点
class RecallNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 根据城市召回班次
        const std::string& city = context->request.city;
        for (const auto& schedule : context->all_schedules) {
            if (schedule.city == city) {
                context->recalled_schedules.push_back(schedule);
            }
        }
        
        std::cout << "RecallNode: Recalled " << context->recalled_schedules.size() << " schedules for city " << city << std::endl;
        context->has_schedules = !context->recalled_schedules.empty();
        
        return CStatus();
    }
};

// 座位过滤节点
class SeatFilterNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 过滤座位数
        int required_seats = context->request.required_seats;
        for (const auto& schedule : context->recalled_schedules) {
            if (schedule.remaining_seats >= required_seats) {
                context->filtered_schedules.push_back(schedule);
            }
        }
        
        std::cout << "SeatFilterNode: Filtered to " << context->filtered_schedules.size() << " schedules with at least " << required_seats << " seats" << std::endl;
        context->has_schedules = !context->filtered_schedules.empty();
        
        return CStatus();
    }
};

// 时间过滤节点
class TimeFilterNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 过滤时间
        time_t request_time = Utils::formatTime(context->request.departure_time);
        std::vector<Schedule> temp_schedules;
        
        for (const auto& schedule : context->filtered_schedules) {
            time_t schedule_time = Utils::formatTime(schedule.departure_time);
            // 只保留发车时间大于等于请求时间的班次
            if (schedule_time >= request_time) {
                temp_schedules.push_back(schedule);
            }
        }
        
        context->filtered_schedules.swap(temp_schedules);
        std::cout << "TimeFilterNode: Filtered to " << context->filtered_schedules.size() << " schedules with departure time >= " << context->request.departure_time << std::endl;
        context->has_schedules = !context->filtered_schedules.empty();
        
        return CStatus();
    }
};

// 距离过滤节点
class DistanceFilterNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 计算距离并过滤
        const Coordinate& start_coord = context->request.start_coord;
        const Coordinate& end_coord = context->request.end_coord;
        std::vector<Schedule> temp_schedules;
        
        for (auto schedule : context->filtered_schedules) {
            // 计算与起始站点的距离
            double min_start_distance = std::numeric_limits<double>::max();
            double min_end_distance = std::numeric_limits<double>::max();
            
            for (const auto& station : schedule.stations) {
                double start_distance = Utils::calculateDistance(start_coord, station.coord);
                double end_distance = Utils::calculateDistance(end_coord, station.coord);
                if (start_distance < min_start_distance) {
                    min_start_distance = start_distance;
                }
                if (end_distance < min_end_distance) {
                    min_end_distance = end_distance;
                }
            }
            
            // 计算总距离
            schedule.distance = min_start_distance + min_end_distance;
            
            // 过滤距离阈值（这里设置为50公里）
            if (min_start_distance <= 50 && min_end_distance <= 50) {
                temp_schedules.push_back(schedule);
            }
        }
        
        context->filtered_schedules.swap(temp_schedules);
        std::cout << "DistanceFilterNode: Filtered to " << context->filtered_schedules.size() << " schedules within distance threshold" << std::endl;
        context->has_schedules = !context->filtered_schedules.empty();
        
        return CStatus();
    }
};

// 排序节点
class SortNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 根据距离排序
        context->sorted_schedules = context->filtered_schedules;
        std::sort(context->sorted_schedules.begin(), context->sorted_schedules.end(), 
            [](const Schedule& a, const Schedule& b) {
                return a.distance < b.distance;
            });
        
        std::cout << "SortNode: Sorted " << context->sorted_schedules.size() << " schedules by distance" << std::endl;
        
        return CStatus();
    }
};

// 分页节点
class PaginateNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 分页处理
        int page_size = context->request.page_size;
        int page_num = context->request.page_num;
        int start_idx = (page_num - 1) * page_size;
        int end_idx = start_idx + page_size;
        
        if (start_idx < context->sorted_schedules.size()) {
            if (end_idx > context->sorted_schedules.size()) {
                end_idx = context->sorted_schedules.size();
            }
            context->paginated_schedules.assign(context->sorted_schedules.begin() + start_idx, 
                                              context->sorted_schedules.begin() + end_idx);
        }
        
        std::cout << "PaginateNode: Paginated to " << context->paginated_schedules.size() << " schedules (page " << page_num << ", size " << page_size << ")" << std::endl;
        
        return CStatus();
    }
};

// 结果处理节点
class ResultNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 处理结果
        context->response.success = true;
        context->response.message = "Success";
        context->response.schedules = context->paginated_schedules;
        context->response.total = context->sorted_schedules.size();
        context->response.page_size = context->request.page_size;
        context->response.page_num = context->request.page_num;
        
        // 输出结果
        std::cout << "ResultNode: Processed result for request " << context->request.id << std::endl;
        std::cout << "Total schedules: " << context->response.total << std::endl;
        std::cout << "Returned schedules: " << context->response.schedules.size() << std::endl;
        for (const auto& schedule : context->response.schedules) {
            std::cout << "  Schedule: " << schedule.id << ", Distance: " << schedule.distance << "km, Departure: " << schedule.departure_time << std::endl;
        }
        
        return CStatus();
    }
};

// 无结果处理节点
class NoResultNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto context = this->getGParam<ScheduleContext>("schedule_context");
        if (!context) {
            return CStatus(-1, "context is null");
        }
        
        // 处理无结果情况
        context->response.success = false;
        context->response.message = "No schedules found";
        context->response.total = 0;
        context->response.page_size = context->request.page_size;
        context->response.page_num = context->request.page_num;
        
        std::cout << "NoResultNode: No schedules found for request " << context->request.id << std::endl;
        
        return CStatus();
    }
};

#endif // CGRAPH_EXP_NODES_H