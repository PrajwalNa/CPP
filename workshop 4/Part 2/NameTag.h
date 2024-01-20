# ifndef nameTag_h
# define nameTag_h
# include <iostream>

namespace fast {

    class NameTag {
        char* m_name;
        int m_number;

        public:
        NameTag();
        NameTag(const char* name);
        NameTag(const char* name, int number);
        ~NameTag();
        void setName(const char* name);
        NameTag& read();
        std::ostream& print() const;
        void prn(const char str[], const int length) const;
    };
}
#endif