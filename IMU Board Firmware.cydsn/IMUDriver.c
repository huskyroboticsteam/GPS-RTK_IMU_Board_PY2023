#include "IMUDriver.h"


void imu_init()
{
    IMU_RST_Write(!IMU_RST_Read());
    CyDelay(20);
    IMU_RST_Write(!IMU_RST_Read());   
    CyDelay(1000);
    
    IMU_I2C_Start();
    
    I2C_routine();
    //Print("Starting imu init");
    bno055_init(&bno055);
    bno055_set_power_mode(BNO055_POWER_MODE_NORMAL);
    bno055_set_operation_mode(BNO055_OPERATION_MODE_NDOF);
    //bno055_set_accel_unit(BNO055_ACCEL_UNIT_MSQ); //set units of accel to m/s^2
    //bno055_set_gyro_unit(BNO055_GYRO_UNIT_DPS); //set units of rotational speed to degrees per second
    //bno055_set_euler_unit(BNO055_EULER_UNIT_DEG); //set units of euler angle to degrees
    //bno055_set_temp_unit(BNO055_TEMP_UNIT_CELSIUS); //set temp measure as celsius
    
    
}

/*----------------------------------------------------------------------------*
 *  struct bno055_t parameters can be accessed by using BNO055
 *  BNO055_t having the following parameters
 *  Bus write function pointer: BNO055_WR_FUNC_PTR
 *  Bus read function pointer: BNO055_RD_FUNC_PTR
 *  Burst read function pointer: BNO055_BRD_FUNC_PTR
 *  Delay function pointer: delay_msec
 *  I2C address: dev_addr
 *  Chip id of the sensor: chip_id
 *---------------------------------------------------------------------------*/


/* This API is an example for reading sensor data
 *  \param: None
 *  \return: communication result
 */
