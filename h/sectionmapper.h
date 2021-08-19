# ifndef SECTIONS
# define SECTIONS

# include <map>
# include <string>
class SectionMapper{

    public:

        void newSectionContent(std::string name, int size);

        void skip(std::string name, int size, int from);

        void init2(std::string name, int value, int from);

        void init1(std::string name, int value, int from);

    private:
        std::map<std::string,char*> content;
};

# endif