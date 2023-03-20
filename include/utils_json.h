#ifndef UTILS_JSON_H
#define UTILS_JSON_H

#include <nlohmann/json.hpp>
#include <map>
#include <fstream>
#include <iostream>


namespace cinema
{
    struct film_date
    {
        std::string name;
        std::string country;
        std::string date;
        std::string studia;
        std::string scenarist;
        std::string director;
        std::string producer;
    
        struct actor
        {
            std::string name;
            std::string surname;

            struct personage
            {
                std::string name;
                std::string description;
            }role;
        };

        actor actors[3];

    };
    
    void to_json(nlohmann::json& j, const film_date& fd)
    {
        j = {
            {"name", fd.name},
            {"country", fd.country},
            {"date", fd.date},
            {"studia", fd.studia},
            {"scenarist", fd.scenarist},
            {"director", fd.director},
            {"producer", fd.producer},
            {"actors", nlohmann::json::array({ {
                                                   {"name", fd.actors[0].name},
                                                   {"surname", fd.actors[0].surname},
                                                   {"personage_name",fd.actors[0].role.name},
                                                   {"personage_description", fd.actors[0].role.description}
                                               },
                     
                                               {
                                                   {"name", fd.actors[1].name},
                                                   {"surname", fd.actors[1].surname},
                                                   {"personage_name",fd.actors[1].role.name},
                                                   {"personage_description", fd.actors[1].role.description}
                                               },
                                               
                                               {
                                                   {"name", fd.actors[2].name},
                                                   {"surname", fd.actors[2].surname},
                                                   {"personage_name",fd.actors[2].role.name},
                                                   {"personage_description", fd.actors[2].role.description}
                                               },

                                             })
            }

        };
    }

    // nlohmann::json create_film_base(const std::map<std::string, film_date>& source_film_data, const std::string& file_path)
    // {
    //     std::ofstream out(file_path, std::ios_base::app);
    //     nlohmann::json j;
        
    //     for(std::map<std::string, film_date>::const_iterator it = source_film_data.begin();it != source_film_data.end(); ++it)
    //     {
    //         j[it->first]=it->second;
    //     }

    //     out<<std::setw(4)<<j;
        
    //     return j;
    // }

    void from_json(const nlohmann::json& j, film_date& fd)
    {
        j.at("name").get_to(fd.name);
        j.at("country").get_to(fd.country);
        j.at("date").get_to(fd.date);
        j.at("studia").get_to(fd.studia);
        j.at("scenarist").get_to(fd.scenarist);
        j.at("director").get_to(fd.director);
        j.at("producer").get_to(fd.producer);
        j.at("actors").at(0).at("name").get_to(fd.actors[0].name);
        j.at("actors").at(0).at("surname").get_to(fd.actors[0].surname);
        j.at("actors").at(0).at("personage_name").get_to(fd.actors[0].role.name);
        j.at("actors").at(0).at("personage_description").get_to(fd.actors[0].role.description);

        j.at("actors").at(1).at("name").get_to(fd.actors[1].name);
        j.at("actors").at(1).at("surname").get_to(fd.actors[1].surname);
        j.at("actors").at(1).at("personage_name").get_to(fd.actors[1].role.name);
        j.at("actors").at(1).at("personage_description").get_to(fd.actors[1].role.description);

        j.at("actors").at(2).at("name").get_to(fd.actors[2].name);
        j.at("actors").at(2).at("surname").get_to(fd.actors[2].surname);
        j.at("actors").at(2).at("personage_name").get_to(fd.actors[2].role.name);
        j.at("actors").at(2).at("personage_description").get_to(fd.actors[2].role.description);

    }


