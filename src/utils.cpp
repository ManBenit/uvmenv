#include "headers/utils.h"


// ****************** INTERFACE UTIL FUNCTIONS ****************** //
void printError(string message){
    cout << C_RED << message << C_N << endl;
}

void printInfo(string message){
    cout << C_GREEN << message << C_N << endl;
}

void printWarning(string message){
    cout << C_YELLOW << message << C_N << endl;
}

void printOption(string option, string message){
    cout << "     " << C_CYAN << option << C_N << "\n\t" << message << endl;
}

int countCharOcurrences(char c, string str) {
    int count = 0;

    for (char i : str)
        if (i == c) count++;

    return count;
}

vector<string> splitString(const string& input, char delimiter) {
    vector<string> tokens;
    istringstream stream(input);
    string token;

    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void runCommandSimple(const string& sysCommand) {
    FILE* pipe = popen(sysCommand.c_str(), "w");
    if (!pipe) {
        printError("Failed to run: " + sysCommand);
        exit(5);
    }
    pclose(pipe);
}

string runCommandReturn(const string& sysCommand){
    FILE* pipe = popen(sysCommand.c_str(), "r");
    if (!pipe) {
        printError("Failed to run: " + sysCommand);
        exit(5);
    }
    char buffer[128];
    string result = "";
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);

    //cout << result << endl;

    return result;
}
////////////////////////////////////////////////////////////////////



// ****************** FRAMEWORK UTIL FUNCTIONS ****************** //
bool isUVMEnvProject(){
    vector<string> pdirParts = splitString( getProjectDir(), '/' );
    string projectIdExpected = "uvm:" + pdirParts[pdirParts.size()-1] + ":env";
    string configFileName = "config.json";

    
    if( !filesystem::exists(configFileName) )
        return false;

    ifstream config_file(configFileName);
    json configFileData = json::parse(config_file);
    if( base64_decode(configFileData["id"]) != projectIdExpected )
        return false;

    return true;
} 

////////////////////////////////////////////////////////////////////

// ********************* COMMANDS FUNCTIONS ********************* //
void showHelp() {
    cout << "Usage:\t uvmenv " << C_CYAN << "<OPTION>" << C_N << "\n" << endl;

    cout << "  OPTION:" << endl;
    cout << "\t" << C_MAGENTA << "Framework management" << C_N << endl;
    printOption("-n|--new", "Creates a new UVMEnv project.");
    printOption("-s|--search", "Looks for a valid UVMEnv project into current directory.");
    printOption("-h|--help", string("Shows ") + C_YELLOW + "uvmenv" + C_N + " command help into system browser (less).");
    printOption("-i|--init", "Create default templates for top module.\n\tBFM, reference model, sequence item, sequence, agent, scoreboard.");
    printOption("-v|--view", "Shows project tree into system browser (less).");
    printOption("run", "Starts verification process.");
    printOption("wave", "Shows wave form using GTKWave.");
    printOption("report", "Shows the report file content.");

    cout << "\t" << C_MAGENTA << "UVM Component handling" << C_N << endl;
    printOption("-c|--create", "Create a UVM component.");
    printOption("-l|--list", "List UVM components and RTL modules and signals.");
    printOption("-e|--edit", "Allow to edit each file of current UVMEnv project.");
    printOption("-d|--delete", "Delete a UVM component");

    cout << endl;
}
////////////////////////////////////////////////////////////////////


// ****************** Python version ****************** //
string getPythonVersion(){
    string python_version_cmd = "python3 --version | awk '{print $2}' | cut -d'.' -f1,2";
    return runCommandReturn(python_version_cmd);
}

void activatePythonVenv(){
    float version = stof(getPythonVersion());
    if(version >= 3.10){
        string activate_cmd = "bash -c 'source " + getVenvDir() + "/bin/activate'";
        runCommandSimple(activate_cmd);
    }
}

///////////////////////////////////////////////////////////////////



// ****************** Base 64 ****************** //
string base64_encode(const string &in) {
    static const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string out;
    int val = 0, valb = -6;

    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');
    return out;
}


string base64_decode(const string &in) {
    static const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[chars[i]] = i;

    string out;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}
///////////////////////////////////////////////////////////////////


// ***************** File writing/reading/research ***************** //
void writeFile(const string filePath, const string content) {
    ofstream outFile(filePath);
    if (!outFile) {
        printError("Error opening file for writing: " + filePath);
        return;
    }
    outFile << content;
    outFile.close();
}

string readFile(const string filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        printError("Error opening file for reading: " + filePath);
        return "";
    }
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    return content;
}

vector<string> getFileNamesInDirectory(const string directoryPath) {
    vector<string> fileNames;

    try {
        for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                fileNames.push_back(entry.path().filename().string());
            } else if (entry.is_directory()) {
                // Get internal files recursively
                vector<string> subFiles = getFileNamesInDirectory(entry.path().string());
                for (const auto& subFile : subFiles) {
                    fileNames.push_back(entry.path().filename().string() + "/" + subFile);
                }
            }
        }
    } catch (const filesystem::filesystem_error& e) {
        cerr << "Error accediendo al directorio: " << e.what() << endl;
    }

    return fileNames;
}
///////////////////////////////////////////////////////////////////

