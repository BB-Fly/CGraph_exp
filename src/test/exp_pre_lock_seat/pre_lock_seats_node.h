#ifndef PRE_LOCK_SEATS_NODE_H_
#define PRE_LOCK_SEATS_NODE_H_

#include "CGraph/CGraph.h"
#include "time.h"
#include <sys/time.h>

void sleep_ms(uint32_t ms) {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = ms * 1000;
    select(NULL, NULL, NULL, NULL, &tv);
}

// 添加订单到carpool池
class AddOrderToCarpoolPool :public CGraph::GNode {
    CStatus run() override {
        printf("AddOrderToCarpoolPool run\n"); 
        sleep_ms(100);
        return CStatus();
    }
};

// 添加订单到pre_lock池
class AddOrderToPreLockPool :public CGraph::GNode {
    CStatus run() override {
        printf("AddOrderToPreLockPool run\n");
        sleep_ms(50);
        return CStatus();
    }
};

// 初始化上下文
class InitCtx :public CGraph::GNode {
    CStatus run() override {
        printf("InitCtx run\n");
        sleep_ms(5);
        return CStatus();
    }
};

// 从carpool池中召回订单
class RecallOrderFromCarpoolPool :public CGraph::GNode {
    CStatus run() override {
        printf("RecallOrderFromCarpoolPool run\n");
        sleep_ms(180);
        return CStatus();
    }
};

// 从pre_lock池中召回订单
class RecallOrderFromPreLockPool :public CGraph::GNode {
    CStatus run() override {
        printf("RecallOrderFromPreLockPool run\n");
        sleep_ms(30);
        return CStatus();
    }
};

class LockShift :public CGraph::GNode {
    CStatus run() override {
        printf("LockShift run\n");
        sleep_ms(10);
        return CStatus();
    }
};

class GetForasInfo :public CGraph::GNode {
    CStatus run() override {
        printf("GetForasInfo run\n");
        sleep_ms(10);
        return CStatus();
    }
};

class SetShiftVersion :public CGraph::GNode {
    CStatus run() override {
        printf("SetShiftVersion run\n");
        sleep_ms(10);
        return CStatus();
    }
};


class GetShiftInventory :public CGraph::GCondition {
    int choose() override {
        return 1;
    }
};

class GetShiftInventoryFromRedis :public CGraph::GNode {
    CStatus run() override {
        printf("GetShiftInventoryFromRedis run\n");
        sleep_ms(100);
        return CStatus();
    }
};

class GetShiftInventoryFromDB :public CGraph::GNode {
    CStatus run() override {
        printf("GetShiftInventoryFromDB run\n");
        sleep_ms(120);
        return CStatus();
    }
};

class GetPrelockInventory :public CGraph::GNode {
    CStatus run() override {
        printf("GetPrelockInventory run\n");
        sleep_ms(10);
        return CStatus();
    }
};

class AddShiftOrderToStgData :public CGraph::GNode {
    CStatus run() override {
        printf("AddShiftOrderToStgData run\n");
        sleep_ms(100);
        return CStatus();
    }
};

class GetRtFeature :public CGraph::GNode {
    CStatus run() override {
        printf("GetRtFeature run\n");
        sleep_ms(80);
        return CStatus();
    }
};

class TryOccupySeats :public CGraph::GNode {
    CStatus run() override {
        printf("TryOccupySeats run\n");
        sleep_ms(5);
        return CStatus();
    }
};

class ApiCheck :public CGraph::GNode {
    CStatus run() override {
        printf("ApiCheck run\n");
        sleep_ms(50);
        return CStatus();
    }
};

class DelOrderFromPreLockPool :public CGraph::GNode {
    CStatus run() override {
        printf("DelOrderFromPreLockPool run\n");
        sleep_ms(50);
        return CStatus();
    }
};

class DelOrderFromCarpoolPool :public CGraph::GNode {
    CStatus run() override {
        printf("DelOrderFromCarpoolPool run\n");
        sleep_ms(50);
        return CStatus();
    }
};

class LockSeats :public CGraph::GNode {
    CStatus run() override {
        printf("LockSeats run\n");
        sleep_ms(30);
        return CStatus();
    }
};

class UnlockShift :public CGraph::GNode {
    CStatus run() override {
        printf("UnlockShift run\n");
        sleep_ms(10);
        return CStatus();
    }
};

class AlreadyLocked :public CGraph::GNode {
    CStatus run() override {
        printf("AlreadyLocked run\n");
        sleep_ms(10);
        return CStatus();
    }
};

#endif // PRE_LOCK_SEATS_NODE_H_