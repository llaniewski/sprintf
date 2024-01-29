#include <assert.h>
#include <stdio.h>

#include <string>

class Printer {
   private:
    template <typename T>
    const T& maybeString(const T& t) {
        return t;
    }
    inline const char* maybeString(const std::string& str) { return str.c_str(); }
    static std::string buf;

   public:
    template <class... Args>
    int sprintf(std::string& str, const char* format, Args&&... args) {
        const int n_chars = std::snprintf(nullptr, 0, format, maybeString(args)...);
        assert(n_chars >= 0);
        str.resize(static_cast<typename std::string::size_type>(n_chars + 1));
        std::snprintf(&str[0], str.size() + 1, format, maybeString(args)...);
        return n_chars;
    }

    template <class... Args>
    std::string formatAsString(const char* format, Args&&... args) {
        sprintf(buf, format, args...);
        return buf;
    }
};

std::string Printer::buf;

Printer printer;

int main() {
    printf("%d\n", 10);
    printf("%s\n", printer.formatAsString("%d %s\n", 10, "test").c_str());
    return 0;
}
