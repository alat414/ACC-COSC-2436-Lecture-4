#include <iostream>
#include <vector>
#include <list>
#include <fstream>

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
}

class flightMap
{
    private:
        std::vector<std::string> cityNames;
    public:
        flightMap(const char* city_list_name, const char* flight_routes_name)
        {

        }
};

int main()
{
    auto city_display = loadCityNames("city_list.txt");
    for (auto & city:city_display)
    {
        std::cout << city << std::endl;
    }

}