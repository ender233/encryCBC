### encryCBC
verification of en/decryption for AES cbc mode using https://github.com/randombit/botan 

### help
```
liu@liu-XPS-13-9343:~/Project/encryCBC$ ./encryCBC --help
All options:
-d [ --direction ] arg (=0)       0-encryption 1-decryption
-t [ --text ] arg (=Changeme_123) encryText or decryText
-h [ --help ]                     generate help message, just support AES128
                                  example1: ./encryCBC -d0 -tChangeme_123
                                  example2: ./encryCBC -d1 -tc88516b4464c14f66c4d155c6f901cae
                                  example3:./encryCBC -tChangeme_123

original Text:Changeme_123
after encry result is:c88516b4464c14f66c4d155c6f901cae
```
