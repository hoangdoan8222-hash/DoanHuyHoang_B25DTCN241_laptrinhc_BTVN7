#include <stdio.h>

struct SmartDeviceOld {
    char status;
    double voltage;
    char deviceType;
    double current;
    float power;
    int operatingMinutes;
    int deviceID;
};

struct SmartDeviceOptimized {
    double voltage;
    double current;
    float power;
    int operatingMinutes;
    int deviceID;
    char status;
    char deviceType;
};

struct EnergyData {
    double voltage;
    double current;
    float power;
};

struct DeviceInfo {
    int deviceID;
    char status;
    char deviceType;
    int operatingMinutes;
};

struct SmartDeviceNested {
    struct EnergyData energy;
    struct DeviceInfo info;
};

int main() {
    struct SmartDeviceOld oldDevice;
    struct SmartDeviceOptimized device;
    struct SmartDeviceNested nestedDevice;

    double calculatedPower;
    double differencePercent;
    double energyKWh;

    printf("=== PHAN TICH SMART HOME IOT ===\n");

    printf("\n=== SO SANH KICH THUOC STRUCT ===\n");
    printf("SmartDeviceOld:       %zu bytes\n", sizeof(oldDevice));
    printf("SmartDeviceOptimized: %zu bytes\n", sizeof(device));
    printf("SmartDeviceNested:    %zu bytes\n", sizeof(nestedDevice));

    printf("\n=== NHAP THONG TIN THIET BI ===\n");

    printf("Nhap ma thiet bi: ");
    scanf("%d", &device.deviceID);

    printf("Nhap trang thai (0-Tat, 1-Bat): ");
    scanf("%d", (int *)&device.status);

    printf("Nhap dien ap U (V): ");
    scanf("%lf", &device.voltage);

    printf("Nhap dong dien I (A): ");
    scanf("%lf", &device.current);

    printf("Nhap cong suat do duoc P (W): ");
    scanf("%f", &device.power);

    printf("Nhap thoi gian hoat dong (phut): ");
    scanf("%d", &device.operatingMinutes);

    if (device.voltage <= 0 ||
        device.current < 0 ||
        device.operatingMinutes < 0) {

        printf("\nLOI: Du lieu cam bien khong hop le!\n");
        printf("Dien ap phai > 0, dong dien phai >= 0 va thoi gian phai >= 0.\n");

        return 0;
    }

    if (device.status != 0 && device.status != 1) {
        printf("\nLOI: Trang thai thiet bi khong hop le!\n");
        printf("Trang thai chi duoc nhan 0 hoac 1.\n");

        return 0;
    }

    calculatedPower = device.voltage * device.current;

    if (calculatedPower > 0) {
        differencePercent =
            ((device.power - calculatedPower) / calculatedPower) * 100.0;

        if (differencePercent < 0) {
            differencePercent = -differencePercent;
        }
    } else {
        differencePercent = 0;
    }

    printf("\n=== KET QUA PHAN TICH ===\n");

    printf("Ma thiet bi: %d\n", device.deviceID);
    printf("Trang thai: %s\n",
           device.status == 1 ? "BAT" : "TAT");

    printf("Dien ap: %.2f V\n", device.voltage);
    printf("Dong dien: %.2f A\n", device.current);
    printf("Cong suat do duoc: %.2f W\n", device.power);
    printf("Cong suat tinh toan U x I: %.2f W\n", calculatedPower);

    printf("\n--- KIEM TRA CAM BIEN CONG SUAT ---\n");

    if (differencePercent > 5.0) {
        printf("CANH BAO: Cam bien cong suat bao sai lech\n");
        printf("Do sai lech: %.2f%%\n", differencePercent);
    } else {
        printf("Cam bien cong suat hoat dong binh thuong.\n");
        printf("Do sai lech: %.2f%%\n", differencePercent);
    }

    printf("\n--- KIEM TRA AN TOAN DIEN ---\n");

    if (device.current > 30.0 || device.power > 6600.0f) {
        printf("CANH BAO: QUA TAI NGUY HIEM\n");
    } else {
        printf("Trang thai tai dien: AN TOAN\n");
    }

    printf("\n--- KIEM TRA RO RI DIEN NANG ---\n");

    if (device.status == 0 && device.current > 0.05) {
        printf("CANH BAO: RO RI DIEN HOAC TAI AN\n");
    } else {
        printf("Khong phat hien ro ri dien nang.\n");
    }

    energyKWh =
        device.power * (device.operatingMinutes / 60.0) / 1000.0;

    printf("\n--- DIEN NANG TIEU THU ---\n");
    printf("Thoi gian hoat dong: %d phut\n",
           device.operatingMinutes);
    printf("Dien nang tieu thu: %.4f kWh\n", energyKWh);

    return 0;
}
