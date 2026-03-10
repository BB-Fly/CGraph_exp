/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: DataModel.h
@Time: 2024/1/1 10:20 下午
@Desc: 数据模型定义
***************************/

#ifndef CGRAPH_EXP_DATAMODEL_H
#define CGRAPH_EXP_DATAMODEL_H

#include <string>
#include <vector>
#include <chrono>

// 坐标结构
struct Coordinate {
    double latitude;  // 纬度
    double longitude; // 经度
};

// 站点信息
struct Station {
    std::string name;            // 站点名称
    Coordinate coord;            // 站点坐标
    std::string arrive_time;     // 预计到达时间
    std::string depart_time;     // 预计出发时间
};

// 班次信息
struct Schedule {
    std::string id;              // 班次ID
    std::string city;            // 城市
    int total_seats;             // 库存总数
    int remaining_seats;         // 剩余库存数
    std::string departure_time;  // 发车时间
    std::vector<Station> stations; // 站点列表
    double distance;             // 与用户的距离（计算后填充）
};

// 用户请求信息
struct UserRequest {
    std::string id;              // 请求ID
    int required_seats;          // 座位数
    std::string departure_time;  // 乘车时间
    std::string city;            // 城市
    Coordinate start_coord;      // 上车坐标
    Coordinate end_coord;        // 下车坐标
    int page_size;               // 分页大小
    int page_num;                // 页码
};

// 响应结果
struct Response {
    bool success;                // 是否成功
    std::string message;         // 消息
    std::vector<Schedule> schedules; // 推荐班次列表
    int total;                   // 总数
    int page_size;               // 分页大小
    int page_num;                // 页码
};

#endif // CGRAPH_EXP_DATAMODEL_H