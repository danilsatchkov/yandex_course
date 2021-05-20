
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
/*
using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

string ReadLine() {
	string s;
	getline(cin, s);
	return s;
}

int ReadLineWithNumber() {
	int result;
	cin >> result;
	ReadLine();
	return result;
}

vector<string> SplitIntoWords(const string& text) {
	vector<string> words;
	string word;
	for (const char c : text) {
		if (c == ' ') {
			if (!word.empty()) {
				words.push_back(word);
				word.clear();
			}
		}
		else {
			word += c;
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
set<string> MakeUniqueNonEmptyStrings(const StringContainer& strings) {
	set<string> non_empty_strings;
	for (const string& str : strings) {
		if (!str.empty()) {
			non_empty_strings.insert(str);
		}
	}
	return non_empty_strings;
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
		: stop_words_(MakeUniqueNonEmptyStrings(stop_words))  // Extract non-empty stop words
	{
		if (!all_of(stop_words_.begin(), stop_words_.end(), IsValidWord)) {
			throw invalid_argument("Some of stop words are invalid"s);
		}
	}

	explicit SearchServer(const string& stop_words_text)
		: SearchServer(SplitIntoWords(stop_words_text))  // Invoke delegating constructor from string container
	{
	}

	void AddDocument(int document_id, const string& document, DocumentStatus status, const vector<int>& ratings) {
		if ((document_id < 0) || (documents_.count(document_id) > 0)) {
			throw invalid_argument("Invalid document_id"s);
		}
		const auto words = SplitIntoWordsNoStop(document);

		const double inv_word_count = 1.0 / words.size();
		for (const string& word : words) {
			word_to_document_freqs_[word][document_id] += inv_word_count;
		}
		documents_.emplace(document_id, DocumentData{ ComputeAverageRating(ratings), status });
		document_ids_.push_back(document_id);
	}

	template <typename DocumentPredicate>
	vector<Document> FindTopDocuments(const string& raw_query, DocumentPredicate document_predicate) const {
		const auto query = ParseQuery(raw_query);

		auto matched_documents = FindAllDocuments(query, document_predicate);

		sort(matched_documents.begin(), matched_documents.end(), [](const Document& lhs, const Document& rhs) {
			if (abs(lhs.relevance - rhs.relevance) < 1e-6) {
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

	vector<Document> FindTopDocuments(const string& raw_query, DocumentStatus status) const {
		return FindTopDocuments(raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
			return document_status == status;
		});
	}

	vector<Document> FindTopDocuments(const string& raw_query) const {
		return FindTopDocuments(raw_query, DocumentStatus::ACTUAL);
	}

	int GetDocumentCount() const {
		return documents_.size();
	}

	int GetDocumentId(int index) const {
		return document_ids_.at(index);
	}

	tuple<vector<string>, DocumentStatus> MatchDocument(const string& raw_query, int document_id) const {
		const auto query = ParseQuery(raw_query);

		vector<string> matched_words;
		for (const string& word : query.plus_words) {
			if (word_to_document_freqs_.count(word) == 0) {
				continue;
			}
			if (word_to_document_freqs_.at(word).count(document_id)) {
				matched_words.push_back(word);
			}
		}
		for (const string& word : query.minus_words) {
			if (word_to_document_freqs_.count(word) == 0) {
				continue;
			}
			if (word_to_document_freqs_.at(word).count(document_id)) {
				matched_words.clear();
				break;
			}
		}
		return { matched_words, documents_.at(document_id).status };
	}

private:
	struct DocumentData {
		int rating;
		DocumentStatus status;
	};
	const set<string> stop_words_;
	map<string, map<int, double>> word_to_document_freqs_;
	map<int, DocumentData> documents_;
	vector<int> document_ids_;

	bool IsStopWord(const string& word) const {
		return stop_words_.count(word) > 0;
	}

	static bool IsValidWord(const string& word) {
		// A valid word must not contain special characters
		return none_of(word.begin(), word.end(), [](char c) {
			return c >= '\0' && c < ' ';
		});
	}

	vector<string> SplitIntoWordsNoStop(const string& text) const {
		vector<string> words;
		for (const string& word : SplitIntoWords(text)) {
			if (!IsValidWord(word)) {
				throw invalid_argument("Word "s + word + " is invalid"s);
			}
			if (!IsStopWord(word)) {
				words.push_back(word);
			}
		}
		return words;
	}

	static int ComputeAverageRating(const vector<int>& ratings) {
		if (ratings.empty()) {
			return 0;
		}
		int rating_sum = 0;
		for (const int rating : ratings) {
			rating_sum += rating;
		}
		return rating_sum / static_cast<int>(ratings.size());
	}

	struct QueryWord {
		string data;
		bool is_minus;
		bool is_stop;
	};

	QueryWord ParseQueryWord(const string& text) const {
		if (text.empty()) {
			throw invalid_argument("Query word is empty"s);
		}
		string word = text;
		bool is_minus = false;
		if (word[0] == '-') {
			is_minus = true;
			word = word.substr(1);
		}
		if (word.empty() || word[0] == '-' || !IsValidWord(word)) {
			throw invalid_argument("Query word "s + text + " is invalid");
		}

		return { word, is_minus, IsStopWord(word) };
	}

	struct Query {
		set<string> plus_words;
		set<string> minus_words;
	};

	Query ParseQuery(const string& text) const {
		Query result;
		for (const string& word : SplitIntoWords(text)) {
			const auto query_word = ParseQueryWord(word);
			if (!query_word.is_stop) {
				if (query_word.is_minus) {
					result.minus_words.insert(query_word.data);
				}
				else {
					result.plus_words.insert(query_word.data);
				}
			}
		}
		return result;
	}

	// Existence required
	double ComputeWordInverseDocumentFreq(const string& word) const {
		return log(GetDocumentCount() * 1.0 / word_to_document_freqs_.at(word).size());
	}

	template <typename DocumentPredicate>
	vector<Document> FindAllDocuments(const Query& query, DocumentPredicate document_predicate) const {
		map<int, double> document_to_relevance;
		for (const string& word : query.plus_words) {
			if (word_to_document_freqs_.count(word) == 0) {
				continue;
			}
			const double inverse_document_freq = ComputeWordInverseDocumentFreq(word);
			for (const auto[document_id, term_freq] : word_to_document_freqs_.at(word)) {
				const auto& document_data = documents_.at(document_id);
				if (document_predicate(document_id, document_data.status, document_data.rating)) {
					document_to_relevance[document_id] += term_freq * inverse_document_freq;
				}
			}
		}

		for (const string& word : query.minus_words) {
			if (word_to_document_freqs_.count(word) == 0) {
				continue;
			}
			for (const auto[document_id, _] : word_to_document_freqs_.at(word)) {
				document_to_relevance.erase(document_id);
			}
		}

		vector<Document> matched_documents;
		for (const auto[document_id, relevance] : document_to_relevance) {
			matched_documents.push_back({ document_id, relevance, documents_.at(document_id).rating });
		}
		return matched_documents;
	}
};

//this should be a pair of iterators that describe a page
template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator in_begin, Iterator in_end) :
		it_begin_(in_begin), it_end_(in_end)
	{}
	Iterator begin() const {
		return it_begin_;
	}

	Iterator end() const {
		return it_end_+1;
	}

	auto size() const {
		return size_;
	}
	Iterator it_begin_;
	Iterator it_end_;
	size_t size_ = distance(it_begin_, it_end_);
};

//constructor to create paginator from iterators to the result of FindTopDocuments and page_size
//creates a vector of pairs of iterators, each one has begin and end
template<typename Iterator>
class Paginator {
public:
	Paginator(Iterator doc_begin, Iterator doc_end, size_t page_size) {
		size_t ctr = 1;
		Iterator range_begin;
		Iterator range_end;
		int dist = distance(doc_begin, doc_end);

		for (auto it = doc_begin; it != doc_end; ++it) {

			if (ctr%page_size == 1) range_begin = it;

			if(ctr%page_size == 0||dist==ctr)
			{
				range_end = it;
				paginator_.push_back(IteratorRange(range_begin, range_end));
			}
			++ctr;	
		}
	}
	
	public:
	auto begin() const {
		return paginator_.begin();
	}

	auto end() const {
		return paginator_.end();
	}

	auto size() const {
		return paginator_.size();
	}


private:
	std::vector<IteratorRange<Iterator>> paginator_;
};


template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
	return Paginator(begin(c), end(c), page_size);
}

ostream& operator<<(ostream& out, Document document) {
	out << "{ "
		<< "document_id = " << document.id 
		<< ", "<< "relevance = " << document.relevance 
		<< ", "	<< "rating = " << document.rating<< " }";
	return out;
}

template<typename Iterator>
ostream& operator<<(ostream& out, IteratorRange<Iterator> page) {
	for (auto i = page.begin(); i != page.end(); i++) {
		out << *i ;
	}
	return out;
}



int main() {
	SearchServer search_server("and with"s);

	search_server.AddDocument(1, "funny pet and nasty rat"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
	search_server.AddDocument(2, "funny pet with curly hair"s, DocumentStatus::ACTUAL, { 1, 2, 3 });
	search_server.AddDocument(3, "big cat nasty hair"s, DocumentStatus::ACTUAL, { 1, 2, 8 });
	search_server.AddDocument(4, "big dog cat Vladislav"s, DocumentStatus::ACTUAL, { 1, 3, 2 });
	search_server.AddDocument(5, "big dog hamster Borya"s, DocumentStatus::ACTUAL, { 1, 1, 1 });

	const auto search_results = search_server.FindTopDocuments("curly dog"s);
	int page_size = 2;
	const auto pages = Paginate(search_results, page_size);  //pages is a vector of IteratorRange

	// ������� ��������� ��������� �� ���������
	for (auto page = pages.begin(); page != pages.end(); ++page) {
		cout << *page << endl;
		cout << "Page break"s << endl;
	}
	
}

*/