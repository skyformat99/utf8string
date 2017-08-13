# utf8string
A class to deal with UTF8 strings in C++ (either std::string or C strings).
Only by including utf8string.hpp, you can manipulate utf8 string, enabling it to:
- obtain a part of the string (substring)
- split the string with a delimiter and generate std::vector
- count the number of letters in the string (not the byte-count length)

## Usage
### To initialize
You can instantiate the UTF8String either with std::string or C string(char *).
```
std::string str = "abcあいうdef";
char cstr[100];
strcpy(cstr, str.c_str);

UTF8String ustr1 = str;
UTF8String ustr2 = cstr;
```
Or you can initialize it with an ordinary constructor.
```
UTF8String ustr3(str);
```

### Substring
```
// this should put out "cあい" ( .toString() needed to pass it to cout as a std::string)
std::cout << ustr1.substr(2, 3).toString();
```
### Split
```
std::string csv = "a,あ,b,c,い,う";
std::string delimiter = ",";
UTF8String ucsv  = csv;

std::vector<UTF8String> v = ucsv.split(delimiter);

// this should list up the each element delimited with comma
for(std::vector<UTF8String>::iterator it = v.begin(); it != v.end(); it++){
  std::cout << it->toString() << '\n';
}

```