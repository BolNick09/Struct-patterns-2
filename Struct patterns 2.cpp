#include <iostream>
#include <unordered_map>
#include <string>

//Паттерн Flyweight 

// Интерфейс элемента карты
class MapElement 
{
public:
    virtual void draw(int x, int y) = 0;
};
// Класс для деревьев
class Tree : public MapElement 
{
private:
    std::string type;
    std::string color;
    std::string texture; public:
        Tree(std::string t, std::string c, std::string tx) : type(t), color(c), texture(tx) {}
        void draw(int x, int y) override 
        {
            std::cout << "Drawing Tree of type " << type << " at (" << x << ", " << y << ") with texture " << texture << std::endl;
        }
};
// Класс для зданий
class Building : public MapElement 
{
private:
    std::string type;
    std::string color;
    int floors; public:
        Building(std::string t, std::string c, int f) : type(t), color(c), floors(f) {}
        void draw(int x, int y) override 
        {
            std::cout << "Drawing Building of type " << type << " at (" << x << ", " << y << ") with " << floors << " floors." << std::endl;
        }
};
// Класс для дорог
class Road : public MapElement 
{
private:
    std::string type;
    std::string material; public:
        Road(std::string t, std::string m) : type(t), material(m) {}
        void draw(int x, int y) override 
        {
            std::cout << "Drawing Road of type " << type << " at (" << x << ", " << y << ") with material " << material << std::endl;
        }
};
// Класс для озер
class Lake : public MapElement 
{
private:
    std::string type;
    std::string color;
    double size; public:
        Lake(std::string t, std::string c, double s) : type(t), color(c), size(s) {}
        void draw(int x, int y) override 
        {
            std::cout << "Drawing Lake of type " << type << " at (" << x << ", " << y << ") with size " << size << " and color " << color << std::endl;
        }
};
// Класс для машин
class Car : public MapElement 
{
private:
    std::string brand;
    std::string color; public:
        Car(std::string b, std::string c) : brand(b), color(c) {}
        void draw(int x, int y) override 
        {
            std::cout << "Drawing Car of brand " << brand << " at (" << x << ", " << y << ") with color " << color << std::endl;
        }
};
// Класс для рек
class River : public MapElement 
{
private:
    std::string name;
    std::string color;
    double width; public:
        River(std::string n, std::string c, double w) : name(n), color(c), width(w) {}
        void draw(int x, int y) override 
        {
            std::cout << "Drawing River named " << name << " at (" << x << ", " << y << ") with width " << width << " and color " << color << std::endl;
        }
};

class MapElementFactory 
{
public:
    static std::unordered_map<std::string, MapElement*> flyweightMap;

    static MapElement* getFlyweight(std::string type)
    {
        auto it = flyweightMap.find(type);
        if (it != flyweightMap.end())
            return it->second;



        MapElement* newFlyweight = nullptr;
        if (type == "Tree")
        {
            newFlyweight = new Tree("Pine", "Green", "PineTexture");
        }
        else if (type == "Building")
        {
            newFlyweight = new Building("Skyscraper", "Gray", 50);
        }
        else if (type == "Road")
        {
            newFlyweight = new Road("Asphalt", "Asphalt");
        }
        else if (type == "Lake")
        {
            newFlyweight = new Lake("Mountain", "Blue", 1.5);
        }
        else if (type == "Car")
        {
            newFlyweight = new Car("Tesla", "Red");
        }
        else if (type == "River")
        {
            newFlyweight = new River("Amazon", "Brown", 10);
        }

        flyweightMap[type] = newFlyweight;
        return newFlyweight;

    }
};
std::unordered_map<std::string, MapElement*> MapElementFactory::flyweightMap;

//-----------------------------------------------------------------------------------
//Паттерн Facade

class RenderSystem 
{
public:
    void initialize() 
    { 
        std::cout << "Initializing Render System" << std::endl; 
    }
    void update() 
    { 
        std::cout << "Updating Render System" << std::endl; 
    }
    void shutdown() 
    { 
        std::cout << "Shutting down Render System" << std::endl; 
    }
};

