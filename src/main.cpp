#include "server.hpp"
#include <chrono>
#include <iostream>

int main(){
    Server server(1200);
    auto t0=std::chrono::steady_clock::now();
    auto grid=server.proximityQueries();
    auto t1=std::chrono::steady_clock::now();
    auto tg=std::chrono::duration<double,std::milli>(t1-t0).count();
    t0=std::chrono::steady_clock::now();
    auto naive=Server::naiveQueries(server.players());
    t1=std::chrono::steady_clock::now();
    auto tn=std::chrono::duration<double,std::milli>(t1-t0).count();
    server.tick(0.016f);
    std::cout<<"PulseGrid authoritative server\n";
    std::cout<<"Simulated players: "<<server.players().size()<<"\n";
    std::cout<<"Grid queries: "<<grid<<" | naive: "<<naive<<"\n";
    std::cout<<"Spatial query time: "<<tg<<" ms | naive: "<<tn<<" ms\n";
    std::cout<<"Speedup: "<<(tg>0?tn/tg:0)<<"x\n";
}
