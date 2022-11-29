/* WiFi station Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
// MQTT
#include <stdint.h>
#include <stddef.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_netif.h"
#include "driver/gpio.h"
//#include "protocol_examples_common.h"

#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "mqtt_client.h"

// MQTT

/// USART

#include <stdio.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "infra_compat.h"

#include "ota_solo.h"

#include "conn_mgr.h"

/* The examples use WiFi configuration that you can set via project configuration menu

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_WIFI_SSID      "Chen"
#define EXAMPLE_ESP_WIFI_PASS      "137gxwtu"
#define EXAMPLE_ESP_MAXIMUM_RETRY  20

#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

// USART begin
#define ECHO_TEST_TXD 		15			//(CONFIG_EXAMPLE_UART_TXD)
#define ECHO_TEST_RXD 		4			//(CONFIG_EXAMPLE_UART_RXD)
#define ECHO_TEST_RTS 		(UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS 		(UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM      2			//(CONFIG_EXAMPLE_UART_PORT_NUM)
#define ECHO_UART_BAUD_RATE     115200		//(CONFIG_EXAMPLE_UART_BAUD_RATE)
#define ECHO_TASK_STACK_SIZE    2046		//(CONFIG_EXAMPLE_TASK_STACK_SIZE)
#define BUF_SIZE (1024)
// USART end

// GPIO begin
#define GPIO_OUTPUT_IO_0    18
#define GPIO_OUTPUT_IO_1    19
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
// GPIO end
static const char *TAG = "wifi station";

// MQTT begin
#define   Aliyun_host       "a1GCrhoFnT8.iot-as-mqtt.cn-shanghai.aliyuncs.com"						//"a1tUbQR2faQ.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define   Aliyun_port       1883
/*Client ID：     ${ClientID}|securemode=${Mode},signmethod=${SignMethod}|*/
#define   Aliyun_client_id  "a1GCrhoFnT8.test|securemode=2,signmethod=hmacsha256,timestamp=1669622367160|"					//"112233|securemode=2,signmethod=hmacsha1|"
/*User Name：     ${DeviceName}&${ProductKey}*/
#define   Aliyun_username   "test&a1GCrhoFnT8"														//"dev-esp32&a1tUbQR2faQ"
/*使用官网 MQTT_Password 工具生成*/
#define   Aliyun_password   "71b3f162ac8c6e9bfad2ebb791d90adbda131a77d35b12cbe94ef85f7ad82518"				//"9ABE732ED28BC38EEE7336FA824C26E744413360"

#define   AliyunSubscribeTopic_user_get     "/a1GCrhoFnT8/test/user/get"   ///a1tIhVm9RS6/${deviceName}/user/update///sys/a1tIhVm9RS6/${deviceName}/thing/event/property/post
#define   AliyunPublishTopic_user_update    "/a1GCrhoFnT8/test/user/update"

char mqtt_publish_data1[] = "mqtt connect ok ";
char mqtt_publish_data2[] = "mqtt subscribe successful";
char mqtt_publish_data3[] = "mqtt i am esp32";
uint8_t serial_coin_add[6] = {0xAA, 4, 1, 2, 7, 0xDD};	//, 0x04 0x01 0x01 0x06 0xDD};

esp_mqtt_client_handle_t client;


 int HAL_SetProductKey(char *product_key);
//int HAL_SetProductSecret(char *product_secret);
 int HAL_SetDeviceName(char *device_name);
 int HAL_SetDeviceSecret(char *device_secret);






// MQTT end

static int s_retry_num = 0;
static int WIFI_Status = 0;		// 0 is not connected. 1 is connected;


typedef struct _SystemConfig
{
	uint8_t		connected;


}str_System_Config;

str_System_Config IPSystemConfig;

/// MQTT program begin
static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int  msg_id;

    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
  /*          char *pub_payload = "{\"id\":\"1\",\"version\":\"1.0\",\"params\":{\"LightSwitch\":0}}";

                   res = aiot_mqtt_pub(mqtt_handle, pub_topic, (uint8_t *)pub_payload, (uint32_t)strlen(pub_payload), 0);
*/
            msg_id = esp_mqtt_client_publish(client, AliyunPublishTopic_user_update, mqtt_publish_data1, strlen(mqtt_publish_data1), 1, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, AliyunSubscribeTopic_user_get, 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, AliyunPublishTopic_user_update, mqtt_publish_data2, strlen(mqtt_publish_data2), 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            // received MESSAGE from MQTT Server;
            //serial_coin_add[3] = atoi(event->data);
            //serial_coin_add[4] = serial_coin_add[1] + serial_coin_add[2] + serial_coin_add[3];
//            printf("[serial]: %x,%x, %x, %x,%x, %x\r\n", serial_coin_add[0],
//            		serial_coin_add[1],serial_coin_add[2],//
//					serial_coin_add[3],
//					serial_coin_add[4],
//					serial_coin_add[5]);
            //if (strcmp (event->data, "AA") >= 0)
            if (strstr(event->data, "AA"))
            	{
            		gpio_set_level(GPIO_OUTPUT_IO_0, 1);
            		sleep(1);
            		printf("GPIO OUTPUT : %d \r\n", GPIO_OUTPUT_IO_0);
            		gpio_set_level(GPIO_OUTPUT_IO_0, 0);
            	}
            if (strstr (event->data, "BB"))
            	{
            		uart_write_bytes(ECHO_UART_PORT_NUM, (const uint8_t *)serial_coin_add, 6 );
            	}
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}



