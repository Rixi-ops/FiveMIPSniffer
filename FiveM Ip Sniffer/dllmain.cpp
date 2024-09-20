#include <Windows.h>
#include <vector>
#include <string>

class IPLogger {
public:
    void Initialize() {
    }

    void LogIP(const std::string& ip) {
        loggedIPs.push_back(ip);
    }

    const std::vector<std::string>& GetLoggedIPs() const {
        return loggedIPs;
    }

private:
    std::vector<std::string> loggedIPs;
};

IPLogger* ipLogger;

DWORD WINAPI MainThread(LPVOID param) {
    ipLogger = new IPLogger();
    ipLogger->Initialize();

    while (true) {
        Sleep(1000);
        std::string IpAddress = "192.168.1." + std::to_string(rand() % 255);
        ipLogger->LogIP(IpAddress);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        delete ipLogger;
        break;
    }
    return TRUE;
}