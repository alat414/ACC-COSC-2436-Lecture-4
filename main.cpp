#include <iostream>
#include <vector>
#include <list>
#include <fstream>

void removeWhiteSpace(std::string& name)
{
    name.erase(0, name.find_first_not_of(" \t"));
    name.erase(name.find_last_not_of(" \t") + 1);
}

std::vector<std::string> loadCityNames(const char* city_list_name)
{
    std::vector<std::string> city_names;
    std::ifstream file_object(city_list_name);

    if (!file_object.is_open())
    {
        throw std::runtime_error("Unable to open file");
    }

    std::string city_name;
    
    while (std::getline(file_object, city_name))
    {
        city_names.push_back(city_name);
    }
    return city_names;
}

using ConnectionPairs = std::vector<std::pair<std::string, std::string>>;

ConnectionPairs loadConnectionPairs(const char* flight_routes_file)
{
    ConnectionPairs connection_pairs;
    
    std::ifstream file_object(flight_routes_file);

    if(!file_object.is_open())
    {
        throw std::runtime_error("unable to open file");
    }

    std::string origin_city;
    std::string destination_city;

    while (std::getline(file_object, origin_city, ','))
    {
        removeWhiteSpace(origin_city);
        if (std::getline(file_object, destination_city))
        {
            removeWhiteSpace(destination_city);
            connection_pairs.push_back(std::make_pair(origin_city,destination_city));
        }
        else
        {
            throw std::runtime_error("Could not parse file");
        }
    }
    return connection_pairs;
}

using CityIndex = size_t;
using CityName = std::string;
using CityConnections = std::list<CityIndex>;
using AdjacencyList = std::vector<CityConnections>;

int indexFromCityName(const std::vector<CityName>& cityNames,
                      const std::string & city_name)
{
    for (int i = 0; i < cityNames.size(); i++)
    {
        if (cityNames[i] == city_name)
        {
            return i;
        }
    }
    return -1;
}
AdjacencyList loadAdjacencyList(const std::vector<CityName>& cityNames, 
                                const char* flight_routes_name)
{
    AdjacencyList adjacency_list;

    for (int i = 0; i < cityNames.size(); i++)
    {
        adjacency_list.emplace_back();
    }
    
    ConnectionPairs connection_pairs = loadConnectionPairs(flight_routes_name);
    
    for (const auto& connection_pair : connection_pairs)
    {
        CityIndex city_1_index = indexFromCityName(cityNames, connection_pair.first);
        CityIndex city_2_index = indexFromCityName(cityNames, connection_pair.second);
        adjacency_list[city_1_index].push_back(city_2_index);
    }
    return adjacency_list;
}


class flightMap
{
    private:
        std::vector<CityName> cityNames;
        AdjacencyList connections;

    public:
        flightMap(const char* city_list_name, const char* flight_routes_name) :
        cityNames(loadCityNames(city_list_name)), 
        connections(loadAdjacencyList(cityNames, flight_routes_name))
        {
        }

        void display_connections() const 
        {
            for (int i = 0; i < cityNames.size(); i++)
            {
                std::cout << cityNames[i] << " ";
                std::cout << "connections: " << std::endl;
                const auto &connection = connections[i];

                for (auto index: connection)
                {
                    std::cout<< "\t" << index << std::endl;
                }
            }
        }
};

int main()
{
    flightMap flight_Map("city_list.txt", "flight_routes.txt");

    flight_Map.display_connections();
    /*
    auto city_display = loadCityNames("city_list.txt");
    for (auto & city:city_display)
    {
        std::cout << city << std::endl;
    }

    */
   return 0;
}