s32 bno055_data_readout_template(void)
{
    
     /* Variable used to return value of
     * communication routine*/
    comres = BNO055_ERROR;

    /* variable used to set the power mode of the sensor*/
     power_mode = BNO055_INIT_VALUE;

    /*********read raw accel data***********/
    /* variable used to read the accel x data */
    accel_datax = BNO055_INIT_VALUE;

    /* variable used to read the accel y data */
    accel_datay = BNO055_INIT_VALUE;

    /* variable used to read the accel z data */
    accel_dataz = BNO055_INIT_VALUE;

    /* variable used to read the accel xyz data */
    

    /*********read raw mag data***********/
    /* variable used to read the mag x data */
    mag_datax = BNO055_INIT_VALUE;

    /* variable used to read the mag y data */
    mag_datay = BNO055_INIT_VALUE;

    /* variable used to read the mag z data */
    mag_dataz = BNO055_INIT_VALUE;

    /* structure used to read the mag xyz data */
    

    /***********read raw gyro data***********/
    /* variable used to read the gyro x data */
    gyro_datax = BNO055_INIT_VALUE;

    /* variable used to read the gyro y data */
    gyro_datay = BNO055_INIT_VALUE;

    /* variable used to read the gyro z data */
    gyro_dataz = BNO055_INIT_VALUE;

    /* structure used to read the gyro xyz data */
    

    /*************read raw Euler data************/
    /* variable used to read the euler h data */
    euler_data_h = BNO055_INIT_VALUE;

    /* variable used to read the euler r data */
    euler_data_r = BNO055_INIT_VALUE;

    /* variable used to read the euler p data */
    euler_data_p = BNO055_INIT_VALUE;

    /* structure used to read the euler hrp data */
    

    /************read raw quaternion data**************/
    /* variable used to read the quaternion w data */
    quaternion_data_w = BNO055_INIT_VALUE;

    /* variable used to read the quaternion x data */
    quaternion_data_x = BNO055_INIT_VALUE;

    /* variable used to read the quaternion y data */
    quaternion_data_y = BNO055_INIT_VALUE;

    /* variable used to read the quaternion z data */
    quaternion_data_z = BNO055_INIT_VALUE;

    /* structure used to read the quaternion wxyz data */
    

    /************read raw linear acceleration data***********/
    /* variable used to read the linear accel x data */
    linear_accel_data_x = BNO055_INIT_VALUE;

    /* variable used to read the linear accel y data */
    linear_accel_data_y = BNO055_INIT_VALUE;

    /* variable used to read the linear accel z data */
    linear_accel_data_z = BNO055_INIT_VALUE;

    /* structure used to read the linear accel xyz data */
    

    /*****************read raw gravity sensor data****************/
    /* variable used to read the gravity x data */
    gravity_data_x = BNO055_INIT_VALUE;

    /* variable used to read the gravity y data */
    gravity_data_y = BNO055_INIT_VALUE;

    /* variable used to read the gravity z data */
    gravity_data_z = BNO055_INIT_VALUE;

    /* structure used to read the gravity xyz data */
    
    
    /*************read accel converted data***************/
    /* variable used to read the accel x data output as m/s2 or mg */
    accel_datax = BNO055_INIT_VALUE;

    /* variable used to read the accel y data output as m/s2 or mg */
    d_accel_datay = BNO055_INIT_VALUE;

    /* variable used to read the accel z data output as m/s2 or mg */
    d_accel_dataz = BNO055_INIT_VALUE;

    /* structure used to read the accel xyz data output as m/s2 or mg */
    

    /******************read mag converted data********************/
    /* variable used to read the mag x data output as uT*/
    d_mag_datax = BNO055_INIT_VALUE;

    /* variable used to read the mag y data output as uT*/
    d_mag_datay = BNO055_INIT_VALUE;

    /* variable used to read the mag z data output as uT*/
    d_mag_dataz = BNO055_INIT_VALUE;

    /* structure used to read the mag xyz data output as uT*/
    

    /*****************read gyro converted data************************/
    /* variable used to read the gyro x data output as dps or rps */
    d_gyro_datax = BNO055_INIT_VALUE;

    /* variable used to read the gyro y data output as dps or rps */
    d_gyro_datay = BNO055_INIT_VALUE;

    /* variable used to read the gyro z data output as dps or rps */
    d_gyro_dataz = BNO055_INIT_VALUE;

    /* structure used to read the gyro xyz data output as dps or rps */
    

    /*******************read euler converted data*******************/

    /* variable used to read the euler h data output
     * as degree or radians*/
    d_euler_data_h = BNO055_INIT_VALUE;

    /* variable used to read the euler r data output
     * as degree or radians*/
    d_euler_data_r = BNO055_INIT_VALUE;

    /* variable used to read the euler p data output
     * as degree or radians*/
    d_euler_data_p = BNO055_INIT_VALUE;

    /* structure used to read the euler hrp data output
     * as as degree or radians */
    

    /*********read linear acceleration converted data**********/
    /* variable used to read the linear accel x data output as m/s2*/
    d_linear_accel_datax = BNO055_INIT_VALUE;

    /* variable used to read the linear accel y data output as m/s2*/
    d_linear_accel_datay = BNO055_INIT_VALUE;

    /* variable used to read the linear accel z data output as m/s2*/
    d_linear_accel_dataz = BNO055_INIT_VALUE;

    /* structure used to read the linear accel xyz data output as m/s2*/
    

    /********************Gravity converted data**********************/
    /* variable used to read the gravity sensor x data output as m/s2*/
    d_gravity_data_x = BNO055_INIT_VALUE;

    /* variable used to read the gravity sensor y data output as m/s2*/
    d_gravity_data_y = BNO055_INIT_VALUE;

    /* variable used to read the gravity sensor z data output as m/s2*/
    d_gravity_data_z = BNO055_INIT_VALUE;

    /* structure used to read the gravity xyz data output as m/s2*/
        
    

    /************************* START READ RAW SENSOR DATA****************/

    /*  Using BNO055 sensor we can read the following sensor data and
     * virtual sensor data
     * Sensor data:
     * Accel
     * Mag
     * Gyro
     * Virtual sensor data
     * Euler
     * Quaternion
     * Linear acceleration
     * Gravity sensor */

    /*  For reading sensor raw data it is required to set the
     * operation modes of the sensor
     * operation mode can set from the register
     * page - page0
     * register - 0x3D
     * bit - 0 to 3
     * for sensor data read following operation mode have to set
     * SENSOR MODE
     * 0x01 - BNO055_OPERATION_MODE_ACCONLY
     * 0x02 - BNO055_OPERATION_MODE_MAGONLY
     * 0x03 - BNO055_OPERATION_MODE_GYRONLY
     * 0x04 - BNO055_OPERATION_MODE_ACCMAG
     * 0x05 - BNO055_OPERATION_MODE_ACCGYRO
     * 0x06 - BNO055_OPERATION_MODE_MAGGYRO
     * 0x07 - BNO055_OPERATION_MODE_AMG
     * based on the user need configure the operation mode*/

    /*  Raw accel X, Y and Z data can read from the register
     * page - page 0
     * register - 0x08 to 0x0D*/
    comres += bno055_read_accel_x(&accel_datax);
    comres += bno055_read_accel_y(&accel_datay);
    comres += bno055_read_accel_z(&accel_dataz);
    comres += bno055_read_accel_xyz(&accel_xyz);

    /*  Raw mag X, Y and Z data can read from the register
     * page - page 0
     * register - 0x0E to 0x13*/
    comres += bno055_read_mag_x(&mag_datax);
    comres += bno055_read_mag_y(&mag_datay);
    comres += bno055_read_mag_z(&mag_dataz);
    comres += bno055_read_mag_xyz(&mag_xyz);

    /*  Raw gyro X, Y and Z data can read from the register
     * page - page 0
     * register - 0x14 to 0x19*/
    comres += bno055_read_gyro_x(&gyro_datax);
    comres += bno055_read_gyro_y(&gyro_datay);
    comres += bno055_read_gyro_z(&gyro_dataz);
    comres += bno055_read_gyro_xyz(&gyro_xyz);

    /************************* END READ RAW SENSOR DATA****************/

    /************************* START READ RAW FUSION DATA ********
     * For reading fusion data it is required to set the
     * operation modes of the sensor
     * operation mode can set from the register
     * page - page0
     * register - 0x3D
     * bit - 0 to 3
     * for sensor data read following operation mode have to set
     * FUSION MODE
     * 0x08 - BNO055_OPERATION_MODE_IMUPLUS
     * 0x09 - BNO055_OPERATION_MODE_COMPASS
     * 0x0A - BNO055_OPERATION_MODE_M4G
     * 0x0B - BNO055_OPERATION_MODE_NDOF_FMC_OFF
     * 0x0C - BNO055_OPERATION_MODE_NDOF
     * based on the user need configure the operation mode*/

    /*  Raw Euler H, R and P data can read from the register
     * page - page 0
     * register - 0x1A to 0x1E */
    comres += bno055_read_euler_h(&euler_data_h);
    comres += bno055_read_euler_r(&euler_data_r);
    comres += bno055_read_euler_p(&euler_data_p);
    comres += bno055_read_euler_hrp(&euler_hrp);

    /*  Raw Quaternion W, X, Y and Z data can read from the register
     * page - page 0
     * register - 0x20 to 0x27 */
    comres += bno055_read_quaternion_w(&quaternion_data_w);
    comres += bno055_read_quaternion_x(&quaternion_data_x);
    comres += bno055_read_quaternion_y(&quaternion_data_y);
    comres += bno055_read_quaternion_z(&quaternion_data_z);
    comres += bno055_read_quaternion_wxyz(&quaternion_wxyz);

    /*  Raw Linear accel X, Y and Z data can read from the register
     * page - page 0
     * register - 0x28 to 0x2D */
    comres += bno055_read_linear_accel_x(&linear_accel_data_x);
    comres += bno055_read_linear_accel_y(&linear_accel_data_y);
    comres += bno055_read_linear_accel_z(&linear_accel_data_z);
    comres += bno055_read_linear_accel_xyz(&linear_acce_xyz);

    /*  Raw Gravity sensor X, Y and Z data can read from the register
     * page - page 0
     * register - 0x2E to 0x33 */
    comres += bno055_read_gravity_x(&gravity_data_x);
    comres += bno055_read_gravity_y(&gravity_data_y);
    comres += bno055_read_gravity_z(&gravity_data_z);
    comres += bno055_read_gravity_xyz(&gravity_xyz);

    /************************* END READ RAW FUSION DATA  ************/
    /******************START READ CONVERTED SENSOR DATA****************/

    /*  API used to read accel data output as double  - m/s2 and mg
     * float functions also available in the BNO055 API */
    comres += bno055_convert_double_accel_x_msq(&d_accel_datax);
    //comres += bno055_convert_double_accel_x_mg(&d_accel_datax);
    comres += bno055_convert_double_accel_y_msq(&d_accel_datay);
    //comres += bno055_convert_double_accel_y_mg(&d_accel_datay);
    comres += bno055_convert_double_accel_z_msq(&d_accel_dataz);
    //comres += bno055_convert_double_accel_z_mg(&d_accel_dataz);
    comres += bno055_convert_double_accel_xyz_msq(&d_accel_xyz);
    //comres += bno055_convert_double_accel_xyz_mg(&d_accel_xyz);

    /*  API used to read mag data output as double  - uT(micro Tesla)
     * float functions also available in the BNO055 API */
    comres += bno055_convert_double_mag_x_uT(&d_mag_datax);
    comres += bno055_convert_double_mag_y_uT(&d_mag_datay);
    comres += bno055_convert_double_mag_z_uT(&d_mag_dataz);
    comres += bno055_convert_double_mag_xyz_uT(&d_mag_xyz);

    /*  API used to read gyro data output as double  - dps and rps
     * float functions also available in the BNO055 API */
    comres += bno055_convert_double_gyro_x_dps(&d_gyro_datax);
    comres += bno055_convert_double_gyro_y_dps(&d_gyro_datay);
    comres += bno055_convert_double_gyro_z_dps(&d_gyro_dataz);
    //comres += bno055_convert_double_gyro_x_rps(&d_gyro_datax);
    //comres += bno055_convert_double_gyro_y_rps(&d_gyro_datay);
    //comres += bno055_convert_double_gyro_z_rps(&d_gyro_dataz);
    comres += bno055_convert_double_gyro_xyz_dps(&d_gyro_xyz);
    //comres += bno055_convert_double_gyro_xyz_rps(&d_gyro_xyz);

    /*  API used to read Euler data output as double  - degree and radians
     * float functions also available in the BNO055 API */
    comres += bno055_convert_double_euler_h_deg(&d_euler_data_h);
    comres += bno055_convert_double_euler_r_deg(&d_euler_data_r);
    comres += bno055_convert_double_euler_p_deg(&d_euler_data_p);
    //comres += bno055_convert_double_euler_h_rad(&d_euler_data_h);
    //comres += bno055_convert_double_euler_r_rad(&d_euler_data_r);
    //comres += bno055_convert_double_euler_p_rad(&d_euler_data_p);
    comres += bno055_convert_double_euler_hpr_deg(&d_euler_hpr);
    //comres += bno055_convert_double_euler_hpr_rad(&d_euler_hpr);

    /*  API used to read Linear acceleration data output as m/s2
     * float functions also available in the BNO055 API */
    comres += bno055_convert_double_linear_accel_x_msq(&d_linear_accel_datax);
    comres += bno055_convert_double_linear_accel_y_msq(&d_linear_accel_datay);
    comres += bno055_convert_double_linear_accel_z_msq(&d_linear_accel_dataz);
    comres += bno055_convert_double_linear_accel_xyz_msq(&d_linear_accel_xyz);

    /*  API used to read Gravity sensor data output as m/s2
     * float functions also available in the BNO055 API */
    comres += bno055_convert_gravity_double_x_msq(&d_gravity_data_x);
    comres += bno055_convert_gravity_double_y_msq(&d_gravity_data_y);
    comres += bno055_convert_gravity_double_z_msq(&d_gravity_data_z);
    comres += bno055_convert_double_gravity_xyz_msq(&d_gravity_xyz);


    return comres;
}