    std::map<std::string,film_date> film_database(
        {std::pair<std::string, film_date>("Ivan Vasilyevich change profession",{
                    "Ivan Vasilyevich changes profession",
                    "USSR",
                    "1973",
                    "Mosfilm",
                    "Vladlen Bachnov",
                    "Leonid Gayday",
                    "Goschino",
                    {
                        {"Yriy","Yachovlev",{"Tsar","Tsar - Ioan Vasilyevich Grozniy"}},
                        {"Leonid","Kyravlev",{"Geroge Miloslavsky","description personage ..."}},
                        {"Alecsandr","Demianenko",{"Shurik","description personage ..."}}
                    }
                }
                ),
         std::pair<std::string, film_date>("test2",{
                 "test2",
                 "country",
                 "year",
                 "studia",
                 "stcenarist",
                 "director",
                 "producer",
                 {
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}},
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}},
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}}
                 }
             }
             ),
         std::pair<std::string, film_date>("test3",{
                 "test3",
                 "country",
                 "year",
                 "studia",
                 "stcenarist",
                 "director",
                 "producer",
                 {
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}},
                     {"Yriy","Yachovlev",{"Role name","description personage ..."}},
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}}
                 }
             }
             ),
         std::pair<std::string, film_date>("test4",{
                 "test4",
                 "country",
                 "year",
                 "studia",
                 "stcenarist",
                 "director",
                 "producer",
                 {
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}},
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}},
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}}
                 }
             }
             ),
         std::pair<std::string, film_date>("test5",{
                 "test5",
                 "country",
                 "year",
                 "studia",
                 "stcenarist",
                 "director",
                 "producer",
                 {
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}},
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}},
                     {"Actor name","Actor Surname",{"Role name","description personage ..."}}
                 }
             }
             ),

        });

    
    class Dispatcher
    {
    public:
        Dispatcher()noexcept=default;
        Dispatcher(const Dispatcher&)=delete;
        Dispatcher& operator=(const Dispatcher&)=delete;
        ~Dispatcher()=default;
        
        void create_film_base(const std::map<std::string, film_date>& source_film_data, const std::string& file_path)
            {
                std::ofstream out(file_path);
                if(!out)
                {
                    std::cerr<<"Error no open file "<<file_path<<std::endl;
                    return;
                }
       
                for(std::map<std::string, film_date>::const_iterator it = source_film_data.begin();it != source_film_data.end(); ++it)
                {
                    m_json[it->first] = it->second;
                }

                out<<std::setw(4)<<m_json;
            }

        void load_base_from_json(const std::string& file_path)
            {
                std::ifstream in(file_path);
                if(!in)
                {
                    std::cerr<<"Error no open file "<<file_path<<std::endl;
                    return;
                }
                m_json = nlohmann::json::parse(in);
            }
        
        void get_name_moves()
            {
                unsigned int counter{1};
                for(const auto& element : m_json.items())
                {
                    std::cout<<counter<<": "<<element.key()<<std::endl;
                    ++counter;
                }
            }

        void get_move_actor(const std::string& actor_name)
            {
                unsigned int counter{1};
                for(nlohmann::json::iterator it = m_json.begin(); it != m_json.end(); ++it)
                {
                    for(unsigned int i = 0; i < it.value().at("actors").size(); ++i)
                    {
                        if(it.value().at("actors").at(i).at("surname") == actor_name || it.value().at("actors").at(i).at("name").get<std::string>()+" "+ it.value().at("actors").at(i).at("surname").get<std::string>() == actor_name)
                        {
                            std::cout<<counter<<": "<<"Film name: "<<it.key()<<std::endl
                                     <<"Role: "<<it.value().at("actors").at(i).at("personage_name")<<std::endl
                                     <<"Description role: "<<it.value().at("actors").at(i).at("personage_description")<<std::endl;
                            ++counter;
                            std::cout<<"--------------------------------------"<<std::endl;
                        }

                    }
                }
                if(counter == 1)std::cout<<"Actor not found!"<<std::endl;
            }
        
        nlohmann::json get_json_object()const {return m_json;}

    private:
        nlohmann::json m_json;
    };


}// end cinema



#endif /* UTILS_JSON_H */
