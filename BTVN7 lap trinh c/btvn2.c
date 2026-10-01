#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[100];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice device;
    struct EnergySensor sensor;

    float operatingHours;
    float totalKWh;
    float totalCost;

    device.deviceID = 0;
    device.deviceName[0] = '\0';
    device.status = 0;
    device.ratedPowerKW = 0.0f;

    sensor.voltageVolts = 0.0f;
    sensor.currentAmperes = 0.0f;
    sensor.unoccupancyMinutes = 0;

    printf("=== SMART HOME IOT ===\n");

    printf("Nhap ma thiet bi: ");
    scanf("%d", &device.deviceID);

    printf("Nhap ten thiet bi: ");
    scanf(" %99[^\n]", device.deviceName);

    printf("Nhap trang thai thiet bi (1-Bat, 0-Tat): ");
    scanf("%d", &device.status);

    printf("Nhap cong suat dinh muc (kW): ");
    scanf("%f", &device.ratedPowerKW);

    printf("Nhap dien ap do duoc (V): ");
    scanf("%f", &sensor.voltageVolts);

    printf("Nhap dong dien do duoc (A): ");
    scanf("%f", &sensor.currentAmperes);

    printf("Nhap thoi gian vang nguoi (phut): ");
    scanf("%d", &sensor.unoccupancyMinutes);

    printf("Nhap so gio hoat dong trong thang: ");
    scanf("%f", &operatingHours);

    if (sensor.voltageVolts < 0 ||
        sensor.currentAmperes < 0 ||
        sensor.unoccupancyMinutes < 0) {

        printf("\nLOI: Du lieu cam bien khong hop le!\n");
        printf("Dien ap, dong dien va thoi gian vang nguoi khong duoc am.\n");

        return 0;
    }

    if (operatingHours <= 0 || operatingHours > 744) {
        printf("\nLOI: Thoi gian van hanh khong hop le!\n");
        printf("So gio phai lon hon 0 va khong vuot qua 744 gio.\n");

        return 0;
    }

    printf("\n=== XU LY HE THONG ===\n");

    if (sensor.currentAmperes > 30.0f) {
        device.status = 0;

        printf("CANH BAO: Dong dien vuot qua 30A!\n");
        printf("He thong da ngat thiet bi de bao ve an toan.\n");
    }

    if (device.status == 1 &&
        sensor.unoccupancyMinutes >= 15) {

        device.status = 0;

        printf("CANH BAO: Phong vang nguoi tu 15 phut tro len!\n");
        printf("He thong da tu dong tat thiet bi de tiet kiem nang luong.\n");
    }

    totalKWh = device.ratedPowerKW * operatingHours;
    totalCost = 0.0f;

    if (totalKWh <= 50.0f) {
        totalCost = totalKWh * 1806.0f;
    } else if (totalKWh <= 100.0f) {
        totalCost = 50.0f * 1806.0f
                  + (totalKWh - 50.0f) * 1866.0f;
    } else if (totalKWh <= 200.0f) {
        totalCost = 50.0f * 1806.0f
                  + 50.0f * 1866.0f
                  + (totalKWh - 100.0f) * 2167.0f;
    } else {
        totalCost = 50.0f * 1806.0f
                  + 50.0f * 1866.0f
                  + 100.0f * 2167.0f
                  + (totalKWh - 200.0f) * 2729.0f;
    }

    printf("\n=== BAO CAO THIET BI ===\n");
    printf("Ma thiet bi: %d\n", device.deviceID);
    printf("Ten thiet bi: %s\n", device.deviceName);
    printf("Trang thai: %s\n", device.status ? "DANG BAT" : "DA TAT");
    printf("Cong suat dinh muc: %.2f kW\n", device.ratedPowerKW);

    printf("\n=== THONG TIN CAM BIEN ===\n");
    printf("Dien ap: %.2f V\n", sensor.voltageVolts);
    printf("Dong dien: %.2f A\n", sensor.currentAmperes);
    printf("Thoi gian vang nguoi: %d phut\n",
           sensor.unoccupancyMinutes);

    printf("\n=== DIEN NANG VA CHI PHI ===\n");
    printf("So gio hoat dong: %.2f gio\n", operatingHours);
    printf("Tong dien nang: %.2f kWh\n", totalKWh);
    printf("Tong tien dien: %.0f VND\n", totalCost);

    return 0;
}
