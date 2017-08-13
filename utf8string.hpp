#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>

class UTF8String {
  
private:
  char *originalStr;

public:
  
  UTF8String(std::string str){
    originalStr = (char *)malloc(str.length());
    strcpy(originalStr, str.c_str());
  }
  UTF8String(char *cstr){
    originalStr = (char *)malloc(strlen(cstr));
    strcpy(originalStr, cstr);
  }
  // copy constructor
  UTF8String(const UTF8String& copyObj){
    std::string str = copyObj.toString();
    originalStr = (char *)malloc(sizeof(char) * str.length());
    strcpy(originalStr, str.c_str());    
  }

  ~UTF8String(){
    free(originalStr);
  }
  
  int utf8length(){
    int pos = 0;
    int len = 0;
    
    while(originalStr[pos]){
      if( (originalStr[pos] & 0b11000000)  == 0b11000000){
	len++;
      }else if ((originalStr[pos] & 0b10000000)  == 0b10000000){
	len = len + 0;
      }else {
	len++;
      }
      pos++;
    }
    return len;
  }
  void utf8substr_cstr(int startPos, int length, char *subtractedStr){
    int len = 0;
    int resultPos = 0;
    int resultLen = 0;
    int pos = 0;
    
    while(originalStr[pos]){
      // begging of a multibyte character
      if( (originalStr[pos] & 0b11000000)  == 0b11000000){
	len++;
	if(startPos <= (len - 1)){
	  resultLen = resultLen + 1;
	  if(resultLen > length){
	    subtractedStr[resultPos] = '\0';
	    break;
	  }
	}
	// continuing byte of a mutibyte character
      }else if ((originalStr[pos] & 0b10000000)  == 0b10000000){
	len = len + 0;
	// ascii character
      }else {
	len++;
	if(startPos  <= (len - 1) ){
	  resultLen = resultLen + 1;
	  if(resultLen > length){
	    subtractedStr[resultPos] = '\0';	    
	    break;
	  }
	}
      }
      
      if(resultLen){
	subtractedStr[resultPos] = originalStr[pos];
	resultPos++;
      }      
      pos++;
    }
  }

  std::string utf8substr(int startPos, int length){
    char *tmp = (char *)malloc(sizeof(char) * length);
    utf8substr_cstr(startPos, length, tmp);
    std::string str(tmp);
    free(tmp);
    return str;    
  }

  UTF8String substr(int startPos, int length){
    char *tmp = (char *)malloc(sizeof(char) * length);
    utf8substr_cstr(startPos, length, tmp);
    UTF8String newStr(tmp);
    free(tmp);
    return newStr;
  }

  std::string toString() const{
    std::string str(originalStr);
    return str;
  }

  UTF8String operator=(char *str){
    UTF8String newStr(str);
    return newStr;    
  }

  UTF8String operator+(UTF8String str){
    char *concatStr = (char *)malloc(strlen(originalStr) + strlen(str.toString().c_str()));
    strcat(concatStr, originalStr);
    strcat(concatStr, str.toString().c_str());
    UTF8String concatUStr = concatStr;
    free(concatStr);
    return concatStr;
  }

  UTF8String operator=(std::string str){
    UTF8String newStr(str);
    return newStr;
  }
  
  std::vector<UTF8String> split(UTF8String delimiter){
    int prevPosition = 0;
    int len = utf8length();
    std::vector<UTF8String> v;
    for(int i = 0; i < len; i++){
      
      if(delimiter.utf8length() && strcmp(delimiter.toString().c_str(), substr(i,1).toString().c_str()) == 0){
	UTF8String str = substr(prevPosition, i - prevPosition);
	v.push_back(str);
	prevPosition = i + 1;
      }
      if(delimiter.utf8length() == 0){
	UTF8String str = substr(i, 1);
	v.push_back(str);
      }
    }
    if(delimiter.utf8length() && prevPosition < len){
      UTF8String str = substr(prevPosition, len - prevPosition);
      v.push_back(str);
    }
    return v;
  }

  std::vector<UTF8String> split(std::string delimiter){
    UTF8String utf8delimiter = delimiter;
    return split(utf8delimiter);
  }

  std::vector<UTF8String> split(char *delimiter){
    UTF8String utf8delimiter = delimiter;
    return split(utf8delimiter);
  }

  
};
