#pragma once
#include <botan/rng.h>
#include <botan/auto_rng.h>
#include <botan/cipher_mode.h>
#include <botan/hex.h>
#include <botan/key_filt.h>
#include <botan/pipe.h>

#include "prettyprint.hpp"
#include <iostream>

using namespace std;
using namespace Botan;
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <sstream>

enum AES_ENCRYP_LENGTH
{
    AES_KEY_LENGTH_16 = 16,
    AES_KEY_LENGTH_24 = 24,
    AES_KEY_LENGTH_32 = 32,
};
const std::string initIv = "1234567890123456";

std::string string_to_hex(const std::string &in)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    size_t cnt = in.length();
    for(size_t i=0; i<cnt; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }
    return ss.str();
}

std::string hex_to_string(const std::string& in) {
    std::string output;

    if ((in.length() % 2) != 0) {
        throw std::runtime_error("String is not valid length ...");
    }

    size_t cnt = in.length() / 2;

    size_t i = 0;
    for (; cnt > i; ++i) {
        uint32_t s = 0;
        std::stringstream ss;
        ss << std::hex << in.substr(i * 2, 2);
        ss >> s;
        output.push_back(static_cast<unsigned char>(s));
    }

    return output;
}

std::string vecByte_to_string(const secure_vector<byte> &vec)
{
    std::string result;

    for(auto &v : vec) {
        result.append(1, (unsigned char)v);
    }
    return result;
}

struct AESCBCBotanUtil
{
    static std::string encryptionCBC(string plainText, AES_ENCRYP_LENGTH len, std::string keyStr)
    {
        std::string encryMod;
        const std::vector<uint8_t>  key = hex_decode(string_to_hex(keyStr));
        std::vector<uint8_t> iv = hex_decode(string_to_hex(initIv));
        if(len == AES_KEY_LENGTH_16) encryMod = string("AES-128/CBC/PKCS7");
        if(len == AES_KEY_LENGTH_24) encryMod = string("AES-192/CBC/PKCS7");
        if(len == AES_KEY_LENGTH_32) encryMod = string("AES-256/CBC/PKCS7");

        Pipe pipe(get_cipher(encryMod, key, iv, ENCRYPTION));
        pipe.process_msg(plainText);
        return string_to_hex(pipe.read_all_as_string());
    }

    static std::string decryptionCBC(string cryText, AES_ENCRYP_LENGTH len, std::string keyStr)
    {
        std::string decryMod; 
        const std::vector<uint8_t> key = hex_decode(string_to_hex(keyStr));
        std::vector<uint8_t> iv = hex_decode(string_to_hex(initIv));
        if(len == AES_KEY_LENGTH_16) decryMod = string("AES-128/CBC/PKCS7");
        if(len == AES_KEY_LENGTH_24) decryMod = string("AES-192/CBC/PKCS7");
        if(len == AES_KEY_LENGTH_32) decryMod = string("AES-256/CBC/PKCS7");

        Pipe pipe(get_cipher(decryMod, key, iv, DECRYPTION));
        pipe.process_msg(hex_to_string(cryText));
        return pipe.read_all_as_string();
    }
};