static void mqtt_test_task(void *pvParameters)
{
    uint8_t num = 0;

    while(1)
    {
       esp_mqtt_client_publish(client, AliyunPublishTopic_user_update, mqtt_publish_data3, strlen(mqtt_publish_data3), 1, 0);
       vTaskDelay(2000 / portTICK_PERIOD_MS);
	   if(num++ > 5) break;
	}
    vTaskDelete(NULL);
}

void user_mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
		.host = Aliyun_host,
		.port = Aliyun_port,
		.client_id = Aliyun_client_id,
		.username = Aliyun_username,
		.password = Aliyun_password,

    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);

	xTaskCreate(&mqtt_test_task, "mqtt_test_task", 4096, NULL, 5, NULL);
}
/// MOTT program end


static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
            WIFI_Status = 0;
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);

        //// Do Something Here;
        WIFI_Status = 1;
    }
}

void wifi_init_sta(void)
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS,
            /* Setting a password implies station will connect to all security modes including WEP/WPA.
             * However these modes are deprecated and not advisable to be used. Incase your Access point
             * doesn't support WPA2, these mode can be enabled by commenting below line */
	     .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
}

static void echo_task(void *arg)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
    printf("[Serial]: Serial Prepared!");
    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(ECHO_UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_RATE_MS);
        uint16_t temp_Best, temp_Curr;
        // Write data back to the UART
        //uart_write_bytes(ECHO_UART_PORT_NUM, (const char *) data, len);
        if (len) {
            data[len] = '\0';
            //ESP_LOGI(TAG, "Recv str: %d, %X",len, data[0]);
           // printf("Recv str:%d\r\n", len);			//(char *) data);

            if (data[0] == 0xaa)
            {
            	switch (data[2])
            	{
            	case 0x01:
            		break;
            	case 0x02:
            		IPSystemConfig.connected = 1;
            		printf("Receive Heart Beat\r\n");
            		break;
            	case 0x03:
            		temp_Best = data[3] * 256 + data[4];
            		temp_Curr = data[5] * 256 + data[6];
            		printf("Receive Final MARK: %d, vs %d\r\n", temp_Best, temp_Curr);
            		char *pub_payload = (char *)malloc(1024);
            		memset(pub_payload, '\0', 1024);
            		sprintf(pub_payload, "{\"id\":\"%s\",\"version\":\"1.0\",\"params\":{\"BestMark\":\"%d\", \"CurrentMark\":\"%d\"}}", Aliyun_client_id, temp_Best, temp_Curr);  //
            		printf(pub_payload);
            		esp_mqtt_client_publish(client, AliyunPublishTopic_user_update, pub_payload, strlen(pub_payload), 1, 0);
            		// MQTT
            		break;
            	case 0x04:
            		printf("[serial]: Received, ADD Coin feedback, %d", data[3]);
            		break;
            	case 0x05:
            		break;
            	default:
            		break;
            	}
            }
        }
    }
}

void gpio_init(){
        //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    //disable pull-up mode
    io_conf.pull_up_en = 0 ;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

}

 void gpio_18_task(void *arg)
{
    while(1)
 {
    gpio_init();
    gpio_set_level(GPIO_OUTPUT_IO_0, 0);
    printf("led on\n");
    vTaskDelay(500/portTICK_PERIOD_MS);
    gpio_set_level(GPIO_OUTPUT_IO_0, 1);
    printf("led off\n");
    vTaskDelay(500/portTICK_PERIOD_MS);
 }

}

void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    // GPIO OUTPUT

    // //zero-initialize the config structure.
    // gpio_config_t io_conf = {};
    // //disable interrupt
    // io_conf.intr_type = GPIO_INTR_DISABLE;
    // //set as output mode
    // io_conf.mode = GPIO_MODE_OUTPUT;
    // //bit mask of the pins that you want to set,e.g.GPIO18/19
    // io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    // //disable pull-down mode
    // io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    // //disable pull-up mode
    // io_conf.pull_up_en = 0 ;
    // //configure GPIO with the given settings
    // gpio_config(&io_conf);


    //gpio_set_level(GPIO_OUTPUT_IO_0, 0);
    xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();
   // ESP_ERROR_CHECK(example_connect());
    user_mqtt_app_start();

    //gpio_18_task();
    HAL_SetProductKey("a1GCrhoFnT8");
    //HAL_SetProductSecret("eFha1yQgo1rf1234");
    HAL_SetDeviceName("test");
    HAL_SetDeviceSecret("dd6262578af8c6ab56152393980d86db");
    xTaskCreate(gpio_18_task, "gpio_18_task", ECHO_TASK_STACK_SIZE, NULL, 6, NULL);
    xTaskCreate((void (*)(void *))ota_main, "ota_example", 20480, NULL, 5, NULL);
   while(1){

       printf("firmware_version=%s\n", CONFIG_LINKKIT_FIRMWARE_VERSION);//打印版本号
       vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}
