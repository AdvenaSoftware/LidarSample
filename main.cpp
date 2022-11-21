#include <iostream>
#include <rplidar.h>


int main(int argc, char* argv[]) {
rp::standalone::rplidar::RPlidarDriver* lidar = rp::standalone::rplidar::RPlidarDriver::CreateDriver();
//rp::standalone::rplidar::RPlidarDriver::DisposeDriver(lidar); //Lidar' ın instance' ınımı dispose ediyor ?

u_result result = lidar->connect("/dev/ttyUSB0", 115200);

    if (IS_OK(result))
        lidar->disconnect();

    else
        fprintf(stderr, "Failed to connect to lidar %08x\r\n",result);

//Start spining motor and stopping motor
lidar-> startMotor();
//lidar->stopMotor();

//Start Scan
std::vector<rp::standalone::rplidar::RplidarScanMode> scanModes;
lidar->getAllSupportedScanModes(scanModes);

//Way1
lidar->startScanExpress(false,scanModes[0].id);

//Way2
/*rp::standalone::rplidar::RplidarScanMode scanMode;
lidar->startScan(false, true,0,&scanMode);*/

//Grab Scan Data
    rplidar_response_measurement_node_hq_t nodes[8192];
    size_t nodeCount = sizeof(nodes)/sizeof(rplidar_response_measurement_node_hq_t);
    result = lidar->grabScanDataHq(nodes, nodeCount);

    if (IS_FAIL(result))
    {
        // failed to get scan data
        puts("Something went wrong. Lidar can not measure the distance. Please check the codes.");
    }

#if defined(_WIN32)
#pragma pack(1)
#endif

    typedef struct rplidar_response_measurement_node_hq_t {
        _u16   angle_z_q14;
        _u32   dist_mm_q2;
        _u8    quality;
        _u8    flag;
    } __attribute__((packed)) rplidar_response_measurement_node_hq_t;

#if defined(_WIN32)
#pragma pack()
#endif


    float angle_in_degrees = node.angle_z_q14 * 90.f / (1 << 14);
    float distance_in_meters = node.dist_mm_q2 / 1000.f / (1 << 2);

}
