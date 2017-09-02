class OtaServerService {
public:
    void begin(char* host, ESP8266WebServer* httpServer, ESP8266HTTPUpdateServer* httpUpdater);
};