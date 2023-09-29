const int MPU_addr=0x68;
double MPU_AcX,MPU_AcY,MPU_AcZ,MPU_Tmp,MPU_GyX,MPU_GyY,MPU_GyZ; //These will be the raw data from the MPU6050.
uint32_t MPU_timer; //it's a timer, saved as a big-ass unsigned int.  We use it to save times from the "micros()" command and subtract the present time in microseconds from the time stored in timer to calculate the time for each loop.
double compAngleX, compAngleY; //These are the angles in the complementary filter
#define MPU_degconvert 57.2957786

