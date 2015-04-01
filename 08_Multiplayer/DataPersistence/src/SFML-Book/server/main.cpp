#include <ORM/backends/Sqlite3.hpp>
orm::Sqlite3DB def("./08_dataPersistence.sqlite");

orm::DB& orm::DB::Default = def;

#include <ORM/core/Tables.hpp>


#include <SFML-Book/server/Server.hpp>

#include <iostream>
#include <cstdlib>

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>


int main(int argc, char* argv[])
{
    int port = 5678;

    std::cout<<"Usage is : "<<argv[0]<<" [port]"<<std::endl;

    if(argc >1 )
        port = std::atoi(argv[1]);


    std::cout<<"Server start on port "<<port<<std::endl;

    orm::DB::Default.connect();
    orm::Tables::create();

    book::Server server(port);
    server.run();

    return 0;
}

