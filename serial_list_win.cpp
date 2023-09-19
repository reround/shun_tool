#ifndef SERIALTOOL_H
#define SERIALTOOL_H

#include <Windows.h>
#include <iostream>
#include <vector>


// Windows 返回串口列表
std::vector<std::wstring> GetSerialPortList()
{
    std::vector<std::wstring> portList;

    // 获取串口信息
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        DWORD maxValueNameSize;
        DWORD maxValueDataSize;
        if (RegQueryInfoKey(hKey, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &maxValueNameSize, &maxValueDataSize, nullptr, nullptr) == ERROR_SUCCESS)
        {
            // 分配内存保存注册表值的名称和数据
            wchar_t* valueName = new wchar_t[maxValueNameSize + 1];
            BYTE* valueData = new BYTE[maxValueDataSize];

            DWORD valueIndex = 0;
            DWORD valueNameSize = maxValueNameSize + 1;
            DWORD valueDataSize = maxValueDataSize;
            while (RegEnumValueW(hKey, valueIndex, valueName, &valueNameSize, nullptr, nullptr, valueData, &valueDataSize) == ERROR_SUCCESS)
            {
                // 获取串口名称
                wchar_t* portName = reinterpret_cast<wchar_t*>(valueData);
                portList.push_back(portName);

                valueIndex++;
                valueNameSize = maxValueNameSize + 1;
                valueDataSize = maxValueDataSize;
            }

            delete[] valueName;
            delete[] valueData;
        }

        RegCloseKey(hKey);
    }

    return portList;
}

#endif // SERIALTOOL_H
