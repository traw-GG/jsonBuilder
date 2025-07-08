#include <string>
#include <sstream>

/*

        JsonArrayBuilder jsonArray;

        for (const auto& [param1, param2] : pools) {
            std::ostringstream playerStream;
            playerStream << "{"
                         << "\"nickname\":\"" << param1 << "\","
                         << "\"playerId\":" << param2
                         << "}";

            jsonArray.addRawJson(playerStream.str());
        }

        std::string jsonString = jsonArray.build();

 */

class JsonArrayBuilder {
private:
    std::ostringstream arrayStream;
    bool needsComma = false;

    void addCommaIfNeeded() {
        if (needsComma) {
            arrayStream << ",";
        }
        needsComma = true;
    }

public:
    JsonArrayBuilder() {
        arrayStream << "[";
    }

    JsonArrayBuilder& add(int value) {
        addCommaIfNeeded();
        arrayStream << value;
        return *this;
    }

    JsonArrayBuilder& add(float value) {
        addCommaIfNeeded();
        arrayStream << value;
        return *this;
    }

    JsonArrayBuilder& add(bool value) {
        addCommaIfNeeded();
        arrayStream << (value ? "true" : "false");
        return *this;
    }

    JsonArrayBuilder& add(const std::string& value) {
        addCommaIfNeeded();
        arrayStream << "\"";
        for (char c : value) {
            switch (c) {
                case '"': arrayStream << "\\\""; break;
                case '\\': arrayStream << "\\\\"; break;
                case '\b': arrayStream << "\\b"; break;
                case '\f': arrayStream << "\\f"; break;
                case '\n': arrayStream << "\\n"; break;
                case '\r': arrayStream << "\\r"; break;
                case '\t': arrayStream << "\\t"; break;
                default: arrayStream << c;
            }
        }
        arrayStream << "\"";
        return *this;
    }

    JsonArrayBuilder& addRawJson(const std::string& json) {
        addCommaIfNeeded();
        arrayStream << json;
        return *this;
    }

    std::string build() {
        arrayStream << "]";
        return arrayStream.str();
    }

    void clear() {
        arrayStream.str("");
        arrayStream.clear();
        arrayStream << "[";
        needsComma = false;
    }
};