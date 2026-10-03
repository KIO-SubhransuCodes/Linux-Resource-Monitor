
#include <iostream>
#include <fstream>
#include <string>
#include <sys/statvfs.h>
#include <thread>
#include <chrono>

using namespace std;

void showCPUInfo()
{
    ifstream file("/proc/cpuinfo");

    string line;
    string cpuName;
    int processors = 0;

    while (getline(file, line))
    {

        if (line.find("model name") == 0 && cpuName.empty())
        {
            cpuName = line.substr(line.find(":") + 2);
        }

        if (line.find("processor") == 0)
        {
            processors++;
        }
    }

    cout << "CPU Name      : " << cpuName << endl;
    cout << "CPU Cores     : " << processors << endl;
}

double getCPUUsage()
{
    ifstream file("/proc/stat");

    string cpu;
    long long user, nice, system, idle;
    long long iowait, irq, softirq, steal;

    file >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    long long idle1 = idle + iowait;

    long long total1 =
        user + nice + system + idle +
        iowait + irq + softirq + steal;

    this_thread::sleep_for(chrono::milliseconds(500));

    file.close();
    file.open("/proc/stat");

    file >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    long long idle2 = idle + iowait;

    long long total2 =
        user + nice + system + idle +
        iowait + irq + softirq + steal;

    long long totalDifference = total2 - total1;
    long long idleDifference = idle2 - idle1;

    if (totalDifference == 0)
    {
        return 0;
    }

    return 100.0 *
           (1.0 - (double)idleDifference / totalDifference);
}

void showMemoryInfo()
{
    ifstream file("/proc/meminfo");

    string name;
    long value;
    string unit;

    long total = 0;
    long available = 0;

    while (file >> name >> value >> unit)
    {

        if (name == "MemTotal:")
        {
            total = value;
        }

        if (name == "MemAvailable:")
        {
            available = value;
        }
    }

    long used = total - available;

    double percentage = (double)used / total * 100;

    cout << "Memory Used   : "
         << used / 1024 << " MB / "
         << total / 1024 << " MB"
         << endl;

    cout << "Memory Usage  : "
         << percentage << "%"
         << endl;
}

void showDiskInfo()
{
    struct statvfs disk;

    if (statvfs("/", &disk) == 0)
    {

        unsigned long long total =
            (unsigned long long)disk.f_blocks *
            disk.f_frsize;

        unsigned long long freeSpace =
            (unsigned long long)disk.f_bfree *
            disk.f_frsize;

        unsigned long long used =
            total - freeSpace;

        double percentage =
            (double)used / total * 100;

        cout << "Disk Used     : "
             << used / (1024 * 1024 * 1024)
             << " GB / "
             << total / (1024 * 1024 * 1024)
             << " GB"
             << endl;

        cout << "Disk Usage    : "
             << percentage << "%"
             << endl;
    }
}

void showSystemInfo()
{
    ifstream file("/proc/uptime");

    double uptime;

    if (file >> uptime)
    {

        int hours = uptime / 3600;
        int minutes = ((int)uptime % 3600) / 60;

        cout << "System Uptime : "
             << hours << " hours "
             << minutes << " minutes"
             << endl;
    }
}

int main()
{

    cout << "====================================" << endl;
    cout << "          RESOURCE MONITOR          " << endl;
    cout << "====================================" << endl;

    showCPUInfo();

    cout << "CPU Usage     : "
         << getCPUUsage()
         << "%" << endl;

    showMemoryInfo();

    showDiskInfo();

    showSystemInfo();

    cout << "====================================" << endl;

    return 0;
}
