
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

void load_env_file(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open .env file\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream is_line(line);
        string key;
        if (getline(is_line, key, '=')) {
            string value;
            if (getline(is_line, value)) {
                #ifdef _WIN32
                string env_entry = key + "=" + value;
                _putenv(env_entry.c_str());
                #else
                setenv(key.c_str(), value.c_str(), 1);
                #endif
            }
        }
    }
}

string get_api_key() {
    const char* key = getenv("API_KEY");
    if (!key) {
        cerr << "API_KEY not set\n";
        exit(1);
    }
    return string(key);
}

//int main() {
//    load_env_file(".env");
//
//    string api_key = get_api_key();
//    cout << "Your API key: " << api_key << endl;
//
//    // You can now use api_key in your API calls
//    return 0;
//}
