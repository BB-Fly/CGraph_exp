/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: Utils.h
@Time: 2024/1/1 10:30 下午
@Desc: 工具类
***************************/

#ifndef CGRAPH_EXP_UTILS_H
#define CGRAPH_EXP_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "DataModel.h"

class Utils {
public:
    // 计算两个坐标之间的距离（单位：公里）
    static double calculateDistance(const Coordinate& coord1, const Coordinate& coord2) {
        const double R = 6371.0; // 地球半径
        double lat1 = coord1.latitude * M_PI / 180.0;
        double lon1 = coord1.longitude * M_PI / 180.0;
        double lat2 = coord2.latitude * M_PI / 180.0;
        double lon2 = coord2.longitude * M_PI / 180.0;
        
        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;
        double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double distance = R * c;
        
        return distance;
    }
    
    // 从文件读取班次数据（简化版，直接返回预设数据）
    static std::vector<Schedule> readSchedules(const std::string& file_path) {
        std::vector<Schedule> schedules;
        
        // 创建预设班次数据
        Schedule sch1;
        sch1.id = "SCH001";
        sch1.city = "北京";
        sch1.total_seats = 50;
        sch1.remaining_seats = 30;
        sch1.departure_time = "2024-01-01 08:00:00";
        
        Station station1_1;
        station1_1.name = "北京站";
        station1_1.coord.latitude = 39.9042;
        station1_1.coord.longitude = 116.4074;
        station1_1.arrive_time = "2024-01-01 07:45:00";
        station1_1.depart_time = "2024-01-01 08:00:00";
        sch1.stations.push_back(station1_1);
        
        Station station1_2;
        station1_2.name = "北京南站";
        station1_2.coord.latitude = 39.8651;
        station1_2.coord.longitude = 116.3786;
        station1_2.arrive_time = "2024-01-01 08:30:00";
        station1_2.depart_time = "2024-01-01 08:40:00";
        sch1.stations.push_back(station1_2);
        
        Station station1_3;
        station1_3.name = "天津站";
        station1_3.coord.latitude = 39.0842;
        station1_3.coord.longitude = 117.2009;
        station1_3.arrive_time = "2024-01-01 09:30:00";
        station1_3.depart_time = "2024-01-01 09:40:00";
        sch1.stations.push_back(station1_3);
        
        schedules.push_back(sch1);
        
        Schedule sch2;
        sch2.id = "SCH002";
        sch2.city = "北京";
        sch2.total_seats = 40;
        sch2.remaining_seats = 5;
        sch2.departure_time = "2024-01-01 09:00:00";
        
        Station station2_1;
        station2_1.name = "北京站";
        station2_1.coord.latitude = 39.9042;
        station2_1.coord.longitude = 116.4074;
        station2_1.arrive_time = "2024-01-01 08:45:00";
        station2_1.depart_time = "2024-01-01 09:00:00";
        sch2.stations.push_back(station2_1);
        
        Station station2_2;
        station2_2.name = "北京西站";
        station2_2.coord.latitude = 39.8586;
        station2_2.coord.longitude = 116.3286;
        station2_2.arrive_time = "2024-01-01 09:20:00";
        station2_2.depart_time = "2024-01-01 09:30:00";
        sch2.stations.push_back(station2_2);
        
        Station station2_3;
        station2_3.name = "石家庄站";
        station2_3.coord.latitude = 38.0457;
        station2_3.coord.longitude = 114.4995;
        station2_3.arrive_time = "2024-01-01 11:00:00";
        station2_3.depart_time = "2024-01-01 11:10:00";
        sch2.stations.push_back(station2_3);
        
        schedules.push_back(sch2);
        
        Schedule sch3;
        sch3.id = "SCH003";
        sch3.city = "北京";
        sch3.total_seats = 60;
        sch3.remaining_seats = 40;
        sch3.departure_time = "2024-01-01 10:00:00";
        
        Station station3_1;
        station3_1.name = "北京南站";
        station3_1.coord.latitude = 39.8651;
        station3_1.coord.longitude = 116.3786;
        station3_1.arrive_time = "2024-01-01 09:45:00";
        station3_1.depart_time = "2024-01-01 10:00:00";
        sch3.stations.push_back(station3_1);
        
        Station station3_2;
        station3_2.name = "天津站";
        station3_2.coord.latitude = 39.0842;
        station3_2.coord.longitude = 117.2009;
        station3_2.arrive_time = "2024-01-01 10:50:00";
        station3_2.depart_time = "2024-01-01 11:00:00";
        sch3.stations.push_back(station3_2);
        
        Station station3_3;
        station3_3.name = "济南站";
        station3_3.coord.latitude = 36.6683;
        station3_3.coord.longitude = 117.0207;
        station3_3.arrive_time = "2024-01-01 13:00:00";
        station3_3.depart_time = "2024-01-01 13:10:00";
        sch3.stations.push_back(station3_3);
        
        schedules.push_back(sch3);
        
        Schedule sch4;
        sch4.id = "SCH004";
        sch4.city = "上海";
        sch4.total_seats = 55;
        sch4.remaining_seats = 25;
        sch4.departure_time = "2024-01-01 08:30:00";
        
        Station station4_1;
        station4_1.name = "上海站";
        station4_1.coord.latitude = 31.2304;
        station4_1.coord.longitude = 121.4737;
        station4_1.arrive_time = "2024-01-01 08:15:00";
        station4_1.depart_time = "2024-01-01 08:30:00";
        sch4.stations.push_back(station4_1);
        
        Station station4_2;
        station4_2.name = "上海南站";
        station4_2.coord.latitude = 31.1629;
        station4_2.coord.longitude = 121.4366;
        station4_2.arrive_time = "2024-01-01 08:50:00";
        station4_2.depart_time = "2024-01-01 09:00:00";
        sch4.stations.push_back(station4_2);
        
        Station station4_3;
        station4_3.name = "杭州站";
        station4_3.coord.latitude = 30.2741;
        station4_3.coord.longitude = 120.1551;
        station4_3.arrive_time = "2024-01-01 10:30:00";
        station4_3.depart_time = "2024-01-01 10:40:00";
        sch4.stations.push_back(station4_3);
        
        schedules.push_back(sch4);
        
        Schedule sch5;
        sch5.id = "SCH005";
        sch5.city = "上海";
        sch5.total_seats = 45;
        sch5.remaining_seats = 10;
        sch5.departure_time = "2024-01-01 09:30:00";
        
        Station station5_1;
        station5_1.name = "上海站";
        station5_1.coord.latitude = 31.2304;
        station5_1.coord.longitude = 121.4737;
        station5_1.arrive_time = "2024-01-01 09:15:00";
        station5_1.depart_time = "2024-01-01 09:30:00";
        sch5.stations.push_back(station5_1);
        
        Station station5_2;
        station5_2.name = "南京站";
        station5_2.coord.latitude = 32.0603;
        station5_2.coord.longitude = 118.7969;
        station5_2.arrive_time = "2024-01-01 11:30:00";
        station5_2.depart_time = "2024-01-01 11:40:00";
        sch5.stations.push_back(station5_2);
        
        schedules.push_back(sch5);
        
        Schedule sch6;
        sch6.id = "SCH006";
        sch6.city = "广州";
        sch6.total_seats = 50;
        sch6.remaining_seats = 35;
        sch6.departure_time = "2024-01-01 10:00:00";
        
        Station station6_1;
        station6_1.name = "广州站";
        station6_1.coord.latitude = 23.1291;
        station6_1.coord.longitude = 113.2644;
        station6_1.arrive_time = "2024-01-01 09:45:00";
        station6_1.depart_time = "2024-01-01 10:00:00";
        sch6.stations.push_back(station6_1);
        
        Station station6_2;
        station6_2.name = "深圳站";
        station6_2.coord.latitude = 22.5431;
        station6_2.coord.longitude = 114.0579;
        station6_2.arrive_time = "2024-01-01 11:30:00";
        station6_2.depart_time = "2024-01-01 11:40:00";
        sch6.stations.push_back(station6_2);
        
        schedules.push_back(sch6);
        
        return schedules;
    }
    