class PhysicsSystem 
{
public:
    void initialize() 
    { 
        std::cout << "Initializing Physics System" << std::endl; 
    }
    void update() 
    { 
        std::cout << "Updating Physics System" << std::endl; 
    }
    void shutdown() 
    { 
        std::cout << "Shutting down Physics System" << std::endl; 
    }
};

class AudioSystem 
{
public:
    void initialize() 
    { 
        std::cout << "Initializing Audio System" << std::endl; 
    }
    void update() 
    { 
        std::cout << "Updating Audio System" << std::endl; 
    }
    void shutdown() 
    { 
        std::cout << "Shutting down Audio System" << std::endl; 
    }
};

// Класс-фасад

class GameEngineFacade 
{
private:
    RenderSystem renderSystem;
    PhysicsSystem physicsSystem;
    AudioSystem audioSystem;

public:
    void initialize() 
    {
        renderSystem.initialize();
        physicsSystem.initialize();
        audioSystem.initialize();
        std::cout << "Init complete" << std::endl;
    }

    void update() 
    {
        renderSystem.update();
        physicsSystem.update();
        audioSystem.update();
        std::cout << "Update complete" << std::endl;
    }

    void shutdown() 
    {
        renderSystem.shutdown();
        physicsSystem.shutdown();
        audioSystem.shutdown();
        std::cout << "Shutdown complete" << std::endl;
    }
};
//-----------------------------------------------------------------------------------
//Паттерн Proxy
class Server 
{
public:
    virtual bool connect() = 0;
    virtual std::string getData(std::string data) = 0;
};

// Реальный сервер

class RealServer : public Server 
{
public:
    bool connect() override 
    {
        std::cout << "Connecting to the real server..." << std::endl;
        return true;
    }

    std::string getData(std::string data) override 
    {
        std::cout << "Retrieving data from the real server..." << std::endl;
        return "Real Server Data: " + data;
    }
};

// Прокси-сервер

class ProxyServer : public Server 
{
private:
    RealServer* realServer;
    std::unordered_map<std::string, std::string> cache;

public:
    ProxyServer() : realServer(nullptr) {}

    bool connect() override 
    {
        if (!realServer) 
            realServer = new RealServer();        
        return realServer->connect();
    }

    std::string getData(std::string data) override 
    {
        auto it = cache.find(data);
        if (it != cache.end()) 
        {
            std::cout << "Loading data from cache..." << std::endl;
            return it->second;
        }
        else 
        {
            std::string result = realServer->getData(data);
            cache[data] = result;
            return result;
        }
    }
};



int main() 
{    
    std::cout << "Flyweight  pattern" << std::endl;

    MapElement* pineTree = MapElementFactory::getFlyweight("Tree");
    MapElement* skyscraper = MapElementFactory::getFlyweight("Building");
    MapElement* asphaltRoad = MapElementFactory::getFlyweight("Road");
    MapElement* mountainLake = MapElementFactory::getFlyweight("Lake");
    MapElement* redCar = MapElementFactory::getFlyweight("Car");
    MapElement* amazonRiver = MapElementFactory::getFlyweight("River");

    pineTree->draw(10, 20);
    skyscraper->draw(50, 30);
    asphaltRoad->draw(100, 40);
    mountainLake->draw(150, 50);
    redCar->draw(200, 60);
    amazonRiver->draw(250, 70);

    MapElementFactory::flyweightMap.clear();


    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Facade pattern" << std::endl;

    GameEngineFacade gameEngine;

    gameEngine.initialize();
    gameEngine.update();
    gameEngine.shutdown();

    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Proxy pattern" << std::endl;
    ProxyServer proxyServer;
    proxyServer.connect();

    std::string data1 = proxyServer.getData("image_1");
    std::string data2 = proxyServer.getData("image_1");  // Должен загрузиться из кэша

    std::string data3 = proxyServer.getData("image_2");
    std::string data4 = proxyServer.getData("image_2");  // Должен загрузиться из кэша

    return 0;
}
