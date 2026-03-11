#include "Nodes.h"

#include "Utils.h"
#include "CGraph/CGraph.h"
#include "pre_lock_seats_node.h"

using namespace CGraph;

int main() {

    auto pipeline = GPipelineFactory::create();

    // 创建节点
    GElementPtr addOrderToPool = pipeline->createGGroup<GRegion>({
        pipeline->createGNode<AddOrderToCarpoolPool>({}, "AddOrderToCarpoolPool", 1),
        pipeline->createGNode<AddOrderToPreLockPool>({}, "AddOrderToPreLockPool", 1),
    });
    pipeline->registerGGroup(&addOrderToPool, {}, "AddOrderToPool", 1);

    auto initCtx = pipeline->registerGNode<InitCtx>({}, "InitCtx", 1);

    GElementPtr recallOrderFromPool = pipeline->createGGroup<GCluster>({
        pipeline->createGNode<RecallOrderFromCarpoolPool>({}, "RecallOrderFromCarpoolPool", 1),
        pipeline->createGNode<RecallOrderFromPreLockPool>({}, "RecallOrderFromPreLockPool", 1),
    });
    pipeline->registerGGroup(&recallOrderFromPool, {initCtx}, "RecallOrderFromPool", 1);

    auto lockShift = pipeline->registerGNode<LockShift>({recallOrderFromPool}, "LockShift", 1);
    
    auto getForasInfo = pipeline->registerGNode<GetForasInfo>({lockShift}, "GetForasInfo", 1);
    auto setShiftVersion = pipeline->registerGNode<SetShiftVersion>({lockShift}, "SetShiftVersion", 1);
    auto getPrelockInventory = pipeline->registerGNode<GetPrelockInventory>({lockShift}, "GetPrelockInventory", 1);
    
    GElementPtr getShiftInventory = pipeline->createGGroup<GetShiftInventory>({
        pipeline->createGNode<GetShiftInventoryFromRedis>({}, "GetShiftInventoryFromRedis", 1),
        pipeline->createGNode<GetShiftInventoryFromDB>({}, "GetShiftInventoryFromDB", 1),
    });
    pipeline->registerGGroup(&getShiftInventory, {getForasInfo}, "GetShiftInventory", 1);

    auto addShiftOrderToStgData = pipeline->registerGNode<AddShiftOrderToStgData>({getShiftInventory, setShiftVersion, getPrelockInventory}, "AddShiftOrderToStgData", 1);

    auto getRtFeature = pipeline->registerGNode<GetRtFeature>({addShiftOrderToStgData}, "GetRtFeature", 1);

    auto tryOccupySeats = pipeline->registerGNode<TryOccupySeats>({getRtFeature}, "TryOccupySeats", 1);

    auto apiCheck = pipeline->registerGNode<ApiCheck>({tryOccupySeats}, "ApiCheck", 1);

    auto lockSeats = pipeline->registerGNode<LockSeats>({apiCheck}, "LockSeats", 1);

    auto unlockShiftFirst = pipeline->registerGNode<UnlockShift>({lockSeats}, "UnlockShiftFirst", 1);

    GElementPtr delOrderFromPool = pipeline->createGGroup<GRegion>({
        pipeline->createGNode<DelOrderFromCarpoolPool>({}, "DelOrderFromCarpoolPool", 1),
        pipeline->createGNode<DelOrderFromPreLockPool>({}, "DelOrderFromPreLockPool", 1),
    });
    pipeline->registerGGroup(&delOrderFromPool, {lockSeats}, "DelOrderFromPool", 1);

    auto unlockShiftSecond = pipeline->registerGNode<UnlockShift>({delOrderFromPool}, "UnlockShiftSecond", 1);

    auto alreadyLocked = pipeline->registerGNode<AlreadyLocked>({lockSeats}, "AlreadyLocked", 1);

    // 留存pipeline结构信息
    pipeline->dump();
    pipeline->perf();

    // 运行pipeline
    pipeline->init();
    pipeline->run();
    pipeline->destroy();
    return 0;
}