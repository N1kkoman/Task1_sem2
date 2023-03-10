#include <iostream>
#include <string>
#include <vector>

class FibonacciCipher {
private:
    std::vector<int> key;
    std::vector <std::string> Words;
    std::string msgAnsStr;
public:
    void setKey(std::vector<int>& newKey) {
        key = newKey;
    }
    std::string Encode(std::string& newMsg) {
        Cipher(newMsg, false);
        msgAnsStr.resize(msgAnsStr.size() - 1); // убираем пробел после работы метода Cipher()
        return msgAnsStr;
    }

    std::string Decode(std::string& newMsg) {
        Cipher(newMsg, true);
        msgAnsStr.resize(msgAnsStr.size() - 1);
        return msgAnsStr;
    }

private:

    // Разбиение предложения на слова
    void lineSeparator(std::string& newMsg) {
        std::string word;
        for (auto&& i : newMsg) {
            if (i != ' ') {
                word += i;
            }
            else {
                Words.push_back(word);
                word.clear();
            }
        }
        Words.push_back(word);
    }

    // Проверка на правильность данных (количество слов, ключ)
    bool testData(std::string& newMsg, std::vector<int>& newKey)
    {
        lineSeparator(newMsg);
        if (Words.size() == newKey.size())
        {
            int num1 = 1;
            int num2 = 1;
            int temp;
            for (int i = 0; i < newKey.size(); ++i)
            {
                for (int j = 0; j < key.size(); ++j)
                {
                    if (key[j] == num2) 
                    {
                        break;
                    }
                    else if (j == newKey.size() - 1)
                    {
                        return false;
                    }
                }
                temp = num2;
                num2 = num1 + num2;
                num1 = temp;
            }
            return true;
        }
        return false;
    }

    // Шифрование с помощью последовательности Фибоначчи 
    void Cipher(std::string& newMsg, bool flag)
    {
        Words.clear();
        msgAnsStr.clear();
        std::vector <std::string> msgAns(key.size(), "0");
        if (!testData(newMsg, key))
        {
            std::cout << "Error data";
            std::exit(0);
        }
        int num1 = 1;
        int num2 = 1;
        int tempNum;
        for (int i = 0; i < key.size(); ++i) 
        {
            for (int j = 0; j < key.size(); ++j)
            {
                if (key[j] == num2)
                {
                    if (flag) 
                        msgAns[i] = Words[j];
                    else 
                        msgAns[j] = Words[i];
                }
            }
            tempNum = num2;
            num2 = num1 + num2;
            num1 = tempNum;
        }
        for (auto&& n : msgAns) 
        {
            msgAnsStr += n + ' ';
        }
    }
};

int main() {
    std::vector <int> key = { 2,8,5,1,3 };
    std::string msg = "Hello, my name is Ivan.";
    std::string ans1;
    std::string ans2;

    FibonacciCipher enc;
    enc.setKey(key);

    ans1 = enc.Encode(msg);
    std::cout << ans1 << std::endl;

    ans2 = enc.Decode(ans1);
    std::cout << ans2;
    return 0;
}