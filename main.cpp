#include "cicrybotanCBC.hpp"
#include <iostream> 

#include "boost/program_options.hpp"
#include "boost/program_options/errors.hpp"

//using opt = boost::program_options;
namespace opt = boost::program_options;
using namespace std;

int main(int argc, char *argv[])
{
    opt::options_description desc("All options");
    desc.add_options()
        ("direction,d", opt::value<int>()->default_value(0), "0-encryption 1-decryption")
        //("aesmod,a", opt::value<int>()->default_value(128), "128-AES128 194-AES194 256-AES256")
        ("text,t", opt::value<string>()->default_value("Changeme_123"), "encryText or decryText")
        ("help,h", "generate help message, just support AES128\nexample1: ./encryCBC -d0 -tChangeme_123\nexample2: ./encryCBC -d1 -tc88516b4464c14f66c4d155c6f901cae\nexample3:./encryCBC -tChangeme_123");

    opt::variables_map vm;   
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);
    if(vm.count("help")) {
        std::cout<<desc<<endl;
    }

    std::string oriText("Changeme_223");
    int dir(0);
    int cryMod(128);
    if(vm.count("direction")) dir = vm["direction"].as<int>();
    if(vm.count("text")) oriText = vm["text"].as<string>();

    AES_ENCRYP_LENGTH aesMod = (128 == cryMod) ? AES_KEY_LENGTH_16 : 
        ((194 == cryMod)? AES_KEY_LENGTH_24 : AES_KEY_LENGTH_32);

    if(!dir) {
       std::string encryRes = AESCBCBotanUtil::encryptionCBC(oriText,
                aesMod, "1234567890123456");
        cout<<"original Text:"<<oriText<<endl;
        cout<<"after encry result is:"<<encryRes<<endl;
    }
   
    if(dir) {
        std::string decryRes = AESCBCBotanUtil::decryptionCBC(oriText,
                aesMod, "1234567890123456");
        cout<<"original Text:"<<oriText<<endl;
        cout<<"after decry result is:"<<decryRes<<endl;
    }
       return 0;
}
