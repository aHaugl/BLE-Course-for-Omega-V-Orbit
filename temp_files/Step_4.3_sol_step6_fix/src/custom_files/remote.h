#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

//Bluetooth configs
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>

/** @brief UUID of the Remote Service. **/
#define BT_UUID_REMOTE_SERV_VAL \
	BT_UUID_128_ENCODE(0x020f0001, 0xbc61, 0x4d87, 0x9319, 0x9aff590fd64c)
#define BT_UUID_REMOTE_BUTTON_CHRC_VAL \
	BT_UUID_128_ENCODE(0x020f0002, 0xbc61, 0x4d87, 0x9319, 0x9aff590fd64c)
#define BT_UUID_REMOTE_BUTTON_MESSAGE_VAL \
	BT_UUID_128_ENCODE(0x020f0003, 0xbc61, 0x4d87, 0x9319, 0x9aff590fd64c)

#define BT_UUID_REMOTE_SERVICE          BT_UUID_DECLARE_128(BT_UUID_REMOTE_SERV_VAL)
#define BT_UUID_REMOTE_BUTTON_CHRC      BT_UUID_DECLARE_128(BT_UUID_REMOTE_BUTTON_CHRC_VAL)
#define BT_UUID_REMOTE_MESSAGE_CHRC     BT_UUID_DECLARE_128(BT_UUID_REMOTE_BUTTON_MESSAGE_VAL)


enum bt_button_notifications_enabled {
	BT_BUTTON_NOTIFICATIONS_ENABLED,
	BT_BUTTON_NOTIFICATIONS_DISABLED,
};

struct bt_remote_service_cb {
	void (*notif_changed)(enum bt_button_notifications_enabled status);
	void (*data_received)(struct bt_conn *conn, const uint8_t *const data, uint16_t len);
};

void bt_ready_callback(int err);
int bluetooth_init(struct bt_conn_cb *bt_cb, struct bt_remote_service_cb *remote_cb);
void set_button_press(uint8_t btn_value);
int send_button_notification(struct bt_conn *conn, uint8_t value);