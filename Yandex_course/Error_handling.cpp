#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cassert>

//using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

std::string ReadLine()
{
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int ReadLineWithNumber()
{
    int result;
    std::cin >> result;
    ReadLine();
    return result;
}

std::vector<std::string> SplitIntoWords(const std::string& text)
{
    std::vector<std::string> words;
    std::string word;
    for (const char character : text)
    {
        if (character == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += character;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

struct Document {
    Document() = default;

    Document(int id, double relevance, int rating)
        : id(id)
        , relevance(relevance)
        , rating(rating) {
    }

    int id = 0;
    double relevance = 0.0;
    int rating = 0;
};

template <typename StringContainer>
std::set<std::string> MakeUniqueNonEmptyStrings(const StringContainer& strings)
{
    std::set<std::string> non_empty_strings;

    for (const std::string& str : strings) {
        if (!str.empty()) {
            non_empty_strings.insert(str);
        }
    }
    return non_empty_strings;
}

static bool IsValidWord(const std::string& word)
{
    // A valid word must not contain special characters
    return std::none_of(word.begin(), word.end(), [](char c) {
        return c >= '\0' && c < ' ';
    });
}

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};

class SearchServer {
public:
    template <typename StringContainer>
    explicit SearchServer(const StringContainer& stop_words)
        : stop_words_(MakeUniqueNonEmptyStrings(stop_words))
    {
        for (const auto& stopword : stop_words) { 
            if (!IsValidWord(stopword)) throw std::invalid_argument("stop words contain forbidden symbols");

        }
    }

    explicit SearchServer(const std::string& stop_words_text)
        : SearchServer(SplitIntoWords(stop_words_text))  // Invoke delegating constructor from string container
    {
    }

    void AddDocument(int document_id, const std::string& document, DocumentStatus status, const std::vector<int>& ratings)
    {
        assert(ratings.size() != 0);
        if (document_id < 0)  throw std::invalid_argument("document id less than zero");
        else if (documents_.find(document_id) != documents_.end()) throw std::invalid_argument("document already added");

        document_id_.push_back(document_id);

        const std::vector<std::string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / static_cast<double> (words.size());

        for (const std::string& word : words) {
            if (!IsValidWord(word)) throw std::invalid_argument("forbidden symbols when adding a document");
            word_to_document_freqs_[word][document_id] += inv_word_count;
        }
        documents_.emplace(document_id, DocumentData{ ComputeAverageRating(ratings), status });

    }

    template <typename DocumentPredicate>
    std::vector<Document> FindTopDocuments(const std::string& raw_query, DocumentPredicate document_predicate) const
    {
        const Query query = ParseQuery(raw_query);

        auto matched_documents = FindAllDocuments(query, document_predicate);

        sort(matched_documents.begin(), matched_documents.end(), [this](const Document& lhs, const Document& rhs)
        {
            if (abs(lhs.relevance - rhs.relevance) < double_tolerance_) {
                return lhs.rating > rhs.rating;
            }
            else {
                return lhs.relevance > rhs.relevance;
            }
        });

        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }


    std::vector<Document> FindTopDocuments(const std::string& raw_query, DocumentStatus status) const
    {
        return FindTopDocuments(raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
            return document_status == status;
        });
    }

    std::vector<Document> FindTopDocuments(const std::string& raw_query) const
    {
        return FindTopDocuments(raw_query, DocumentStatus::ACTUAL);
    }

    int GetDocumentCount() const {
        return static_cast<int>(documents_.size());
    }

    std::tuple<std::vector<std::string>, DocumentStatus> MatchDocument(const std::string& raw_query, int document_id) const
    {
        const Query query = ParseQuery(raw_query);
        std::vector<std::string> matched_words;

        for (const std::string& word : query.plus_words)
        {
            if (word_to_document_freqs_.count(word) == 0)
            {
                continue;
            }

            if (word_to_document_freqs_.at(word).count(document_id))
            {
                matched_words.push_back(word);
            }
        }

        for (const std::string& word : query.minus_words)
        {
            if (word_to_document_freqs_.count(word) == 0)
            {
                continue;
            }

            if (word_to_document_freqs_.at(word).count(document_id))
            {
                matched_words.clear();
                break;
            }
        }

        return make_tuple(matched_words, documents_.at(document_id).status);
    }

    int GetDocumentId(int index) const
    {
        auto found_id = document_id_.at(index);

        return  found_id;
    }
private:
    const double double_tolerance_ = 1e-6;

private:
    struct DocumentData
    {
        int rating = 0;
        DocumentStatus status;
    };

    bool IsStopWord(const std::string& word) const
    {
        return stop_words_.count(word) > 0;
    }

    std::vector<std::string> SplitIntoWordsNoStop(const std::string& text) const
    {
        std::vector<std::string> words;
        for (const std::string& word : SplitIntoWords(text))
        {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    static int ComputeAverageRating(const std::vector<int>& ratings)
    {
        assert(ratings.size() != 0);
        if (ratings.empty()) {
            return 0;
        }
        int rating_sum = 0;

        for (const int rating : ratings) {
            rating_sum += rating;
        }

        return rating_sum / static_cast<int>(ratings.size());
    }

    struct QueryWord
    {
        std::string data;
        bool is_minus = false;
        bool is_stop = false;
    };

    QueryWord ParseQueryWord(std::string text) const
    {
        bool is_minus = false;

        assert(!text.empty());

        if (text[0] == '-') {
            is_minus = true;
            text = text.substr(1);
        }
        //three possible problems with separate exceptions
        if (text[0] == '-')  throw std::invalid_argument("query contains -");
        else if (text.size() == 0) throw std::invalid_argument("query is empty");
        else if (!IsValidWord(text)) throw std::invalid_argument("query contains forbidden symbols)");

        return
        {
            text, is_minus, IsStopWord(text)
        };
    };


    struct Query {
        std::set<std::string> plus_words;
        std::set<std::string> minus_words;
    };

    Query ParseQuery(const std::string& text) const
    {
        Query query;
        for (const std::string& word : SplitIntoWords(text))
        {
            const QueryWord query_word = ParseQueryWord(word);

            if (!query_word.is_stop) {

                if (query_word.is_minus) {
                    query.minus_words.insert(query_word.data);
                }
                else {
                    query.plus_words.insert(query_word.data);
                }
            }
        }
        return query;
    }

    // Existence required
    double ComputeWordInverseDocumentFreq(const std::string& word) const
    {
        assert(word_to_document_freqs_.at(word).size() != 0);

        return log(GetDocumentCount() * 1.0 / static_cast<double>(word_to_document_freqs_.at(word).size()));
    }

    template <typename DocumentPredicate>
    std::vector<Document> FindAllDocuments(const Query& query, DocumentPredicate document_predicate) const
    {
        std::map<int, double> document_to_relevance;

        for (const std::string& word : query.plus_words) {

            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            const double inverse_document_freq = ComputeWordInverseDocumentFreq(word);

            for (const auto[document_id, term_freq] : word_to_document_freqs_.at(word))
            {
                const auto& document_data = documents_.at(document_id);

                if (document_predicate(document_id, document_data.status, document_data.rating))
                {
                    document_to_relevance[document_id] += term_freq * inverse_document_freq;
                }
            }
        }

        for (const std::string& word : query.minus_words)
        {
            if (word_to_document_freqs_.count(word) == 0)
            {
                continue;
            }

            for (const auto[document_id, _] : word_to_document_freqs_.at(word))
            {
                document_to_relevance.erase(document_id);
            }
        }
        std::vector<Document> matched_documents;

        for (const auto[document_id, relevance] : document_to_relevance)
        {
            matched_documents.push_back({ document_id, relevance, documents_.at(document_id).rating });
        }
        return matched_documents;
    }

private:
    const std::set<std::string> stop_words_;
    std::map<std::string, std::map<int, double>> word_to_document_freqs_;
    std::map<int, DocumentData> documents_;
    std::vector<int> document_id_;
};

void PrintDocument(const Document& document)
{
    std::cout << "{ "
        << "document_id = " << document.id << ", "
        << "relevance = " << document.relevance << ", "
        << "rating = " << document.rating << " }" << std::endl;
}

void PrintMatchDocumentResult(int document_id, const std::vector<std::string>& words, DocumentStatus status)
{
    std::cout << "{ "
        << "document_id = " << document_id << ", "
        << "status = " << static_cast<int>(status) << ", "
        << "words =";
    for (const std::string& word : words)
    {
        std::cout << ' ' << word;
    }
    std::cout << "}" << std::endl;
}

void AddDocument(SearchServer& search_server, int document_id, const std::string& document, DocumentStatus status,
    const std::vector<int>& ratings)
{
    try {
        search_server.AddDocument(document_id, document, status, ratings);
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка добавления документа " << document_id << ": " << e.what() << std::endl;
    }
}

void FindTopDocuments(const SearchServer& search_server, const std::string& raw_query)
{
    std::cout << "Результаты поиска по запросу: " << raw_query << std::endl;

    try {
        for (const Document& document : search_server.FindTopDocuments(raw_query)) {
            PrintDocument(document);
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка поиска: " << e.what() << std::endl;
    }
}

void MatchDocuments(const SearchServer& search_server, const std::string& query)
{
    try {
        std::cout << "Матчинг документов по запросу: " << query << std::endl;
        const int document_count = search_server.GetDocumentCount();
        for (int index = 0; index < document_count; ++index) {
            const int document_id = search_server.GetDocumentId(index);
            const auto[words, status] = search_server.MatchDocument(query, document_id);
            PrintMatchDocumentResult(document_id, words, status);
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Ошибка матчинга документов на запрос " << query << ": " << e.what() << std::endl;
    }
}

int main() {
    std::string initial_stopwords = "и в на";
    SearchServer search_server(initial_stopwords);

    AddDocument(search_server, 1, "пушистый кот пушистый хвост", DocumentStatus::ACTUAL, { 7, 2, 7 });
    AddDocument(search_server, 1, "пушистый пёс и модный ошейник", DocumentStatus::ACTUAL, { 1, 2 });
    AddDocument(search_server, -1, "пушистый пёс и модный ошейник", DocumentStatus::ACTUAL, { 1, 2 });
    AddDocument(search_server, 3, "большой пёс скво\x12рец евгений", DocumentStatus::ACTUAL, { 1, 3, 2 });
    AddDocument(search_server, 4, "большой пёс скворец евгений", DocumentStatus::ACTUAL, { 1, 1, 1 });

    FindTopDocuments(search_server, "пушистый -пёс");
    FindTopDocuments(search_server, "пушистый --кот");
    FindTopDocuments(search_server, "пушистый -");

    MatchDocuments(search_server, "пушистый пёс");
    MatchDocuments(search_server, "модный -кот");
    MatchDocuments(search_server, "модный --пёс");
    MatchDocuments(search_server, "пушистый - хвост");
}

