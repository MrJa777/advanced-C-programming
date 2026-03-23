#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>
#include <algorithm>

struct Packet {
    std::string srcIP, dstIP;
    int   srcPort, dstPort;
    std::string proto;
    std::string direction;
    std::string payload;
    bool isSyn = false;
};

struct ConnKey {
    std::string srcIP; int srcPort;
    std::string dstIP; int dstPort;
    std::string proto;
    bool operator<(const ConnKey& o) const {
        std::ostringstream a, b;
        a << srcIP<<srcPort<<dstIP<<dstPort<<proto;
        b << o.srcIP<<o.srcPort<<o.dstIP<<o.dstPort<<o.proto;
        return a.str() < b.str();
    }
};
enum ConnState { SYN_SENT, ESTABLISHED, CLOSED };
std::map<ConnKey, ConnState> conntrack;

struct Rule {
    std::string  chain;
    std::string  srcNet;
    std::string  dstNet;
    int          dstPort;
    std::string  proto;
    std::string  target;
    std::string  comment;
    bool         stateful;
};

class Firewall {
    std::vector<Rule> rules_;
    int  accepted_=0, dropped_=0;

    bool matchNet(const std::string& ip, const std::string& net) {
        if(net=="ANY") return true;
        std::string prefix = net.substr(0, net.find('/'));
        return ip.find(prefix.substr(0, prefix.rfind('.'))) == 0;
    }

    bool isEstablished(const Packet& p) {
        ConnKey k{p.srcIP,p.srcPort,p.dstIP,p.dstPort,p.proto};
        ConnKey r{p.dstIP,p.dstPort,p.srcIP,p.srcPort,p.proto};
        return (conntrack.count(k) && conntrack[k]==ESTABLISHED)
            || (conntrack.count(r) && conntrack[r]==ESTABLISHED);
    }

    void trackConn(const Packet& p) {
        ConnKey k{p.srcIP,p.srcPort,p.dstIP,p.dstPort,p.proto};
        if(p.isSyn)               conntrack[k]=SYN_SENT;
        else if(conntrack.count(k)&&conntrack[k]==SYN_SENT)
                                  conntrack[k]=ESTABLISHED;
    }

public:
    void addRule(const Rule& r) { rules_.push_back(r); }

    std::string process(const Packet& p) {
        if(isEstablished(p)) {
            trackConn(p); accepted_++;
            return "ACCEPT (ESTABLISHED)";
        }

        for(auto& r : rules_) {
            bool matchProto = r.proto=="ANY" || r.proto==p.proto;
            bool matchSrc   = matchNet(p.srcIP, r.srcNet);
            bool matchDst   = (r.dstPort==-1 || r.dstPort==p.dstPort);
            bool matchDir   = r.chain == p.direction || r.chain == "BOTH";

            if(matchProto && matchSrc && matchDst && matchDir) {
                if(!p.payload.empty() &&
                   p.payload.find("DROP_KEYWORD") != std::string::npos) {
                    dropped_++;
                    return "DROP (DPI: banned content)";
                }
                trackConn(p);
                if(r.target=="ACCEPT"||r.target=="LOG") {
                    accepted_++;
                    return r.target + " [" + r.comment + "]";
                }
                dropped_++;
                return r.target + " [" + r.comment + "]";
            }
        }
        dropped_++;
        return "DROP (default policy)";
    }

    void stats() {
        std::cout << "\n[FW STATS] Accepted=" << accepted_
                  << "  Dropped=" << dropped_ << "\n";
    }
};

void printPacket(const Packet& p, const std::string& verdict) {
    std::cout << std::left
              << std::setw(16) << p.srcIP+":"+std::to_string(p.srcPort)
              << " → "
              << std::setw(16) << p.dstIP+":"+std::to_string(p.dstPort)
              << " [" << std::setw(5) << p.proto << "] "
              << verdict << "\n";
}

int main() {
    std::cout << "=== Stateful Firewall + DMZ Topology Simulator ===\n\n";

    Firewall fw;

    // Ruleset (iptables-style)
    fw.addRule({"INBOUND",  "ANY",           "ANY", 80,   "TCP", "ACCEPT", "Allow HTTP to DMZ",     false});
    fw.addRule({"INBOUND",  "ANY",           "ANY", 443,  "TCP", "ACCEPT", "Allow HTTPS to DMZ",    false});
    fw.addRule({"INBOUND",  "ANY",           "ANY", 22,   "TCP", "DROP",   "Block SSH from outside", false});
    fw.addRule({"INBOUND",  "10.0.0.0/8",    "ANY", 22,   "TCP", "ACCEPT", "Allow SSH from LAN",    false});
    fw.addRule({"OUTBOUND", "ANY",           "ANY", -1,   "ANY", "ACCEPT", "Allow all outbound",    true });
    fw.addRule({"FORWARD",  "192.168.2.0/24","ANY", -1,   "ANY", "ACCEPT", "DMZ→LAN forwarding",    true });

    std::cout << "─── Packet Processing ───\n";
    std::cout << std::left
              << std::setw(20) << "SRC"
              << std::setw(20) << "DST"
              << std::setw(8)  << "PROTO"
              << "VERDICT\n"
              << std::string(70,'-') << "\n";

    struct TestCase { Packet p; };
    std::vector<Packet> packets = {
        {"203.0.113.5",  "192.168.2.10", 54321, 80,  "TCP", "INBOUND",  "",               true},
        {"203.0.113.5",  "192.168.2.10", 54322, 443, "TCP", "INBOUND",  "",               true},
        {"203.0.113.99", "192.168.2.10", 54323, 22,  "TCP", "INBOUND",  "",               true},
        {"10.0.0.5",     "192.168.2.10", 54324, 22,  "TCP", "INBOUND",  "",               true},
        {"192.168.2.10", "8.8.8.8",      12345, 53,  "UDP", "OUTBOUND", "",               false},
        {"192.168.2.5",  "10.0.0.1",     8080,  80,  "TCP", "FORWARD",  "",               false},
        {"203.0.113.5",  "192.168.2.10", 54325, 80,  "TCP", "INBOUND",  "DROP_KEYWORD",   false},
    };

    for (auto& p : packets) {
        std::string v = fw.process(p);
        printPacket(p, v);
    }

    fw.stats();

    std::cout << "\n─── DMZ Topology ───\n";
    std::cout << "  [Internet] ─── Firewall ─── [DMZ: 192.168.2.0/24]\n";
    std::cout << "                     │\n";
    std::cout << "                 [LAN: 10.0.0.0/8]\n";
    std::cout << "\n  Zones:\n";
    std::cout << "    Internet  → DMZ  :80,443 ALLOW | :22 DROP\n";
    std::cout << "    LAN       → DMZ  :22     ALLOW (admin)\n";
    std::cout << "    DMZ       → WAN  :*      ALLOW (outbound)\n";
    std::cout << "    DMZ       → LAN  :*      ALLOW (forward)\n";

    return 0;
}
