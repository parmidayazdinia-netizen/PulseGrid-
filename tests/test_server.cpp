#include "server.hpp"
#include <cassert>
#include <iostream>

int main(){
    // 128 parameterized checks across player counts and reconciliation inputs.
    int checks=0;
    for(int n=1;n<=16;n++){
        Server s(static_cast<size_t>(n*8));
        assert(s.players().size()==static_cast<size_t>(n*8)); checks++;
        assert(s.proximityQueries()>=s.players().size()); checks++;
        for(int k=0;k<6;k++){
            Player p{1,float(k),float(k),1,1};
            NetworkState st{static_cast<uint32_t>(k),{1,float(k+2),float(k+2),0,0}};
            auto r=Reconciler::reconcile(p,st);
            assert(r.x>p.x && r.x<st.authoritative.x); checks++;
            assert(r.y>p.y && r.y<st.authoritative.y); checks++;
        }
    }
    std::cout<<"PASS: "<<checks<<" parameterized checks\n";
}
