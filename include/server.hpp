#pragma once
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

struct Player { uint32_t id; float x{}, y{}; float vx{}, vy{}; };

class SpatialGrid {
    float cell_; std::unordered_map<int64_t,std::vector<uint32_t>> cells_;
    int cell(float v) const { return static_cast<int>(std::floor(v/cell_)); }
    static int64_t key(int x,int y){ return (static_cast<int64_t>(x)<<32) ^ static_cast<uint32_t>(y); }
public:
    explicit SpatialGrid(float cell=8.f):cell_(cell){}
    void clear(){cells_.clear();}
    void insert(const Player& p){cells_[key(cell(p.x),cell(p.y))].push_back(p.id);}
    std::vector<uint32_t> nearby(float x,float y,float r) const {
        std::vector<uint32_t> out; int minx=cell(x-r),maxx=cell(x+r),miny=cell(y-r),maxy=cell(y+r);
        for(int cx=minx;cx<=maxx;cx++) for(int cy=miny;cy<=maxy;cy++){
            auto it=cells_.find(key(cx,cy)); if(it!=cells_.end()) out.insert(out.end(),it->second.begin(),it->second.end());
        } return out;
    }
};

class Server {
    std::vector<Player> players_; SpatialGrid grid_;
public:
    explicit Server(size_t n=1000):grid_(8.f){
        players_.reserve(n); for(size_t i=0;i<n;i++) players_.push_back({static_cast<uint32_t>(i),float(i%100)*2.f,float(i/100)*2.f});
        rebuildGrid();
    }
    void rebuildGrid(){grid_.clear(); for(const auto&p:players_) grid_.insert(p);}
    void tick(float dt){for(auto&p:players_){p.x+=p.vx*dt;p.y+=p.vy*dt;} rebuildGrid();}
    const std::vector<Player>& players() const{return players_;}
    size_t proximityQueries(float r=10.f) const {size_t n=0; for(const auto&p:players_) n+=grid_.nearby(p.x,p.y,r).size(); return n;}
    static size_t naiveQueries(const std::vector<Player>& ps,float r=10.f){size_t n=0; for(const auto&a:ps) for(const auto&b:ps) if(std::hypot(a.x-b.x,a.y-b.y)<=r)n++; return n;}
};

// Transport boundary used by the simulation; a production adapter can bind this to WebSockets.
struct NetworkState { uint32_t sequence{}; Player authoritative{}; };
class Reconciler {
public:
    static Player reconcile(Player predicted,const NetworkState& server){
        predicted.x += (server.authoritative.x-predicted.x)*0.5f;
        predicted.y += (server.authoritative.y-predicted.y)*0.5f;
        return predicted;
    }
};
