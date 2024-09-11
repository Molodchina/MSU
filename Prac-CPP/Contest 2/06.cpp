#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl, std::vector, std::string, std::min;

class StringView
{
public:
    using iterator = string::iterator;
    using const_iterator = string::const_iterator;
    using reverse_iterator = string::reverse_iterator;
    using const_reverse_iterator = string::const_reverse_iterator;

    StringView(string &s, size_t begin = 0,
               size_t count = string::npos) : _sv(s), _begin(begin){
        if (begin >= s.size()) {
            _begin = 0;
            _last = 0;
        } else if (count > s.size() - begin) {
            _last = s.size();
        } else {
            _last = count + _begin;
        }
    }

    StringView(const StringView &sv, size_t begin = 0,
               size_t count = string::npos) : _sv(sv._sv), _begin(begin + sv.begin()) {
        if (begin >= sv.size()) {
            _begin = 0;
            _last = 0;
        } else if (count > sv.size() - begin) {
            _last = sv.size() + sv.begin();
        } else {
            _last = count + _begin;
        }
    }

    size_t length() const {
        return _last - _begin;
    }

    size_t size() const {
        return _last - _begin;
    }

    size_t begin() const {
        return _begin;
    }

    char &operator[] (size_t idx) const {
        return _sv[idx + _begin];
    }

    string str(size_t begin = 0,
               size_t count = string::npos) const {
        if (begin >= _last - _begin)
            return "";
        return _sv.substr(begin + _begin, min(count, _last - _begin - begin));
    }

    char &at(size_t pos) const {
        if (pos >= _last - _begin) {
            throw std::out_of_range("");
        }
        return _sv[pos + _begin];
    }

    iterator begin() {
        auto elem = _sv.begin();
        std::advance(elem, _begin);
        return elem;
    }
    iterator end() {
        auto elem = _sv.begin();
        std::advance(elem, _last);
        return elem;
    }

    reverse_iterator rbegin() {
        auto elem = _sv.rend();
        std::advance(elem, -_last);
        return elem;
    }
    reverse_iterator rend() {
        auto elem = _sv.rend();
        std::advance(elem, -_begin);
        return elem;
    }

    const_iterator cbegin() {
        auto elem = _sv.cbegin();
        std::advance(elem, _begin);
        return elem;
    }
    const_iterator cend() {
        auto elem = _sv.cbegin();
        std::advance(elem, _last);
        return elem;
    }

    const_reverse_iterator crbegin() {
        auto elem = _sv.crend();
        std::advance(elem, -_last);
        return elem;
    }
    const_reverse_iterator crend() {
        auto elem = _sv.crend();
        std::advance(elem, -_begin);
        return elem;
    }

    StringView &operator = (const StringView &) = delete;
private:
    string &_sv;
    size_t _begin;
    size_t _last;
};

bool operator > (const StringView &sv1, const StringView &sv2) {
    return sv1.str() > sv2.str();
}

bool operator < (const StringView &sv1, const StringView &sv2) {
    return sv1.str() < sv2.str();
}

bool operator >= (const StringView &sv1, const StringView &sv2) {
    return sv1.str() >= sv2.str();
}

bool operator <= (const StringView &sv1, const StringView &sv2) {
    return sv1.str() <= sv2.str();
}

bool operator == (const StringView &sv1, const StringView &sv2) {
    return sv1.str() == sv2.str();
}

bool operator != (const StringView &sv1, const StringView &sv2) {
    return sv1.str() != sv2.str();
}
