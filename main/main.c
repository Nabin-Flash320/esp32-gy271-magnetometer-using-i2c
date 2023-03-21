

#include "trace.h"
#include "driver/i2c.h"
#include "main_defs.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "math.h"


#define HMC5883L_SDA            2
#define HMC5883L_SCL            3
#define HMC5883L_I2C_NUM        I2C_NUM_0

static const i2c_config_t HMC5883L_config = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = HMC5883L_SDA,
    .scl_io_num = HMC5883L_SCL,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = 100000
};

static float find_square_root(float x, float y, float z)
{
    return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
}


esp_err_t write_reg(uint8_t data, uint8_t register_addr)
{
    esp_err_t error = ESP_OK;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_start(cmd));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_write_byte(cmd, (SLAVE_ADDR << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_write_byte(cmd, register_addr, ACK_CHECK_EN));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_write_byte(cmd, data, ACK_CHECK_EN));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_stop(cmd));
    i2c_master_cmd_begin(HMC5883L_I2C_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return error;
}

esp_err_t read_reg(uint8_t *data, uint8_t register_addr)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_start(cmd));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_write_byte(cmd, (SLAVE_ADDR << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_write_byte(cmd, register_addr, ACK_CHECK_EN));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_start(cmd));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_read_byte(cmd, data, I2C_MASTER_NACK));
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_stop(cmd));
    i2c_master_cmd_begin(HMC5883L_I2C_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ESP_OK;
}

static void get_device_ID()
{
    uint8_t device_ID_A, device_ID_B, device_ID_C;
    uint32_t device_id = 0;

    read_reg(&device_ID_A, HMC5883L_DEVICE_IDENTIFICATION_REGISTER_A);
    TRACE_E("The device ID is: %x", device_ID_A);

    read_reg(&device_ID_B, HMC5883L_DEVICE_IDENTIFICATION_REGISTER_B);
    TRACE_E("The device ID is: %x", device_ID_B);

    read_reg(&device_ID_C, HMC5883L_DEVICE_IDENTIFICATION_REGISTER_C);
    TRACE_E("The device ID is: %x", device_ID_C);

    device_id = (device_ID_A << 16) | (device_ID_B << 8) | device_ID_C;

    TRACE_E("The device ID is: %x", device_id);
}

void app_main()
{
    esp_err_t error;

    TRACE_B("HMC5883L-i2c");
    error = i2c_param_config(HMC5883L_I2C_NUM, &HMC5883L_config);
    if(ESP_OK != error)
    {
        TRACE_E("Error confugring I2C params.(code:%s)", esp_err_to_name(error));
    }
    else
    {
        TRACE_I("I2C params confiugred successfully!");
    }

    error = i2c_driver_install(HMC5883L_I2C_NUM, I2C_MODE_MASTER, 0, 0, 0);
    if(ESP_OK != error)
    {
        TRACE_E("Error installing I2C driver.(code:%s)", esp_err_to_name(error));
    }
    else
    {
        TRACE_I("I2C driver installed successfully!");
    }

    // Configure device for continuous reading mode.
    write_reg(MR_CONTINUOUS_READ_MODE_VALUE, HMC5883L_DEVICE_MODE_REGISTER);

    // Set CRB to default value
    write_reg(CRB_DEFAULT_VALUE, HMC5883L_DEVICE_CONFIGURATION_REGISTER_B);

    uint8_t *data = (uint8_t*)malloc(3);
    memset(data, 0, 3);
    // Read device identification register.
    read_reg(data, 0x07);

    TRACE_B("Data is: %d", *data);
    
    free(data);

}
