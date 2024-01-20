# ifndef SDDS_COVIDCOLLECTION_H
# define SDDS_COVIDCOLLECTION_H

# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <sstream>
# include <iomanip>
# include <algorithm>
# include <list>

namespace sdds{
    struct Covid {
        std::string country;
        std::string city;
        std::string variant;
        int year;
        unsigned int cases;
        unsigned int deaths;
        std::string status = "General";
    };

    std::ostream& operator<<(std::ostream& out, const Covid& covid) {
        // | Country                | City           | Variant            | Year | Cases | Deaths || Status   |
        // uses ternary operator to check if year is greater than 0, if not, it prints a space
        // std::to_string() converts int to string
        out << "| " << std::setw(21) << std::left << covid.country << " | " << std::setw(15) << covid.city << " | " << std::setw(20) << covid.variant << " | " 
            << std::setw(6) << std::right << (covid.year > 0 ? std::to_string(covid.year) : " ") << " | " << std::setw(4) << covid.cases << " | " << std::setw(3) << covid.deaths << " | |"<< std::setw(9) << covid.status << " |";
        return out;
    }

    class CovidCollection {
    private:
        std::vector<Covid> collection;
    public:
        CovidCollection(const std::string& filename) {
            std::ifstream file(filename);
            // checks if file is open, if not, throws an exception
            try{
                if (!file) throw std::string("Unable to open [") + filename + "] file";
            }
            catch (std::string& msg) { 
                std::cout << msg << std::endl;
                exit(1);  
            }

            std::string line;
            // while there is a line to read, it reads it and stores it in a Covid object
            while (std::getline(file, line)) {
                // citation: https://stackoverflow.com/questions/20594520/what-exactly-does-stringstream-do
                // citation: https://www.geeksforgeeks.org/stringstream-c-applications/
                // stringstream splits the string into individual words
                // uses istringstream to read each line and store it in a Covid object
                std::istringstream iss(line);
                Covid covidData;
                // read up to 25 characters and store it in the corresponding variable
                iss >> std::setw(25) >> covidData.country;
                // checks if country is United States or United Kingdom and adds the rest of the string to country
                // iss stops reading at the first space, so I had to put an if statement to check for the country with two words
                if(covidData.country == "United"){
                    iss >> std::setw(25) >> covidData.country;
                    covidData.country = "United " + covidData.country;
                }
                // same for city
                iss >> std::setw(25) >> covidData.city;
                if (covidData.city == "New") {
                    iss >> std::setw(25) >> covidData.city;
                    covidData.city = "New " + covidData.city;
                }
                iss >> std::setw(25) >> covidData.variant;
                iss >> covidData.year;
                iss >> covidData.cases;
                iss >> covidData.deaths;
                // psuhes the Covid object to the vector
                collection.push_back(covidData);
            }
        }


        void display(std::ostream& out, const std::string& country = "ALL") const {
            // unsigned int so that it doesn't print negative numbers
            unsigned int totalCases = 0, totalDeaths = 0, countryCases = 0, countryDeaths = 0;
            if (country != "ALL"){
                out << "Displaying information of country = " << country << "\n";
            }
            // using std::for_each to iterate through the vector and print each Covid object USING LAMBDA
            std::for_each(collection.begin(), collection.end(), [&](const Covid& covidData) {
                totalCases += covidData.cases;
                totalDeaths += covidData.deaths;
                // if country is ALL, it prints all the data, else it prints the data for the country specified in the argument above
                if (country == "ALL" || covidData.country == country) {
                    // if country is not ALL, it adds the cases and deaths to the countryCases and countryDeaths variables
                    if (country != "ALL") {
                        countryCases += covidData.cases;
                        countryDeaths += covidData.deaths;
                    }
                    
                    out << covidData << "\n";
                }
            });
            out << "|--------------------------------------------------------------------------------------|\n";
            // if printing for a specific country,
            if (country != "ALL") {
                // if country is United States, it prints the data with a different setw
                if (country == "United States") {
                    out << "|" << std::setw(66) << "Total cases in " << country << ": " << countryCases << " |\n";
                    out << "|" << std::setw(66) << "Total deaths in " << country << ": " << countryDeaths << " |\n";
                }
                // else it prints the data with a common setw
                else{
                    out << "|" << std::setw(73) << "Total cases in " << country << ": " << countryCases << " |\n";
                    out << "|" << std::setw(73) << "Total deaths in " << country << ": " << countryDeaths << " |\n";
                }
                // prints the percentage of cases and deaths in the country compared to the world
                // if country is France, it prints the data with a different setw
                if (country == "France"){
                    out << "|" << std::setw(28)<< country <<" has "<< ((double)(countryCases) / totalCases) * 100 << "% of global cases and ";
                    out << ((double)(countryDeaths) / totalDeaths) * 100<< "% of global deaths |\n";
                }
                // else it prints the data with a common setw
                else{
                    out << "|" << std::setw(26)<< country <<" has "<< ((double)(countryCases) / totalCases) * 100 << "% of global cases and ";
                    out << ((double)(countryDeaths) / totalDeaths) * 100<< "% of global deaths |\n";
                }
            } 
            // else it prints the total cases and deaths in the world
            else {
                out << "|" << std::setw(80) << "Total cases in the world: " << totalCases <<" |\n";
                out << "|" << std::setw(80) << "Total deaths in the world: " << totalDeaths <<" |\n";
            }
        }

        void sort(const std::string& field = "country") {
            // uses std::sort to sort the vector based on the field specified in the argument
            // default is country
            // uses lambda to compare the Covid objects
            std::sort(collection.begin(), collection.end(), [&](const Covid& a, const Covid& b) {
                if (field == "country") return a.country < b.country;
                if (field == "city") return a.city < b.city;
                if (field == "variant") {
                    // if variant is the same, it sorts by deaths, else it sorts by variant
                    if (a.variant == b.variant) return a.deaths < b.deaths;
                    return a.variant < b.variant;}
                if (field == "year") return a.year < b.year;
                if (field == "cases") return a.cases < b.cases;
                if (field == "deaths") return a.deaths < b.deaths;
                return false;
            });
        }

        // checks if the Covid object is already in the vector
        bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const {
            // uses std::find_if to check if the Covid object is already in the vector USING LAMBDA
            return std::find_if(collection.begin(), collection.end(), [&](const Covid& covidData) {
                return covidData.variant == variant && covidData.country == country && covidData.deaths == deaths;
            }) != collection.end();
        }

        // returns a list of Covid objects that have more deaths than the argument
        std::list<Covid> getListForDeaths(unsigned int deaths) const {
            std::list<Covid> list;
            // uses std::copy_if to copy the Covid objects that have more deaths than the argument USING LAMBDA
            std::copy_if(collection.begin(), collection.end(), std::back_inserter(list), [&](const Covid& covidData) {
                return covidData.deaths >= deaths;
            });
            return list;
        }

        // updates the status of each Covid object based on the number of deaths
        void updateStatus() {
            // uses std::transform to update the status of each Covid object based on the number of deaths USING LAMBDA
            std::transform(collection.begin(), collection.end(), collection.begin(), [](Covid c) {
                if (c.deaths > 300) {
                    c.status = "EPIDEMIC";
                } else if (c.deaths < 50) {
                    c.status = "EARLY";
                } else {
                    c.status = "MILD";
                }
                return c;
            });
        }
    };
}
# endif // !SDDS_COVIDCOLLECTION_H
