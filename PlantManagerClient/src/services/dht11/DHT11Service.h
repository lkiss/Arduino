class DHT11Service {
private:
    int DHT11Pin;
public:
    DHT11Service(int DHT11Pin);
    int* read(int *results);
};