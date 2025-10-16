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
    std::string city_name;
    while (!file_object.eof())
    {
        std::getline(file_object, city_name);
        city_names.push_back(city_name);

    }
    return city_names;
}

using ConnectionVector = std::vector<std::pair<std::string, std::string>>;

ConnectionVector loadConnections(const char* flight_routes_file)
{
    ConnectionVector connections;
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
            connections.push_back(std::make_pair(origin_city,destination_city));
        }
        else
        {
            throw std::runtime_error("Could not parse file");
        }
    }
    return connections;
}
class flightMap
{
    private:
        std::vector<std::string> cityNames;

        int indexFromCityName(const std::string &city_name) const
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
    public:
        flightMap(const char* city_list_name, const char* flight_routes_name)
        {

        }
};

int main()
{
    auto flight_display = loadConnections("flight_routes.txt");

    for (auto &flights : flight_display)
    {
        std::cout << flights.first << "     " << flights.second << std::endl;
    }
    /*
    auto city_display = loadCityNames("city_list.txt");
    for (auto & city:city_display)
    {
        std::cout << city << std::endl;
    }

    */
}