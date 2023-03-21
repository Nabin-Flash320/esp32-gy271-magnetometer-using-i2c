

#ifndef _MAIN_DEFS_H_
#define _MAIN_DEFS_H_


// Datasheet can be found at:
// https://www.farnell.com/datasheets/1683374.pdf

// For reference following github repository can be consulted.
// https://github.com/Embetronicx/incubator-nuttx-apps/tree/master/examples/etx_i2c

#define SLAVE_ADDR 0x1E
#define ACK_CHECK_EN 0x1

/**
 * @brief Configuration register A, also called (CRA) is a read-write register that configures device for output dataa rate and measurement configurations.
 * 
 * Value set is => 0x70
 * i.e.
 * Default sample number 8.
 * Default output rate is 15Hz.
 * Default bias is normal operation without iput biasing.
 * 
 */
#define HMC5883L_DEVICE_CONFIGURATION_REGISTER_A                            0x00    // This is read-write register.

/**
 * @brief Configuration register B, also called as (CRB) is a read-write register that configures gain of the deivce.
 * 
 * Value set is => 0x20
 * i.e. 
 * Default gain configuration is 1090 LSB/Gauss with range of -1.3Ga to +1.3Ga
 * 
 */
#define HMC5883L_DEVICE_CONFIGURATION_REGISTER_B                            0x01    // This is read-write register.

/**
 * @brief Mode register, also called MR is a read write register that configures the mode of operation of the device.
 * 
 * Value set is => 0x01
 * i.e.
 * Default mode of operation is single measurement mode.
 * 
 */
#define HMC5883L_DEVICE_MODE_REGISTER                                       0x02    // This is read-write register.

/**
 * @brief data x MSB, data x LSB, data z MSB, data z LSB, data z MSB, data z LSB, store the measured values in specified axies.
 * 
 */
#define HMC5883L_DEVICE_DATA_X_MSB_REGISTER                                 0x03    // This is read-only register.
#define HMC5883L_DEVICE_DATA_X_LSB_REGISTER                                 0x04    // This is read-only register.
#define HMC5883L_DEVICE_DATA_Z_MSB_REGISTER                                 0x05    // This is read-only register.
#define HMC5883L_DEVICE_DATA_Z_LSB_REGISTER                                 0x06    // This is read-only register.
#define HMC5883L_DEVICE_DATA_Y_MSB_REGISTER                                 0x07    // This is read-only register.
#define HMC5883L_DEVICE_DATA_Y_LSB_REGISTER                                 0x08    // This is read-only register.

/**
 * @brief Status register is the read-only register that gives the status of the register.
 * i.e. Data lock status and data ready status.
 * 
 */
#define HMC5883L_DEVICE_STATUS_REGISTER                                     0x09    // This is read-only register.

/**
 * @brief Identification register A is a read-only register that holds the ASCII value H.
 * 
 */
#define HMC5883L_DEVICE_IDENTIFICATION_REGISTER_A                           0x0A    // This is read-only register.

/**
 * @brief Identification register B is a read-only register that holds the ASCII value 4.
 * 
 */
#define HMC5883L_DEVICE_IDENTIFICATION_REGISTER_B                           0x0B    // This is read-only register.

/**
 * @brief Identification register C is a read-only register that holds the ASCII value 3.
 * 
 */
#define HMC5883L_DEVICE_IDENTIFICATION_REGISTER_C                           0x0C    // This is read-only register.  


/**
 * @brief Here the default values are defined for read-write registers.
 * 
 */

#define CRA_DEFAULT_VALUE                                                   0x70
#define CRB_DEFAULT_VALUE                                                   0x20
#define MR_CONTINUOUS_READ_MODE_VALUE                                       0x00    
#define MR_SINGLE_READ_MODE_VALUE                                           0x01    // This is the default value of the device.
#define MR_IDEAL_VALUE                                                      0x02    // 0x03. can also be set to keep device in ideal



#endif //_MAIN_DEFS_H_