/*--------------------------------------------------------------------------*
 *  The following API is used to map the I2C bus read, write, delay and
 *  device address with global structure bno055_t
 *-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*
 *  By using bno055 the following structure parameter can be accessed
 *  Bus write function pointer: BNO055_WR_FUNC_PTR
 *  Bus read function pointer: BNO055_RD_FUNC_PTR
 *  Delay function pointer: delay_msec
 *  I2C address: dev_addr
 *--------------------------------------------------------------------------*/
s8 I2C_routine(void)
{
    bno055.bus_write = BNO055_I2C_bus_write;
    bno055.bus_read = BNO055_I2C_bus_read;
    bno055.delay_msec = BNO055_delay_msek;
    bno055.dev_addr = BNO055_I2C_ADDR1;

    return BNO055_INIT_VALUE;
}

/************** I2C buffer length******/

#define I2C_BUFFER_LEN 8
#define I2C0           5


/*  \Brief: The API is used as I2C bus write
 *  \Return : Status of the I2C write
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register,
 *   will data is going to be written
 *  \param reg_data : It is a value hold in the array,
 *      will be used for write the value into the register
 *  \param cnt : The no of byte of data to be write
 */


s8 BNO055_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    //Print("writing");
    IMU_I2C_I2CMasterClearStatus(); //clear the garbage
    u8 data_pack [cnt+1]; 
    data_pack[0] = reg_addr;
    for(int i = 1; i < cnt+1; i++){
        data_pack[i] = reg_data[i-1];   
    }
    int status = IMU_I2C_I2CMasterWriteBuf(dev_addr, data_pack, cnt+1, IMU_I2C_I2C_MODE_COMPLETE_XFER);
    while ((IMU_I2C_I2CMasterStatus() & IMU_I2C_I2C_MSTAT_WR_CMPLT) == 0u) //should wait for write buffer to complete
    {
        //Print("\r\nWRITE TO: \n\r");
        //PrintChar(dev_addr);
    }
    
	return status;  
}

