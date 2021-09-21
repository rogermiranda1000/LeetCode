int strStr(char * haystack, char * needle) {
    int x = 0;
    int last = 0, index = 0;

    while (haystack[x]) {
        if (needle[index] == '\0') return last;

        if (haystack[x] != needle[index]) {
            x = last; // ++ after if
            last++;
            index = 0;
        }
        else index++;
        
        x++;
    }

    return (needle[index] == '\0') ? last : -1; // found on last position?
}