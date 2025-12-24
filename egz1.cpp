#include <iostream>
#include <fstream>
#include <string>
#include <regex> 
#include <map>
#include <set> 
#include <cctype>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Naudojimas: " << argv[0] << " ivestis.txt\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Nepavyko atidaryti failo: " << argv[1] << "\n";
        return 1;
    }

    std::map<std::string, int> zodziuKiekis;
    std::map<std::string, std::set<int>> zodziuEilutes;

    std::map<std::string, std::set<int>> urlEilutes;

    std::regex urlRegex(
        R"((https?://[^\s,]+)|(www\.[^\s,]+)|([A-Za-z0-9-]+\.[A-Za-z0-9.-]+))",
        std::regex::icase);

    std::string eilute;
    int eilNr = 0;

    while (std::getline(in, eilute)) {
        ++eilNr;

        auto pr = std::sregex_iterator(eilute.begin(), eilute.end(), urlRegex);
        auto pb = std::sregex_iterator();

        for (auto it = pr; it != pb; ++it) {
            std::string url = it->str();

            while (!url.empty() &&
                   (url.back() == '.' || url.back() == ',' ||
                    url.back() == ';' || url.back() == ':' ||
                    url.back() == ')' || url.back() == '!' ||
                    url.back() == '?')) {
                url.pop_back();
            }

            bool turiRaide = false;
            for (char c : url) {
                if (std::isalpha((unsigned char)c)) {
                    turiRaide = true;
                    break;
                }
            }
            if (!turiRaide || url.empty())
                continue;

            urlEilutes[url].insert(eilNr);
        }

        std::string zodis;
        for (size_t i = 0; i <= eilute.size(); ++i) {
            unsigned char c = (i < eilute.size())
                              ? (unsigned char)eilute[i]
                              : ' ';

            if (std::isalnum(c)) {
                zodis.push_back((char)c);
            } else {
                if (!zodis.empty()) {
                    for (char &ch : zodis)
                        ch = (char)std::tolower((unsigned char)ch);

                    zodziuKiekis[zodis]++;
                    zodziuEilutes[zodis].insert(eilNr);

                    zodis.clear();
                }
            }
        }
    }

    std::cout << "URL ADRESAI:\n";
    if (urlEilutes.empty()) {
        std::cout << "(URL adresu nerasta)\n";
    } else {
        for (auto const &p : urlEilutes) {
            std::cout << p.first << " (eilutes: ";
            bool pirmas = true;
            for (int ln : p.second) {
                if (!pirmas) std::cout << ",";
                std::cout << ln;
                pirmas = false;
            }
            std::cout << ")\n";
        }
    }

    std::cout << "\nLENTELE (ZODIS, KIEKIS, EILUTES):\n";

    const int STULP_ZODIS = 16;
    const int STULP_KIEK  = 6;

    std::cout << std::left  << std::setw(STULP_ZODIS) << "ZODIS"
              << std::right << std::setw(STULP_KIEK)  << "KIEKIS"
              << "  EILUTES\n";

    for (auto const &p : zodziuKiekis) {
        const std::string &zodis = p.first;
        int kiek = p.second;

        std::cout << std::left  << std::setw(STULP_ZODIS) << zodis
                  << std::right << std::setw(STULP_KIEK)  << kiek
                  << "  ";

        bool pirmas = true;
        for (int ln : zodziuEilutes[zodis]) {
            if (!pirmas) std::cout << ",";
            std::cout << ln;
            pirmas = false;
        }
        std::cout << "\n";
    }

    return 0;
}

