#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

class Token
{
    public:

    int i_type;
    std::string s_type;
    std::string name;

    void mkToken(int t_type, std::string t_name, std::string str_type)
    {
        i_type = t_type;
        name = t_name;
        s_type = str_type;
    };
};

class Tokenizer     
{

    public:

    std::string content;
    std::vector<Token> tokens;

    Tokenizer(std::string str_file)
    {
        m_src = str_file;
    };

    std::vector<Token> tokenize()
    {
        m_index = 0;
        std::string buffer;
        std::cout << "Beginning Tokenization.\n";

        while(!(isEOF()))
        {
            std::cout << m_src.at(m_index) << std::endl;
            Token new_token;
            if (std::isalpha(m_src.at(m_index)))    // IDENTIFIER + Keywords
            {
                buffer.push_back(consume());
                while (!(isEOF()) && std::isalnum(peak())) //IDENTIFIER
                {
                    buffer.push_back(consume());
                };

                new_token = assertToken(buffer);
            } else
            if (std::isdigit(m_src.at(m_index)))    // integer literal
            {
                buffer.push_back(consume());
                while (!(isEOF()) && std::isdigit(peak()))
                {
                    buffer.push_back(consume());
                };

                new_token.mkToken(2, buffer, "int literal");
            } else
            if (m_src[m_index] == '\n')
            {
                std::cout << "cum";
                new_token.mkToken(3, "newline", "separator");
            } else {
                std::cout << "cum";
            };
            tokens.push_back(new_token);
            buffer = "";
            m_index++;
        };

        std::cout << "Finished Tokenization.\n";
    };

    void printTokens()
    {
        for (Token token : tokens)
        {
            std::cout << token.name << " " << token.s_type << std::endl;
        };
    };

    private:

    std::vector<std::string> keyword_names = {"return", "int"};

    int m_index;
    std::string m_src;

    Token assertToken(std::string buffer)
    {
        Token new_token;
        for (std::string keyword : keyword_names)
        {
            if (keyword == buffer)
            {
                new_token.mkToken(1, keyword, "keyword");
                return new_token;         
            };
        };
        new_token.mkToken(0, buffer, "identifier");
        return new_token;
    };

    char peak(int ahead = 1)
    {
        if (m_index + ahead > m_src.length())
        {
            return '\0';
        } else {
            return m_src.at(m_index);
        };

    };

    char consume()
    {
        return m_src.at(m_index++);
    };

    bool isEOF()
    {
        return peak() == '\0';
    };
};

std::string getStringFromFile(std::string filename)
{
    std::ifstream file;

    file.open(filename);

    std::string contents = "";
    std::string content;

    while (std::getline(file, content)) {
        contents += content;
    }

    file.close();

    return contents;
};


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "No file provided." << std::endl;
        exit(1);
    }
    std::string str_contents = getStringFromFile(argv[1]);

    Tokenizer tokenizer(str_contents);
    tokenizer.tokenize();
    tokenizer.printTokens();
};

// TYPE IDENTIFIER = VALUE