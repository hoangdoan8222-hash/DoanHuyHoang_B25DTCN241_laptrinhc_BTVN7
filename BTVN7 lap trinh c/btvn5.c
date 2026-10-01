#include <stdio.h>

struct EnvironmentSensor {
    int sensor_id;
    char room_name[50];
    float temperature;
    float humidity;
    int battery_level;
};

int main() {
    struct EnvironmentSensor sensor;
    char status[10];

    printf("Nhap ma cam bien: ");
    scanf("%d", &sensor.sensor_id);

    printf("Nhap ten phong: ");
    scanf("%49s", sensor.room_name);

    printf("Nhap nhiet do: ");
    scanf("%f", &sensor.temperature);

    printf("Nhap do am: ");
    scanf("%f", &sensor.humidity);

    printf("Nhap dung luong pin: ");
    scanf("%d", &sensor.battery_level);

    if (sensor.battery_level < 0 || sensor.battery_level > 100) {
        printf("Loi: Dung luong pin khong hop le!\n");
        return 0;
    }

    if (sensor.battery_level < 10 || sensor.temperature > 60.0f) {
        snprintf(status, sizeof(status), "CRITICAL");
    } else if (
        (sensor.battery_level >= 10 && sensor.battery_level <= 20) ||
        (sensor.temperature >= 40.0f && sensor.temperature <= 60.0f) ||
        sensor.humidity > 85.0f
    ) {
        snprintf(status, sizeof(status), "WARNING");
    } else {
        snprintf(status, sizeof(status), "SAFE");
    }

    printf("\n--- HE THONG MONITORING SMART_HOME_IOT ---\n");
    printf("Ma cam bien: %d\n", sensor.sensor_id);
    printf("Phong: %s\n", sensor.room_name);
    printf("Nhiet do: %.2f C\n", sensor.temperature);
    printf("Do am: %.2f %%\n", sensor.humidity);
    printf("Dung luong pin: %d %%\n", sensor.battery_level);
    printf("Trang thai: %s\n", status);

    return 0;
}
