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

}
