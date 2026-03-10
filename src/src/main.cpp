/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: main.cpp
@Time: 2024/1/1 11:00 下午
@Desc: 主文件
***************************/

#include "Nodes.h"
#include "Utils.h"
#include "CGraph/CGraph.h"

int main() {
    // 读取请求数据
    auto requests = Utils::readRequests("src/data/requests.json");
    
    // 处理每个请求
    for (const auto& request : requests) {
        // 创建图
        auto pipeline = CGraph::GPipelineFactory::create();
        
        // 注册节点
        auto dataLoadNode = pipeline->registerGNode<DataLoadNode>({});
        auto recallNode = pipeline->registerGNode<RecallNode>({dataLoadNode});
        auto seatFilterNode = pipeline->registerGNode<SeatFilterNode>({recallNode});
        auto timeFilterNode = pipeline->registerGNode<TimeFilterNode>({seatFilterNode});
        auto distanceFilterNode = pipeline->registerGNode<DistanceFilterNode>({timeFilterNode});
        auto sortNode = pipeline->registerGNode<SortNode>({distanceFilterNode});
        auto paginateNode = pipeline->registerGNode<PaginateNode>({sortNode});
        auto resultNode = pipeline->registerGNode<ResultNode>({paginateNode});
        
        // 运行图
        CStatus status = pipeline->init();
        if (!status.isOK()) {
            std::cout << "Pipeline init failed: " << status.getInfo() << std::endl;
            return -1;
        }
        
        status = pipeline->run();
        if (!status.isOK()) {
            std::cout << "Pipeline run failed: " << status.getInfo() << std::endl;
            return -1;
        }
        
        // 清理
        pipeline->destroy();
        CGraph::GPipelineFactory::remove(pipeline);
        
        std::cout << "\n------------------------\n" << std::endl;
    }
    
    return 0;
}