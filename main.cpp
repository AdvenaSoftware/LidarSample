#include <iostream>
#include <rplidar.h>

int main() {
    rp::standalone::rplidar::RPlidarDriver* lidar = rp::standalone::rplidar::RPlidarDriver::CreateDriver();

    u_result result = lidar->connect("/dev/ttyUSB0", 115200);
    if (IS_OK(result)){
        puts("CONNECTION STATUS : SUCCESSFUL. RPLIDAR ALL EARS");
        lidar->startMotor();
        std::vector<rp::standalone::rplidar::RplidarScanMode> scanModes;
        lidar->getAllSupportedScanModes(scanModes);

        lidar ->startScanExpress(false, scanModes[0].id);

        rplidar_response_measurement_node_hq_t nodes[8192];
        size_t nodeCount= sizeof(nodes)/sizeof(rplidar_response_measurement_node_hq_t);
        result = lidar->grabScanDataHq(nodes,nodeCount);
        if (IS_FAIL(result))
            puts("Something went wrong. Lidar can not measure the distance. Please check the codes");

    }
}