/*  \Brief: The API is used as I2C bus read
 *  \Return : Status of the I2C read
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register,
 *  will data is going to be read
 *  \param reg_data : This data read from the sensor,
 *   which is hold in an array
 *  \param cnt : The no of byte of data to be read
 */
s8 BNO055_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    IMU_I2C_I2CMasterClearStatus(); //clear the garbage
    
    /*u8 data_pack [cnt+1]; 
    data_pack[0] = reg_addr;
    for(int i = 1; i < cnt+1; i++){
        data_pack[i] = reg_data[i-1];   
    }
    int status = IMU_I2C_I2CMasterReadBuf(dev_addr, data_pack, cnt+1, IMU_I2C_I2C_MODE_COMPLETE_XFER);
    while ((IMU_I2C_I2CMasterStatus() & IMU_I2C_I2C_MSTAT_RD_CMPLT) == 0u) //should wait for read buffer to complete
    {
        //Print("\r\nREAD FROM: \n\r");
        //PrintChar(dev_addr);
    }
    
    return status;
    */
    //Print("reading");
    int ms_timeout = 20;
    s32 BNO055_iERROR = 0; // this is the "status" we usually use in our R/W functions
	u8 idx;
	BNO055_iERROR = IMU_I2C_I2CMasterSendStart(dev_addr, IMU_I2C_I2C_WRITE_XFER_MODE, ms_timeout);
	// Check for BNO055_iERROR before proceeding
	BNO055_iERROR = IMU_I2C_I2CMasterWriteByte(reg_addr, ms_timeout);
	// Check for BNO055_iERROR before proceeding
	BNO055_iERROR = IMU_I2C_I2CMasterSendStop(10);
	
	BNO055_iERROR = IMU_I2C_I2CMasterSendStart(dev_addr, IMU_I2C_I2C_READ_XFER_MODE, ms_timeout);
    //PrintInt(BNO055_iERROR);
	for (idx = 0; (idx < cnt) && (BNO055_iERROR == 0); idx++)
	{
        if (idx < cnt-1)
        {
		    IMU_I2C_I2CMasterReadByte(IMU_I2C_I2C_ACK_DATA, &reg_data[idx], ms_timeout);
        }
        else
        {
            IMU_I2C_I2CMasterReadByte(IMU_I2C_I2C_NAK_DATA, &reg_data[idx], ms_timeout);
        }
	}
	// Check for BNO055_iERROR before proceeding
	BNO055_iERROR = IMU_I2C_I2CMasterSendStop(ms_timeout);

	return (s8)BNO055_iERROR;
    
	
}

/*  Brief : The delay routine
 *  \param : delay in ms
 */
void BNO055_delay_msek(u32 msek)
{
    CyDelay(msek);
}
