#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float powerWatt;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

struct PowerReport {
    float totalPowerWatt;
    float totalCurrentAmperes;
    float energyKWh;
    int overloadWarning;
};

int main() {
    struct SmartDevice airConditioner;
    struct SmartDevice lighting;

    struct EnergySensor sensor;
    struct PowerReport report;

    int inputStatus;

    airConditioner.deviceID = 101;
    snprintf(airConditioner.deviceName, sizeof(airConditioner.deviceName), "Dieu hoa");
    airConditioner.status = 1;
    airConditioner.powerWatt = 3000.0f;

    lighting.deviceID = 102;
    snprintf(lighting.deviceName, sizeof(lighting.deviceName), "Den chieu sang");
    lighting.status = 1;
    lighting.powerWatt = 1200.0f;

    sensor.voltageVolts = 220.0f;
    sensor.currentAmperes = 20.0f;
    sensor.unoccupancyMinutes = 20;

    report.totalPowerWatt = 0.0f;
    report.totalCurrentAmperes = 0.0f;
    report.energyKWh = 0.0f;
    report.overloadWarning = 0;

    printf("===============================================\n");
    printf("       SMART HOME CENTRAL GATEWAY\n");
    printf("===============================================\n");

    printf("\n--- DU LIEU CAM BIEN ---\n");
    printf("Dien ap: %.2f V\n", sensor.voltageVolts);
    printf("Dong dien: %.2f A\n", sensor.currentAmperes);
    printf("Thoi gian phong khong co nguoi: %d phut\n",
           sensor.unoccupancyMinutes);

    if (sensor.unoccupancyMinutes > 15) {
        airConditioner.status = 0;
        airConditioner.powerWatt = 0.0f;

        printf("\n[CANH BAO TU DONG]\n");
        printf("Phong da trong hon 15 phut.\n");
        printf("He thong tu dong tat dieu hoa.\n");
    }

    printf("\n--- CAP NHAT TRANG THAI THIET BI ---\n");

    printf("Nhap trang thai dieu hoa (1: BAT, 0: TAT): ");
    scanf("%d", &inputStatus);

    if (inputStatus == 0 || inputStatus == 1) {
        airConditioner.status = inputStatus;

        if (airConditioner.status == 0) {
            airConditioner.powerWatt = 0.0f;
        } else {
            airConditioner.powerWatt = 3000.0f;
        }
    } else {
        printf("Trang thai khong hop le. Giu nguyen trang thai hien tai.\n");
    }

    report.totalPowerWatt =
        airConditioner.powerWatt + lighting.powerWatt;

    if (sensor.voltageVolts > 0) {
        report.totalCurrentAmperes =
            report.totalPowerWatt / sensor.voltageVolts;
    } else {
        report.totalCurrentAmperes = 0.0f;
    }

    if (report.totalCurrentAmperes > 30.0f) {
        report.overloadWarning = 1;
    } else {
        report.overloadWarning = 0;
    }

    report.energyKWh =
        (report.totalPowerWatt / 1000.0f) * (1.0f / 60.0f);

    printf("\n===============================================\n");
    printf("              SMART HOME DASHBOARD\n");
    printf("===============================================\n");

    printf("\n%-15s %-12s %-12s %-12s\n",
           "Thiet bi", "Ma", "Trang thai", "Cong suat");
    printf("-----------------------------------------------\n");

    printf("%-15s %-12d %-12s %.2f W\n",
           airConditioner.deviceName,
           airConditioner.deviceID,
           airConditioner.status ? "BAT" : "TAT",
           airConditioner.powerWatt);

    printf("%-15s %-12d %-12s %.2f W\n",
           lighting.deviceName,
           lighting.deviceID,
           lighting.status ? "BAT" : "TAT",
           lighting.powerWatt);

    printf("\n--- CAM BIEN REAL-TIME ---\n");
    printf("Dien ap              : %.2f V\n",
           sensor.voltageVolts);
    printf("Dong dien do duoc     : %.2f A\n",
           sensor.currentAmperes);
    printf("Phong vang            : %d phut\n",
           sensor.unoccupancyMinutes);

    printf("\n--- POWER REPORT ---\n");
    printf("Tong cong suat        : %.2f W\n",
           report.totalPowerWatt);
    printf("Tong dong dien        : %.2f A\n",
           report.totalCurrentAmperes);
    printf("Dien nang uoc tinh    : %.6f kWh\n",
           report.energyKWh);

    if (report.overloadWarning == 1) {
        printf("Trang thai an toan    : CANH BAO QUA TAI NGUY HIEM!\n");
        printf("Nguyen nhan           : Tong dong dien vuot 30A.\n");
    } else {
        printf("Trang thai an toan    : AN TOAN\n");
    }

    printf("\n===============================================\n");
    printf("          KET THUC SMART HOME MODULE\n");
    printf("===============================================\n");

    return 0;
}
