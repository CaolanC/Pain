#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

class Token
{
    public:

    int i_type; // 1:keyword 2:intliteral 3:separator 4:operator
    std::string s_type;
    std::string name;
    bool assigned = false;

    void mkToken(int t_type, std::string t_name, std::string str_type)
    {
        i_type = t_type;
        name = t_name;
        s_type = str_type;
        assigned = true;
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

    void printContents()
    {
        std::cout << m_src << std::endl;
    };

    std::vector<Token> tokenize()
    {
        m_index = 0;
        std::string buffer;
        std::cout << "Beginning Tokenization.\n";

        while(!(isEOF()))
        {
            std::cout << m_src.at(m_index);
            Token new_token;
            if (m_src.at(m_index) == '\n') {
                new_token.mkToken(3, "newline", "separator");
                m_index++;
            } else 
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
            if (m_src.at(m_index) == '/' && !(isEOF()) && peak() == '/') 
            {
                m_index += 2;
                new_token.mkToken(4, "//", "operator");
            } else 
            {
                if (m_src.at(m_index) != ' ')
                {
                buffer.push_back(consume());
                new_token = assertToken(buffer);
                }
                std::cout << "empchar";
                m_index++;
            }
            if (new_token.assigned)
            {
                tokens.push_back(new_token);
            };
            buffer = "";
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
    std::vector<std::string> operator_names = {"=", "+"};

    int m_index;
    std::string m_src;

    Token assertToken(std::string buffer)
    {

        std::cout << "\nAsserted: " << buffer << '\n';
        Token new_token;
        for (std::string keyword : keyword_names)
        {
            if (keyword == buffer)
            {
                new_token.mkToken(1, keyword, "keyword");
                return new_token;
            };
        };

        for (std::string op : operator_names)
        {
            if (op == buffer)
            {
                new_token.mkToken(4, op, "operator");
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

class Node
{
    public:

    bool exists = false;

    int type;
    std::vector<Node> children;

    Node()
    {
        type = 0;
    };

    Node(int n_type)
    {
        type = n_type;
    };

    void giveChild(Node child)
    {
        children.push_back(child);
    };

};

class AST
{
    private:

    Node start_node;

    bool p_isEscape(Token token)
    {
        if (token.)
    };

    void p_genTree(std::vector<Token> tokens, Node parent_token)
    {
        for (Token token : tokens)
        {

        };
    };



    public:

    void makeTree(std::vector<Token> tokens)
    {
        p_genTree(tokens, start_node);
    };

};

std::string getStringFromFile(std::string filename)
{
    std::ifstream file;

    file.open(filename);

    std::string contents = "";
    std::string content;

    while (std::getline(file, content)) {
        contents += content + '\n';
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