    // 从文件读取用户请求数据（简化版，直接返回预设数据）
    static std::vector<UserRequest> readRequests(const std::string& file_path) {
        std::vector<UserRequest> requests;
        
        // 创建预设请求数据
        UserRequest req1;
        req1.id = "REQ001";
        req1.required_seats = 2;
        req1.departure_time = "2024-01-01 08:00:00";
        req1.city = "北京";
        req1.start_coord.latitude = 39.9042;
        req1.start_coord.longitude = 116.4074;
        req1.end_coord.latitude = 39.0842;
        req1.end_coord.longitude = 117.2009;
        req1.page_size = 10;
        req1.page_num = 1;
        requests.push_back(req1);
        
        UserRequest req2;
        req2.id = "REQ002";
        req2.required_seats = 5;
        req2.departure_time = "2024-01-01 09:00:00";
        req2.city = "北京";
        req2.start_coord.latitude = 39.8586;
        req2.start_coord.longitude = 116.3286;
        req2.end_coord.latitude = 38.0457;
        req2.end_coord.longitude = 114.4995;
        req2.page_size = 10;
        req2.page_num = 1;
        requests.push_back(req2);
        
        UserRequest req3;
        req3.id = "REQ003";
        req3.required_seats = 3;
        req3.departure_time = "2024-01-01 10:00:00";
        req3.city = "上海";
        req3.start_coord.latitude = 31.2304;
        req3.start_coord.longitude = 121.4737;
        req3.end_coord.latitude = 30.2741;
        req3.end_coord.longitude = 120.1551;
        req3.page_size = 10;
        req3.page_num = 1;
        requests.push_back(req3);
        
        UserRequest req4;
        req4.id = "REQ004";
        req4.required_seats = 10;
        req4.departure_time = "2024-01-01 08:30:00";
        req4.city = "上海";
        req4.start_coord.latitude = 31.1629;
        req4.start_coord.longitude = 121.4366;
        req4.end_coord.latitude = 30.2741;
        req4.end_coord.longitude = 120.1551;
        req4.page_size = 10;
        req4.page_num = 1;
        requests.push_back(req4);
        
        UserRequest req5;
        req5.id = "REQ005";
        req5.required_seats = 2;
        req5.departure_time = "2024-01-01 10:00:00";
        req5.city = "广州";
        req5.start_coord.latitude = 23.1291;
        req5.start_coord.longitude = 113.2644;
        req5.end_coord.latitude = 22.5431;
        req5.end_coord.longitude = 114.0579;
        req5.page_size = 10;
        req5.page_num = 1;
        requests.push_back(req5);
        
        return requests;
    }
    
    // 格式化时间字符串为时间戳
    static time_t formatTime(const std::string& time_str) {
        struct tm tm_time = {0};
        strptime(time_str.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);
        return mktime(&tm_time);
    }
};

#endif // CGRAPH_EXP_UTILS_H